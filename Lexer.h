// Lexer.h
/* 
* 词法分析器（Lexer）
* 使用Thompson算法实现词法分析功能
*/
#include <string>
#include <vector>
#include <regex>

enum class TokenType {
    PROGRAM, VAR, CONST, BEGIN, END, WHILE, DO, IF, THEN, IDENTIFIER, NUMBER,
    ASSIGN, EQUAL, NOT_EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL,
    PLUS, MINUS, MULTIPLY, DIVIDE, LEFT_PAREN, RIGHT_PAREN, SEMICOLON, COMMA,
    END_OF_FILE, INVALID
};

struct Token {
    TokenType type;     // Token类型
    std::string value;  // Token值
    int line;           // Token所在行号
    int column;         // Token所在列号
};

class Lexer {
    std::string source;     // 代码字符串
    size_t pos = 0;         // 当前字符位置
    int line = 1;           // 当前行号
    int column = 1;         // 当前列号
    std::vector<Token> tokens;

    // 增加一个用于映射保留关键字和TokenType的map
    const std::map<std::string, TokenType> keywords = {
        {"PROGRAM",     TokenType::PROGRAM},
        {"VAR",         TokenType::VAR},
        {"CONST",       TokenType::CONST},
        {"BEGIN",       TokenType::BEGIN},
        {"END",         TokenType::END},
        {"WHILE",       TokenType::WHILE},
        {"DO",          TokenType::DO},
        {"IF",          TokenType::IF},
        {"THEN",        TokenType::THEN},
        {"IDENTIFIER",  TokenType::IDENTIFIER},
        {"NUMBER",      TokenType::NUMBER},
        {"ASSIGN",      TokenType::ASSIGN},
        {"EQUAL",       TokenType::EQUAL},
        {"NOT_EQUAL",   TokenType::NOT_EQUAL},
        {"LESS",        TokenType::LESS},
        {"LESS_EQUAL",  TokenType::LESS_EQUAL},
        {"GREATER",     TokenType::GREATER},
        {"GREATER_EQUAL", TokenType::GREATER_EQUAL},
        {"PLUS",        TokenType::PLUS},
        {"MINUS",       TokenType::MINUS},
        {"MULTIPLY",    TokenType::MULTIPLY},
        {"DIVIDE",      TokenType::DIVIDE},
        {"LEFT_PAREN",  TokenType::LEFT_PAREN},
        {"RIGHT_PAREN", TokenType::RIGHT_PAREN},
        {"SEMICOLON",   TokenType::SEMICOLON},
        {"COMMA",       TokenType::COMMA},
        {"END_OF_FILE", TokenType::END_OF_FILE},
        {"INVALID",     TokenType::INVALID}
    };

public:
    Lexer(const std::string& src) : source(src) {}
    std::vector<Token> tokenize();
private:
    Token nextToken();
    enum class State {
        START,      // 初始状态
        IN_ASSIGN,  // 赋值符号
        IN_COMMENT, // 注释
        IN_NUM,     // 数字
        IN_ID,      // 标识符
        DONE        // 结束状态
    };
    State state = State::START;
    std::string tokenString;
    std::vector<Token> tokens;
    void ungetNextChar();
    void addToken(TokenType type, const std::string& value);
    void addToken(TokenType type);
    char advance();
    bool match(char expected);
    void skipWhitespace();
    void skipComment();
    bool isAtEnd() const;
    char peek() const;
    char peekNext() const;
};

