#include "Parser.h"

Parser::Parser(QString const &cmdline)
{
    (void)cmdline;
    std::cout << cmdline.toStdString() << std::endl;
}

Parser::Parser( void )
{
    isNameExpression = false;
    coordCount = 0;
    cCount = 0;
    eCount = 0;
    fmap[Parser::COMMAND] = &Parser::commandSyntax;
    fmap[Parser::EXPANSION] = &Parser::expansionSyntax;
    fmap[Parser::EXPANSION_FIELD] = &Parser::fieldSyntax;
}

Parser::~Parser()
{

}

void Parser::setCommand(QString const &cmd)
{
    this->cmd = cmd.toStdString();
    std::locale loc;
    for(std::string::size_type i = 0; i < this->cmd.size(); i++)
    {
        char &c = this->cmd[i];
        if (std::isupper(c, loc)) c = std::tolower(c, loc);
    }
}

void Parser::reset( void )
{
    this->coordCount = 0;
    this->cCount = 0;
    this->eCount = 0;
    this->shape.clear();
    this->command.clear();
    this->name.clear();
    lst.clear();
}

bool Parser::parser(QString const &cmd)
{
    setCommand(cmd);
    reset();
    if (!lexicalAnalysis(this->cmd) || !syntaxAnalysis() || !semanticAnalysis() || eCount != 1 || cCount != 1 || coordCount < 2)
        return (false);
    if (!insertShapeData())
        return (false);
    return (true);
}

bool Parser::lexicalAnalysis(std::string const &cmd)
{
    std::string query = cmd;
    int i = 0;
    while(i < (int)query.size() && query[i])
    {
        if (isCommandPart(query[i]))
        {
            //command
            // std::cout << "Command" << std::endl;
            if (!insert(Parser::COMMAND, query, &i))
                return (false);
            continue;
        }
        else if (query[i] == '-')
        {
            //expansion
            // std::cout << "Expansion" << std::endl;
            i++;
            if (!insert(Parser::EXPANSION, query, &i))
                return (false);
            continue;
        }
        else if (query[i] == '{')
        {
            //expansion field
            // std::cout << "Expansion Field" << std::endl;
            if (!insert(query, &i))
                return (false);
            continue;
        }
        else if(isSpace(query[i]))
        {
            i++;
            continue;
        }
        else
        {
            return (false);
        }
        i++;
    }
    return (true);
}

void Parser::printList( void )
{
    for(auto &l : lst)
    {
        Parser::tok type;
        std::string lex;
        std::tie(type, lex) = l;
        std::cout << type << " : " << lex << std::endl;
    }
}

bool Parser::syntaxAnalysis( void )
{
    for(auto &lex : lst)
    {
        Parser::tok type;
        std::string lexeme;
        std::tie(type, lexeme) = lex;
        if (type == EXPANSION && lexeme == "name")
            isNameExpression = true;
        if (!(this->*fmap[type])(type, lexeme))
            return (false);
    }
    return (true);
}

bool Parser::semanticAnalysis( void )
{
    for(int i = 0; i < lst.size(); i++)
    {
        auto [cLex, cVal] = lst[i];
        if ((i + 1) < lst.size())
        {
            auto [nLex, nVal] = lst[i + 1];
            switch (cLex)
            {
                case Parser::COMMAND :
                    if (nLex != Parser::EXPANSION)
                        return (false);
                    break;
                case Parser::EXPANSION :
                    if (nLex != Parser::EXPANSION_FIELD)
                        return (false);
                    break;
                case Parser::EXPANSION_FIELD :
                    if (nLex == Parser::EXPANSION_FIELD || nLex == Parser::COMMAND)
                        return (false);
                    break;
            }
        }
    }

    return (true);
}

//command or expansions
int Parser::insert(Parser::tok type, std::string const &query, int *i)
{
    int len = 0;
    int j = *i;
    while (isValidExpression(query[j]))
    {
        len++;
        j++;
    }
    if (!len)
        return (0);
    std::string exp = query.substr(*i, len);
    lst.push_back(std::make_tuple(type, trim(exp)));
    *i += len;
    return (1);
}

//expansion fields
int Parser::insert(std::string &query, int *i)
{
    int len = 0;
    int j = *i;
    bool found = false;
    while (query[j])
    {
        if (query[j] == '}')
        {
            found = true;
            break;
        }
        j++;
        len++;
    }
    if (!found || !len)
        return (false);
    std::string field = query.substr(*i+1, len-1);
    lst.push_back(std::make_tuple(EXPANSION_FIELD, trim(field)));
    *i += len+1;
    return (1);
}

