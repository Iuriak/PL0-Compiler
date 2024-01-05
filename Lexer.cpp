#include <string>
#include <vector>
#include <regex>
#include "Lexer.h"

/**
 * 词法分析器（Lexer）
 */

/**
 * nextToken()方法
 *
 * */
Token Lexer::nextToken()
{
    // state = State::START;
    tokenString = "";
    char ch;

    while (pos < source.length()) // state != State::DONE)
    {
        ch = source[pos]; // source是整个代码字符串，pos是当前字符位置
        switch (state)
        {
        case State::START:
            // ... 处理初始状态 ...
            // 情况1：当前字符是数字
            if (isdigit(ch))
            {
                read();
                state = State::IN_NUM;
                tokenString += ch;
            }
            // 情况2：当前字符是字母
            else if (isalpha(ch))
            {
                read();
                state = State::IN_ID;
                tokenString += ch;
            }
            // 情况3：当前字符是空白字符
            else if (isspace(ch))
            {
                // 忽略空白字符
                skipWhitespace();
            }
            // 情况4：当前字符是注释
            else if (ch == '/')
            {
                bool devide = skipComment();
                if (devide)
                {
                    state = State::START;
                    return Token(TokenType::DIVIDE, "/");
                }
            }
            // 情况5：当前字符是文件末尾
            else if (ch == '\0')
            {
                state = State::DONE;
                // 生成END_OF_FILE token
                return Token(TokenType::END_OF_FILE, tokenString);
            }
            // 情况6：当前字符是其他字符
            else
            {
                return handleSymbol();
            }
            break;

        case State::IN_NUM:
            if (isdigit(ch))
            {
                read();
                tokenString += ch;
            } else if(isalpha(ch))  // 数字后面跟字母，报错
            {
                read();
                tokenString += ch;
                state = State::IN_ERROR;
                return Token{TokenType::INVALID, tokenString};
            } else
            {
                state = State::START;
                return Token{TokenType::NUMBER, tokenString};
            }
            break;

        case State::IN_ID:
            // 识别标识符，字母开头之后可以是字母或数字
            if (isalnum(ch) || isdigit(ch))
            {
                read();
                tokenString += ch;
                if(pos == source.length())
                {
                    state = State::START;
                    if(tokenString == "END")
                        return Token(TokenType::END, tokenString);
                    else if(tokenString == "IF")
                        return Token(TokenType::IF, tokenString);
                    else if(tokenString == "THEN")
                        return Token(TokenType::THEN, tokenString);
                    else if(tokenString == "WHILE")
                        return Token(TokenType::WHILE, tokenString);
                    else if(tokenString == "DO")
                        return Token(TokenType::DO, tokenString);
                    else if(tokenString == "BEGIN")
                        return Token(TokenType::BEGIN, tokenString);
                    else if(tokenString == "END")
                        return Token(TokenType::END, tokenString);
                    else if(tokenString == "VAR")
                        return Token(TokenType::VAR, tokenString);
                    else if(tokenString == "CONST")
                        return Token(TokenType::CONST, tokenString);
                    else
                        return Token(TokenType::IDENTIFIER, tokenString);
                }
            }
            else
            {
                state = State::START;
                // 检查是否为关键字
                std::string upperValue = tokenString;
                auto kw = keywords.find(upperValue);
                if (kw != keywords.end())
                {
                    return Token(kw->second, upperValue);
                }
                else
                {
                    return Token(TokenType::IDENTIFIER, tokenString);
                }
            }
            break;

        // 处理 :=
        case State::IN_ASSIGN:
            // 处理赋值符号
            if (ch == '=')
            {
                read();
                tokenString += ch;
                state = State::START;
                return Token{TokenType::ASSIGN, tokenString};
            }
            else
            {
                state = State::START;
                return Token{TokenType::INVALID, tokenString};
            }
            break;

        // 处理<, <=, <>
        case State::IN_LESS:
            if (ch == '=')
            {
                read();
                tokenString += ch;
                state = State::START;
                return Token{TokenType::LESS_EQUAL, tokenString};
            }
            else if (ch == '>')
            {
                read();
                tokenString += ch;
                state = State::START;
                return Token{TokenType::NOT_EQUAL, tokenString};
            }
            else
            {
                state = State::START;
                return Token{TokenType::LESS, tokenString};
            }
            break;
        // 处理>, >=
        case State::IN_GREATER:
            if (ch == '=')
            {
                read();
                tokenString += ch;
                state = State::START;
                return Token{TokenType::GREATER_EQUAL, tokenString};
            }
            else
            {
                state = State::START;
                return Token{TokenType::GREATER, tokenString};
            }
            break;
        default:
            // 错误处理
            throw std::runtime_error("Lexer Error: Invalid State");
        }
    }
    return Token(TokenType::END_OF_FILE, "");
}