Token Lexer::nextToken() {
    state = State::START;
    tokenString = "";
    char c;

    while (state != State::DONE) {
        c = source[pos++]; // 假设source是整个代码字符串，pos是当前字符位置
        switch (state) {
            case State::START:
            // ... 处理初始状态 ...
                // 情况1：当前字符是数字
                if (isdigit(c)) {
                    state = State::IN_NUM;
                    tokenString += c;
                }
                // 情况2：当前字符是字母
                else if (isalpha(c)) {
                    state = State::IN_ID;
                    tokenString += c;
                } 
                // 情况3：当前字符是冒号
                else if (c == ':') {
                    if (peek() == '=') {
                        tokenString += c;  // 这里我们得到了 ":=" 这个赋值符号
                        return Token{TokenType::ASSIGN, tokenString, line, column};
                    } else {
                        // 回退一个字符，因为我们已经读取了下一个字符但它不是 "="
                        ungetNextChar();
                        // 处理只有一个冒号的情况，比如它可能是一个错误的token
                        return Token{TokenType::INVALID, tokenString, line, column};
                        // 或者冒号本身在你的语言中是一个有效的token
                        // return Token{TokenType::COLON, tokenString, line, column};
                    }
                    break;
                }
                // 情况4：当前字符是其他符号
                else if (c == '<') {
                    if (peek() == '=') {
                        tokenString += c;
                        tokenString += advance();
                        return Token{TokenType::LESS_EQUAL, tokenString, line, column};
                    } else if (peek() == '>') {
                        tokenString += c;
                        tokenString += advance();
                        return Token{TokenType::NOT_EQUAL, tokenString, line, column};
                    } else {
                        tokenString += c;
                        return Token{TokenType::LESS, tokenString, line, column};
                    }
                }
                else if (c == '>') {
                    if (peek() == '=') {
                        tokenString += c;
                        tokenString += advance();
                        return Token{TokenType::GREATER_EQUAL, tokenString, line, column};
                    } else {
                        tokenString += c;
                        return Token{TokenType::GREATER, tokenString, line, column};
                    }
                }
                else if (c == '=') {
                    if (peek() == '=') {
                        tokenString += c;
                        tokenString += advance();
                        return Token{TokenType::EQUAL, tokenString, line, column};
                    } else {
                        tokenString += c;
                        return Token{TokenType::ASSIGN, tokenString, line, column};
                    }
                }
                else if (c == '!') {
                    if (peek() == '=') {
                        tokenString += c;
                        tokenString += advance();
                        return Token{TokenType::NOT_EQUAL, tokenString, line, column};
                    } else {
                        tokenString += c;
                        return Token{TokenType::INVALID, tokenString, line, column};
                    }
                }
                else if (c == '-') {
                    // 生成减号token
                    return Token{TokenType::MINUS, std::string(1, c), line, column};
                }
                else if (c == '*') {
                    // 生成乘号token
                    return Token{TokenType::MULTIPLY, std::string(1, c), line, column};
                }
                else if (c == '(') {
                    // 生成左括号token
                    return Token{TokenType::LEFT_PAREN, std::string(1, c), line, column};
                }
                else if (c == ')') {
                    // 生成右括号token
                    return Token{TokenType::RIGHT_PAREN, std::string(1, c), line, column};
                }
                else if (c == ';'){
                    // 生成分号token
                    return Token{TokenType::SEMICOLON, std::string(1, c), line, column};
                }
                else if (c == ',') {
                    // 生成逗号token
                    return Token{TokenType::COMMA, std::string(1, c), line, column};
                }
                else if (c == '+') {
                    // 生成加号token
                    return Token{TokenType::PLUS, std::string(1, c), line, column};
                }
                else if (c == '/') {
                    if (peek() == '/' || peek() == '*') { // 检查是否是注释
                        skipComment();
                    }
                    else {
                        // 生成除号token
                        return Token{TokenType::DIVIDE, std::string(1, c), line, column};
                    }
                }
                // 情况5：当前字符是空白字符
                else if (c == ' ' || c == '\t' || c == '\n') {
                    // 忽略空白字符
                    skipWhitespace();
                }
                // 情况6：当前字符是文件末尾
                else if (c == '\0') {
                    state = State::DONE;
                    // 生成END_OF_FILE token
                    return Token{TokenType::END_OF_FILE, tokenString, line, column};
                }
                // 情况7：当前字符是其他字符
                else {
                    state = State::DONE;
                    // 根据c生成单个字符的token
                }
                break;

            case State::IN_NUM:
                if (isdigit(c)) {
                    tokenString += c;
                } else {
                    // 生成NUMBER token，回退一个字符
                    ungetNextChar();
                    return Token{TokenType::NUMBER, tokenString};
                }
                break;

            case State::IN_ID:
                // 识别标识符，字母开头之后可以是字母或数字
                if (isalnum(c) || isdigit(c)) {
                    tokenString += c;
                } else {
                    // 生成IDENTIFIER token，回退一个字符
                    ungetNextChar();
                    // 检查是否为关键字
                    auto kw = keywords.find(tokenString);
                    if (kw != keywords.end()) {
                        return Token{kw->second, tokenString, line, column};
                    } else {
                        return Token{TokenType::IDENTIFIER, tokenString, line, column};
                    }
                }
                break;

            case State::IN_ASSIGN:
                if (c == '=') {
                    tokenString += c;
                    return Token{TokenType::ASSIGN, tokenString};
                } else {
                    // 回退一个字符，生成错误token或处理单独的冒号token
                    ungetNextChar();
                    // ...
                }
                break;

            // ... 添加其他状态的处理
            
            default:
                // 错误处理
                break;
        }
    }
    return Token{TokenType::END_OF_FILE, ""};
}

std::vector<Token> Lexer::tokenize() {
    Token token = nextToken();
    while (token.type != TokenType::END_OF_FILE) {
        tokens.push_back(token);
        token = nextToken();
    }
    return tokens;
}

void Lexer::ungetNextChar() {
    if (!source.empty()) {
        pos--;
    }
}

void Lexer::addToken(TokenType type, const std::string& value) {
    tokens.push_back({type, value, line, column});
}

void Lexer::addToken(TokenType type) {
    addToken(type, "");
}

char Lexer::advance() {
    column++; // 更新列号
    return source[pos++];
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source[pos] != expected) return false;
    pos++;
    column++; // 更新列号
    return true;
}

// 跳过空白字符
void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line++;
                column = 1;
                advance();
                break;
            default:
                return;
        }
    }
}

// 跳过注释
void Lexer::skipComment() {
    if (match('/')) {
        if (match('/')) {
            // 单行注释，跳过直到行末
            while (!isAtEnd() && peek() != '\n') {
                advance();
            }
        } else if (match('*')) {
            // 多行注释，跳过直到 '*/'
            while (!isAtEnd()) {
                if (peek() == '*' && peekNext() == '/') {
                    // 跳过结束的 '*/'
                    advance();
                    advance();
                    break;
                }
                if (peek() == '\n') {
                    line++;
                    column = 1;
                } else {
                    column++;
                }
                advance();
            }
        }
    }
}

// 判断是否到达代码末尾
bool Lexer::isAtEnd() const {
    return pos >= source.length();
}

// 查看下一个字符
char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[pos];
}

// 查看下一个字符的下一个字符
char Lexer::peekNext() const {
    if (pos + 1 >= source.length()) return '\0';
    return source[pos + 1];
}