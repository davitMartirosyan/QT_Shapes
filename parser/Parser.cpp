#include "Parser.h"

Parser::Parser(QString const &cmdline)
{
    (void)cmdline;
    std::cout << cmdline.toStdString() << std::endl;
}

Parser::Parser( void )
{
    cCount = 0;
    eCount = 0;
    fmap[Parser::COMMAND] = &Parser::commandSyntax;
    fmap[Parser::EXPANSION] = &Parser::expansionSyntax;
    fmap[Parser::SHAPE_NAME] = &Parser::expansionSyntax;
    fmap[Parser::EXPANSION_FIELD] = &Parser::fieldSyntax;
}

Parser::~Parser()
{
    std::cout << "mta destructor" << std::endl;
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

void Parser::resetCommandCount( void )
{
    this->cCount = 0;
}

void Parser::resetCommandName( void )
{
    this->commandName.clear();
}
void Parser::resetShapeName( void )
{
    this->shapeName.clear();
}

bool Parser::parser(QString const &cmd)
{
    setCommand(cmd);
    resetCommandCount();
    resetCommandName();
    resetShapeName();

    auto cleaning = [&]() {lst.clear(); return (false);};
    if (
            !lexicalAnalysis(this->cmd) || !syntaxAnalysis() /*|| !semanticAnalysis() || eCount != 1 || cCount != 1*/)
            return cleaning();

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
    // printList();
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
        if (!(this->*fmap[type])(type, lexeme))
            return (false);
    }
    return (true);
}

// bool Parser::syntaxAnalysis( void )
// {
//     Parser::tok prevType;
//     bool first = true;

//     for(auto &lex : lst)
//     {
//         Parser::tok currType;
//         std::string lexeme;
//         std::tie(currType, lexeme) = lex;

//         if (!first) {
//             if (!(this->*fmap[currType])(prevType, lexeme))
//                 return false;
//         } else {
//             first = false;
//         }

//         prevType = currType;
//     }
//     return true;
// }

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
                    if (nLex != Parser::EXPANSION && nLex != Parser::SHAPE_NAME)
                        return (false);
                    break;
                case Parser::EXPANSION :
                case Parser::SHAPE_NAME :
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
    cCount++;
    if ((f = lexeme.find('_')) != std::string::npos)
    {
        commandName = lexeme.substr(0, f);
        shapeName = lexeme.substr(f+1);
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
        return (true);
    return (false);
}

// bool Parser::fieldSyntax(Parser::tok type, std::string lexeme)
// {
//     std::string validChars;
//     size_t f;
//     if (type == Parser::SHAPE_NAME)
//         validChars = "-+0123456789. abcdefghijklmnopqrstuvwxyz";
//     else if(type == Parser::EXPANSION)
//         validChars = "-+0123456789,. ";
//     f = lexeme.find_first_not_of(validChars);
//     if (f != std::string::npos)
//         return (false);
//     if (type == Parser::EXPANSION && !isValidCoordinate(lexeme))
//             return (false);
//     return (true);
// }

bool Parser::fieldSyntax(Parser::tok type, std::string lexeme)
{
    (void)type, (void)lexeme;
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

      std::cout << "coordinates: " << std::endl;
      for(auto &coord : tokens)
      {
          std::cout << coord << " : ";
      }
      std::cout << std::endl;
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


