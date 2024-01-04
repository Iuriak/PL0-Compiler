/**Lexer.h
 * 词法分析器（Lexer）
 * 使用Thompson算法实现词法分析功能
 */

#pragma once

#include <string>
#include <vector>
#include <regex>

using namespace std;

/**
 * Token类型
 * */
enum TokenType
{
    PROGRAM,
    VAR,
    CONST,
    BEGIN,
    END,
    WHILE,
    DO,
    IF,
    THEN,
    IDENTIFIER,
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMICOLON,
    COMMA,
    END_OF_FILE,
    INVALID
};

/**
 * Token类
 */
class Token
{
public:
    Token(TokenType type, std::string value) : type(type), value(value) {}
    Token(TokenType type, std::string value, int line, int column) : type(type), value(value), line(line), column(column) {}
    Token() : type(TokenType::INVALID), value("") {}
    TokenType getType() const { return type; }
    string getValue() const { return value; }
    int getLine() const { return line; }
    int getColumn() const { return column; }
    void setLine(int line) { this->line = line; }
    void setColumn(int column) { this->column = column; }

private:
    TokenType type;    // Token类型
    string value; // Token值
    int line = 1;     // Token所在行号
    int column = 1;   // Token所在列号
};

/**
 * 词法分析器类
 */
class Lexer
{
    std::string source; // 代码字符串
    size_t pos = 0;     // 当前字符位置
    int line = 1;       // 当前行号
    int column = 1;     // 当前列号
    vector<Token> tokens;

    // 增加一个用于映射保留关键字和TokenType的map
    const std::map<std::string, TokenType> keywords = {
        {"PROGRAM", TokenType::PROGRAM},
        {"VAR", TokenType::VAR},
        {"CONST", TokenType::CONST},
        {"BEGIN", TokenType::BEGIN},
        {"END", TokenType::END},
        {"WHILE", TokenType::WHILE},
        {"DO", TokenType::DO},
        {"IF", TokenType::IF},
        {"THEN", TokenType::THEN},
        {"IDENTIFIER", TokenType::IDENTIFIER},
        {"NUMBER", TokenType::NUMBER},
        {"ASSIGN", TokenType::ASSIGN},
        {"EQUAL", TokenType::EQUAL},
        {"NOT_EQUAL", TokenType::NOT_EQUAL},
        {"LESS", TokenType::LESS},
        {"LESS_EQUAL", TokenType::LESS_EQUAL},
        {"GREATER", TokenType::GREATER},
        {"GREATER_EQUAL", TokenType::GREATER_EQUAL},
        {"PLUS", TokenType::PLUS},
        {"MINUS", TokenType::MINUS},
        {"MULTIPLY", TokenType::MULTIPLY},
        {"DIVIDE", TokenType::DIVIDE},
        {"LEFT_PAREN", TokenType::LEFT_PAREN},
        {"RIGHT_PAREN", TokenType::RIGHT_PAREN},
        {"SEMICOLON", TokenType::SEMICOLON},
        {"COMMA", TokenType::COMMA},
        {"END_OF_FILE", TokenType::END_OF_FILE},
        {"INVALID", TokenType::INVALID}};

public:
    Lexer(const std::string &src) : source(src), pos(0), line(1), column(1) {}
    std::vector<Token> tokenize();
    Token nextToken();  // 获取下一个Token
    int getLine() const { return line; }        // 获取当前行号
    int getColumn() const { return column; }    // 获取当前列号
    char peek() const;      // 预读下一个字符
    char peekNext() const;  // 预读下下个字符
private:
    enum class State    // 词法分析器状态
    {
        START,      // 初始状态
        IN_ASSIGN,  // 赋值符号
        IN_COMMENT, // 注释
        IN_NUM,     // 数字
        IN_ID,      // 标识符
        IN_LESS,    // 小于号
        IN_GREATER, // 大于号
        IN_ERROR,   // 错误状态
        DONE        // 结束状态
    };
    State state = State::START; // 当前状态
    string tokenString;
    // vector<Token> tokens;
    Token handleSymbol();
    //void ungetNextChar();
    //void addToken(TokenType type, const std::string &value);
    //void addToken(TokenType type);
    void read();
    bool match(char expected);
    void skipWhitespace();
    bool skipComment();
    bool isAtEnd() const;
};