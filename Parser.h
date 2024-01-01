/**Parser.h
 * 语法分析器（Parser）
 * 使用递归下降算法实现语法分析功能
 */
#pragma once

#include "Lexer.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <map>
using namespace std;
class Parser
{
public:
    // 构造函数
    Parser(Lexer &lexer) { this->lexer = &lexer; };
    // 析构函数
    ~Parser(){};
    // 执行语法分析
    bool program();             // 实现对应于文法中的 <程序>
    // 输出语法树
    void output(std::ofstream &IRout, std::ofstream &ITout);

private:
    Token token;                                        // 词法分析器获取的当前Token
    Lexer *lexer;                                       // 词法分析器
    bool conpoundStatementFlag = false;                 // 复合语句标志
    void nextToken(){ token = lexer->nextToken(); }     // 获取下一个Token

    void programHeader();       // 实现对应于文法中的 <程序首部>
    void block();               // 实现对应于文法中的 <分程序>

    void constDeclaration();   // 实现对应于文法中的 <常量声明>
    void constDefinition();    // 实现对应于文法中的 <常量定义>
    void varDeclaration();     // 实现对应于文法中的 <变量声明>
    
    void statement();          // 实现对应于文法中的 <语句>
    void assignmentStatement();// 实现对应于文法中的 <赋值语句>
    void conditionStatement(); // 实现对应于文法中的 <条件语句>
    void cyclicStatement();     // 实现对应于文法中的 <当型循环语句>
    void compoundStatement();  // 实现对应于文法中的 <复合语句>
    void voidStatement();      // 实现对应于文法中的 <空语句>
    
    string expression();         // 实现对应于文法中的 <表达式>
    string term();               // 实现对应于文法中的 <项>
    string factor();             // 实现对应于文法中的 <因子>
    // 实现对应于文法中的 <条件>
    // <条件>→<表达式> <关系运算符> <表达式>
    // <关系运算符>→ = | <> | < | <= | > | >=
    array<string, 3> condition();   // 实现对应于文法中的 <条件>

    Token consume(TokenType type, const std::string &message);  // 消耗当前Token，如果类型不匹配则抛出异常
    bool match(TokenType type);                                 // 如果当前Token类型匹配，消耗当前Token并返回true，否则返回false
    bool check(TokenType type);                                 // 检查当前Token类型是否匹配
    Token advance();                                            // 消耗当前Token并返回
    bool isAtEnd();                                             // 是否已经到达Token序列末尾
    void error(const Token &token, const std::string &message); // 抛出一个解析错误
};
