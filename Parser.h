#include "Lexer.h"
#include <vector>
#include <memory>
#include <stdexcept>

// AST 节点的头文件
#include "ASTNodes.h"

class Parser {
    std::vector<Token> tokens;  // 词法分析器生成的Token序列
    size_t current = 0;         // 当前Token的索引

public:
    explicit Parser(const std::vector<Token>& tokens);
    // 执行语法分析，返回AST根节点
    std::unique_ptr<ProgramNode> parse();   // 执行语法分析

private:
    std::unique_ptr<ProgramNode> program(); // 实现对应于文法中的 <程序>
    std::unique_ptr<ProgramHeaderNode> programHeader(); // 实现对应于文法中的 <程序头部>
    std::unique_ptr<BlockNode> block();     // 实现对应于文法中的 <分程序>

    std::unique_ptr<ConstDeclarationNode> constDeclaration();
    std::unique_ptr<VarDeclarationNode> varDeclaration();
    std::unique_ptr<StatementNode> statement();

    Token consume(TokenType type, const std::string& message);  // 消耗当前Token，如果类型不匹配则抛出异常
    bool match(TokenType type);     // 如果当前Token类型匹配，消耗当前Token并返回true，否则返回false
    bool check(TokenType type);     // 检查当前Token类型是否匹配
    Token advance();                // 消耗当前Token并返回
    bool isAtEnd();                 // 是否已经到达Token序列末尾
    void error(const Token& token, const std::string& message); // 抛出一个解析错误
};

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<ProgramNode> Parser::parse() {
    return program();
}

std::unique_ptr<ProgramNode> Parser::program() {
    auto header = programHeader();
    auto body = block();
    // ... 创建并返回程序节点，包含 header 和 body ...
    return std::make_unique<ProgramNode>(std::move(header), std::move(body));
}

std::unique_ptr<ProgramHeaderNode> Parser::programHeader() {
    consume(TokenType::PROGRAM, "Expect 'PROGRAM' at the beginning of program header.");
    Token identifier = consume(TokenType::IDENTIFIER, "Expect program name after 'PROGRAM'.");
    // ... 创建并返回程序头部节点，包含程序名 ...
    return std::make_unique<ProgramHeaderNode>(identifier.value);   // 词法分析器保证了程序名一定是一个标识符
}

std::unique_ptr<BlockNode> Parser::block() {
    // ... 实现对应于文法中的 <分程序> ...
    std::unique_ptr<ConstDeclarationNode> constDec = nullptr;
    std::unique_ptr<VarDeclarationNode> varDec = nullptr;
    std::vector<std::unique_ptr<StatementNode>> statements;

    if (match(TokenType::CONST)) {
        constDec = constDeclaration();
    }

    if (match(TokenType::VAR)) {
        varDec = varDeclaration();
    }

    while (!check(TokenType::BEGIN)) {
        statements.push_back(statement());
        match(TokenType::SEMICOLON); // 可能需要处理语句之间的分号
    }

    // 确保 'BEGIN' token 存在
    consume(TokenType::BEGIN, "Expect 'BEGIN' before statements.");

    // 处理语句直到 'END' token
    do {
        statements.push_back(statement());
    } while (!match(TokenType::END));

    // 返回构造的 BlockNode
    return std::make_unique<BlockNode>(std::move(constDec), std::move(varDec), std::move(statements));
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return advance();
    }
    throw std::runtime_error(message);
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return tokens[current].type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

bool Parser::isAtEnd() {
    return current >= tokens.size();
}

void Parser::error(const Token& token, const std::string& message) {
    // 抛出一个解析错误
    throw std::runtime_error("Error at [" + std::to_string(token.line) + ":" + std::to_string(token.column) + "]: " + message);
}

