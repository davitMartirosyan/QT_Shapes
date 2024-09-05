#ifndef PARSER_H
#define PARSER_H
#include <QString>
#include <iostream>
#include <string>
#include <sstream>
#include <QVector>
#include <QList>
#include <QMap>
#include <QPair>
#include <tuple>

struct ShapeData
{
    std::string shape;
    QMap<std::string, std::pair<int, int>> coord;
};

class Parser
{
private:
    enum tok
    {
        COMMAND,            // create_rectangle
        EXPANSION,          // coord_1
        SHAPE_NAME,         // name
        EXPANSION_FIELD,    // {34,45}
    };

public:
    Parser(QString const &cmdline);
    Parser( void );
    void setCommand(QString const &cmd);
    void resetCommandCount( void );
    void resetCommandName( void );
    void resetShapeName( void );
    void printList( void );
    ~Parser();

private:
    QList<std::tuple<Parser::tok, std::string >>    lst;
    QMap<Parser::tok, bool(Parser::*)(Parser::tok, std::string)> fmap;

private:
    ShapeData   shapeData;
    std::string cmd;
    std::string commandName;
    std::string shapeName;
    short       cCount;
    short       eCount;

private:
    bool commandSyntax(Parser::tok, std::string);
    bool expansionSyntax(Parser::tok, std::string);
    bool fieldSyntax(Parser::tok, std::string);

public slots:
    bool    parser(QString const &cmd);
    bool    lexicalAnalysis(std::string const &cmd);
    bool    syntaxAnalysis( void );
    bool    semanticAnalysis( void );

private: //helpers
    bool        isCommandPart(char c);
    bool        isSpace(char c);
    bool        isDigit(char c);
    bool        isValidExpression(char c);
    bool        isInteger(std::string const &coord);
    bool        isValidCoordinate(std::string const &coord);

public:
    int         insert(std::string &query, int *i);
    int         insert(Parser::tok type, std::string const &query, int *i);
    ShapeData   const &getShapeData( void ) const;

public:
    std::string ltrim(const std::string &s);
    std::string rtrim(const std::string &s);
    std::string trim(const std::string &s);
};


//create_rectangle  -name{Rect1}    -coord_1{13, 14}    -coord_2{34,45}
//create_triangle   -name{Tri1}     -coord_1{50, 50}    -coord_2{60,40}     -coord_3{70,50}
//create_line       -name{Li1}      -coord_1{90, 50}    -coord_2{100,50}
//create_square     -name{Square1}  -coord_1{45, 45}    -coord_2{150,150}

#endif // PARSER_H