bool Parser::isCommandPart(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
        return (true);
    return (false);
}

bool Parser::isValidExpression(char c)
{
    if (isCommandPart(c) || isDigit(c) || c == '-')
        return (true);
    return (false);
}

bool Parser::isDigit(char c)
{
    if ((c >= 48 && c <= 57))
        return (true);
    return (false);
}

bool Parser::isSpace(char c)
{
    if((c >= 9 && c <= 13) || c == 32)
        return (true);
    return (false);
}

std::string Parser::rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" \n\t\f\v");
    return (end == std::string::npos ? "" : s.substr(0, end + 1));
}

std::string Parser::ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \n\t\f\v");
    return (start == std::string::npos ? s : s.substr(start));
}

std::string Parser::trim(const std::string &s)
{
    return (ltrim(rtrim(s)));
}

bool Parser::commandSyntax(Parser::tok type, std::string lexeme)
{
    (void)type;
    size_t f;
    if ((f = lexeme.find('_')) != std::string::npos)
    {
        cCount++;
        command = lexeme.substr(0, f);
        shape = lexeme.substr(f+1);
        return (true);
    }
    return (false);
}

bool Parser::expansionSyntax(Parser::tok type, std::string lexeme)
{
    (void)type;
    constexpr auto prefix = "coord_";
    if (lexeme == "name")
    {
        eCount++;
        return (true);
    }
    if (lexeme.compare(0, std::strlen(prefix), prefix) == 0)
    {
        coordCount++;
        return (true);
    }
    return (false);
}

bool Parser::fieldSyntax(Parser::tok type, std::string lexeme)
{
    (void)type, (void)lexeme;
    std::string validChars;
    size_t f;
    if (isNameExpression)
    {
        //name expansion
        validChars = "abcdefghijklmnopqrstuvwxyz0123456789";
        isNameExpression = false;
        f = lexeme.find_first_not_of(validChars);
        if (f != std::string::npos)
            return (false);
        name = lexeme;
    }
    else
    {
        //coordinates expansion
        validChars = "-+0123456789., ";
        f = lexeme.find_first_not_of(validChars);
        if (f != std::string::npos)
            return (false);
        if (!isValidCoordinate(lexeme))
            return (false);
    }
    return (true);
}

bool Parser::isValidCoordinate(std::string const &coord)
{
      std::stringstream ss(coord);
      std::string item;
      std::vector<std::string> tokens;

      while (std::getline(ss, item, ',')) {
          tokens.push_back(trim(item));
      }
      if (tokens.size() != 2) {
          return false;
      }
      for (const auto& token : tokens) {
          if (!isInteger(token)) {
              return false;
          }
      }
      return true;
}

bool Parser::isInteger(std::string const &coord)
{
    if (coord.empty()) {
         return false;
     }
     std::istringstream iss(coord);
     double d;
     iss >> d;
     return iss.eof() && !iss.fail();
}

bool Parser::insertShapeData( void )
{
    shapeData.shape = this->shape;
    shapeData.command = this->command;
    shapeData.name = this->name;
    std::string coordName;
    for(int i = 0; i < lst.size(); i++)
    {
        std::string lexeme;
        Parser::tok type;
        std::tie(type, lexeme) = lst[i];
        if (type == Parser::EXPANSION && lexeme != "name")
        {
            std::string coordinates = std::get<1>(lst[i+1]);
            if (!insertCoordinates(lexeme, coordinates))
                return (false);
        }
    }
    return (true);
}

bool Parser::insertCoordinates(std::string const &lexeme, std::string const &coordinates)
{
    size_t comma = coordinates.find(',');
    if (comma == std::string::npos)
        return (false);
    std::string xCoord = coordinates.substr(0, comma);
    std::string yCoord = coordinates.substr(comma + 1);
    try
    {
        double x = std::stod(xCoord);
        double y = std::stod(yCoord);
        shapeData.coord[lexeme] = {x, y};
    } catch (const std::invalid_argument& e) {
        std::cerr << "Incorrect Symbols (" << xCoord << ", " << yCoord << ")" << std::endl;
        return (false);
    }
    return (true);
}

ShapeData   const &Parser::getShapeData( void ) const
{
    return (this->shapeData);
}