Token Lexer::handleSymbol()
{
    char ch = source[pos];
    read();
    switch (ch)
    {
    case '+':
        return Token(TokenType::PLUS, "+");
    case '-':
        return Token(TokenType::MINUS, "-");
    case '*':
        return Token(TokenType::MULTIPLY, "*");
    //case '/':
        /*
        if (source[pos] == '/')
        {
            // 单行注释，跳过直到行末
            while (!isAtEnd() && peek() != '\n')
            {
                read();
            }
        }
        else if (source[pos] == '*')
        {
            // 多行注释，跳过直到 '*
            while (!isAtEnd())
            {
                if (peek() == '*' && peekNext() == '/')
                {
                    // 跳过结束的 '*
                    read();
                    read();
                    break;
                }
                if (peek() == '\n')
                {
                    line++;
                    column = 1;
                }
                else
                {
                    column++;
                }
                read();
            }
        }
        else*/
        //return Token(TokenType::DIVIDE, "/");
    case '(':
        return Token(TokenType::LEFT_PAREN, "(");
    case ')':
        return Token(TokenType::RIGHT_PAREN, ")");
    case ';':
        return Token(TokenType::SEMICOLON, ";");
    case ',':
        return Token(TokenType::COMMA, ",");
    case ':':
        if (source[pos] == '=')
        {
            read();
            return Token(TokenType::ASSIGN, ":=");
        }
        else
        {
            return Token(TokenType::INVALID, ":");
        }
    case '<':
        if (source[pos] == '=')
        {
            read();
            return Token(TokenType::LESS_EQUAL, "<=");
        }
        else if (source[pos] == '>')
        {
            read();
            return Token(TokenType::NOT_EQUAL, "<>");
        }
        else
        {
            return Token(TokenType::LESS, "<");
        }
    case '>':
        if (source[pos] == '=')
        {
            read();
            return Token(TokenType::GREATER_EQUAL, ">=");
        }
        else
        {
            return Token(TokenType::GREATER, ">");
        }
    case '=':
        if (source[pos] == '=')
        {
            read();
            return Token(TokenType::EQUAL, "==");
        }
        else
        {
            return Token(TokenType::ASSIGN, "=");
        }
    case '!':
        if (source[pos] == '=')
        {
            read();
            return Token(TokenType::NOT_EQUAL, "!=");
        }
        else
        {
            return Token(TokenType::INVALID, "!");
        }
    default:
        return Token(TokenType::INVALID, std::string(1, ch));
    }
}
/*
std::vector<Token> Lexer::tokenize()
{
    Token token = nextToken();
    while (token.type != TokenType::END_OF_FILE)
    {
        tokens.push_back(token);
        token = nextToken();
    }
    return tokens;
}

void Lexer::ungetNextChar()
{
    if (!source.empty())
    {
        pos--;
    }
}

void Lexer::addToken(TokenType type, const std::string &value)
{
    tokens.push_back({type, value, line, column});
}

void Lexer::addToken(TokenType type)
{
    addToken(type, "");
}
*/
void Lexer::read()
{
    if (source[pos] == '\n')
    {
        line++;
        column = 1;
    }
    else
    {
        column++;
    }
    pos++;
}

bool Lexer::match(char expected)
{
    if (isAtEnd())
        return false;
    if (source[pos] != expected)
        return false;
    pos++;
    column++; // 更新列号
    return true;
}

// 跳过空白字符
void Lexer::skipWhitespace()
{
    while (!isAtEnd())
    {
        char ch = peek();
        switch (ch)
        {
        case ' ':
        case '\r':
        case '\t':
            column++;
            break;
        case '\n':
            line++;
            column = 1;
            break;
        default:
            return;
        }
        pos++;
    }
    state = State::START;
}

// 跳过注释
bool Lexer::skipComment()
{
    bool devide = true;
    if (match('/'))
    {
        if (match('/'))
        {
            devide = false;
            // 单行注释，跳过直到行末
            while (!isAtEnd() && peek() != '\n')
            {
                read();
            }
        }
        else if (match('*'))
        {   
            devide = false;
            // 多行注释，跳过直到 '*/'
            while (!isAtEnd())
            {
                if (peek() == '*' && peekNext() == '/')
                {
                    // 跳过结束的 '*/'
                    read();
                    read();
                    break;
                }
                if (peek() == '\n')
                {
                    line++;
                    column = 1;
                }
                else
                {
                    column++;
                }
                read();
            }
        }
    }
    return devide;
}

// 判断是否到达代码末尾
bool Lexer::isAtEnd() const
{
    return pos >= source.length();
}

// 查看下一个字符
char Lexer::peek() const
{
    if (isAtEnd())
        return '\0';
    return source[pos];
}

// 查看下一个字符的下一个字符
char Lexer::peekNext() const
{
    if (pos + 1 >= source.length())
        return '\0';
    return source[pos + 1];
}