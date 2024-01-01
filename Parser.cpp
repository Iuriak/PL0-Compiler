/**
 * 语法分析器（Parser）
 * 使用递归下降算法实现语法分析功能
 */
#include "Parser.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <map> 

//using namespace std;

map<string, string> idTable;    // 变量表
map<string, string> tempTable;  // 临时变量表
int tempVarNum = 0;             // 临时变量编号

vector<array<string, 4>> IR;    // 中间代码(三地址代码)
void storeIRCode(string op, string arg1, string arg2, string result) {
    IR.push_back({op, arg1, arg2, result});
};

string getTempVar(){
    while(idTable.find("TempVar"+to_string(tempVarNum)) != idTable.end()
        || tempTable.find("TempVar"+to_string(tempVarNum)) != tempTable.end()) {
        tempVarNum++;
    }
    tempTable.insert(pair<string, string>("TempVar"+to_string(tempVarNum), "Temp"));
    return "TempVar"+to_string(tempVarNum);
}

void Parser::output(std::ofstream &IRout, std::ofstream &ITout) {
    // 输出中间代码
    for(auto i : IR) {
        IRout << "(" << i[0] << " " << i[1] << " " << i[2] << ")" << " " << i[3] << endl;
    }
    // 输出变量表
    ITout << "name,type" << endl;
    for(auto i : idTable) {
        ITout << i.first << "," << i.second << endl;
    }
}

/**
 * program()方法
 * 实现对应于文法中的 <程序>
 * <程序>→<程序⾸部> <分程序>
*/
bool Parser::program() {
    try{
        programHeader();    //  <程序首部>
        block();            //  <分程序>
        return true;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return false;
}

/**
 * programHeader()方法
 * 实现对应于文法中的 <程序首部>
 * <程序⾸部>→PROGRAM <标识符>
*/
void Parser::programHeader() {
    nextToken();
    if(token.getType() != TokenType::PROGRAM) {
        error(token, "Expect 'PROGRAM' at the beginning of program header.");
    }
    nextToken();
    if(token.getType() != TokenType::IDENTIFIER) {
        error(token, "Expect program name after 'PROGRAM'.");
    }
    // 语义分析与中间代码生成
    // ...
}

/**
 * block()方法
 * 实现对应于文法中的 <分程序>
 * <分程序>→[<常量声明>][<变量声明>]<语句>
*/
void Parser::block() {
    nextToken();
    if(token.getType() == TokenType::CONST) {
        constDeclaration(); // <常量声明>
    }
    if(token.getType() == TokenType::VAR) {
        varDeclaration();   // <变量声明>
    }
    if(token.getType() == TokenType::END_OF_FILE) {
        return;             // <空语句>
    }
    statement();            // <语句>
    // 语义分析与中间代码生成

}

/**
 * constDeclaration()方法
 * 实现对应于文法中的 <常量声明>
 * <常量说明>→CONST <常量定义>{，<常量定义>} ; （注： { }中的项表⽰可重复若⼲次）
*/
void Parser::constDeclaration() {
    nextToken();
    if(token.getType() != TokenType::CONST) {
        error(token, "Expect 'CONST' at the beginning of const declaration.");
    }
    constDefinition();
    while(token.getType() == TokenType::COMMA) {
        constDefinition();
    }
    if(token.getType() != TokenType::SEMICOLON) {
        error(token, "Expect ';' at the end of const declaration.");
    }
    // 语义分析与中间代码生成
}

/**
 * constDefinition()方法
 * 实现对应于文法中的 <常量定义>
 * <常量定义>→<标识符>:=<⽆符号整数>
*/
void Parser::constDefinition(){
    nextToken();
    if(token.getType() != TokenType::IDENTIFIER) {
        error(token, "Expect identifier at the beginning of const definition.");
    }
    nextToken();
    if(token.getType() != TokenType::ASSIGN) {
        error(token, "Expect ':=' in const definition.");
    }
    nextToken();
    if(token.getType() != TokenType::NUMBER) {
        error(token, "Expect number in const definition.");
    }
    idTable.insert(pair<string, string>(token.getValue(), "const")); // 将常量加入变量表
    int value = std::stoi(token.getValue());    // 获取常量值
    // 语义分析与中间代码生成
}

/**
 * varDeclaration()方法
 * 实现对应于文法中的 <变量声明>
 * <变量说明>→VAR<标识符>{，<标识符>};
*/
void Parser::varDeclaration() {
    nextToken();
    if(token.getType() != TokenType::VAR) {
        error(token, "Expect 'VAR' at the beginning of var declaration.");
    }
    idTable.insert(pair<string, string>(token.getValue(), "var")); // 将变量加入变量表
    nextToken();
    if(token.getType() != TokenType::IDENTIFIER) {
        error(token, "Expect identifier in var declaration.");
    }
    while(token.getType() == TokenType::COMMA) {
        nextToken();
        if(token.getType() != TokenType::IDENTIFIER) {
            error(token, "Expect identifier in var declaration.");
        }
        idTable.insert(pair<string, string>(token.getValue(), "var")); // 将变量加入变量表
    }
    if(token.getType() != TokenType::SEMICOLON) {
        error(token, "Expect ';' at the end of var declaration.");
    }
    // 语义分析与中间代码生成
}

/**
 * statement()方法
 * 实现对应于文法中的 <语句>
 * <语句>→<赋值语句> | <条件语句 >| <循环语句> | <复合语句> | <空语句>
*/
void Parser::statement() {
    nextToken();
    switch(token.getType()) {
        case TokenType::IDENTIFIER:
            assignmentStatement();  // <赋值语句>
            break;
        case TokenType::IF:
            conditionStatement();   // <条件语句>
            break;
        case TokenType::WHILE:
            cyclicStatement();      // <循环语句>
            break;
        case TokenType::BEGIN:
            compoundStatement();    // <复合语句>
            break;
        case TokenType::SEMICOLON:
        case TokenType::END:
            //voidStatement();       // <空语句>
            break;
        default:
            error(token, "Expect statement.");
    }
}


/**
 * assignmentStatement()方法
 * 实现对应于文法中的 <赋值语句>
 * <赋值语句>→<标识符>:=<表达式>
*/
void Parser::assignmentStatement(){
    // token 指向 IDENTIFIER
    nextToken();
    if(token.getType() != TokenType::ASSIGN) {
        error(token, "Expect ':=' in assignment statement.");
    }
    string exp = expression();   // <表达式>
    // 语义分析与中间代码生成
    if(idTable.find(token.getValue()) == idTable.end()) {
        error(token, "Identifier not declared.");
    } else{
        string arg1 = exp;
        string arg2 = "_";
        string result = token.getValue();
        storeIRCode(":=", arg1, arg2, result);  // 生成中间代码
    }
}

/**
 * conditionStatement()方法
 * 实现对应于文法中的 <条件语句>
 * <条件语句>→IF<条件>THEN<语句>
*/
void Parser::conditionStatement(){
    // token 指向 IF
    auto [orp, arg1, arg2] = condition();    // <条件>
    // 生成中间代码
    auto label1 = IR.size();    
    storeIRCode("j"+orp, arg1, arg2, "M");
    auto label2 = IR.size();
    storeIRCode("j", "_", "_", "M");
    nextToken();
    // token 指向 THEN
    if(token.getType() != TokenType::THEN) {
        error(token, "Expect 'THEN' in condition statement.");
    }
    nextToken();
    IR[label1][3] = to_string(IR.size());
    statement();    // <语句>
    IR[label2][3] = to_string(IR.size());
    // 语义分析与中间代码生成
}

/**
 * cyclicStatement()方法
 * 实现对应于文法中的 <循环语句>
 * <循环语句>→WHILE <条件> DO <语句>
*/
void Parser::cyclicStatement(){
    // token 指向 WHILE
    auto [orp, arg1, arg2] = condition();    // <条件>
    // 生成中间代码
    auto label1 = IR.size();
    storeIRCode("j"+orp, arg1, arg2, "M");
    auto label2 = IR.size();
    storeIRCode("j", "_", "_", "M");
    nextToken();
    // token 指向 DO
    if(token.getType() != TokenType::DO) {
        error(token, "Expect 'DO' in cyclic statement.");
    }
    nextToken();
    IR[label1][3] = to_string(IR.size());
    statement();    // <语句>
    storeIRCode("j", "_", "_", to_string(label1));
    IR[label2][3] = to_string(IR.size());
    // 语义分析与中间代码生成
}

/**
 * compoundStatement()方法
 * 实现对应于文法中的 <复合语句>
 * <复合语句>→BEGIN <语句>{; <语句>} END
*/
void Parser::compoundStatement(){
    // token 指向 BEGIN
    statement();    // <语句>
    nextToken();
    while(1) {
        if(token.getType() == TokenType::SEMICOLON) {
            nextToken();
            // 一个语句已经结束，且后面可能跟着另一个语句或者空语句。
        } else {
            if(token.getType() != TokenType::END) {
                // 当前处于嵌套的复合语句中，需要重置Flag
                if(conpoundStatementFlag) {
                    conpoundStatementFlag = false;
                }
                // 结束嵌套的复合语句
                else {
                    conpoundStatementFlag = true;
                    break;
                }
            }
            nextToken();
            if(token.getType() == TokenType::SEMICOLON) {
                nextToken();
            }
            else if(token.getType() == TokenType::END) {
                conpoundStatementFlag = true;
                break;
            }
            else {
                error(token, "Expect ';' or 'END' in compound statement.");
            }
        }
        statement();    // <语句>
    }
    // 结束条件：token 指向 END，且conpoundStatementFlag为true
    // 语义分析与中间代码生成
}

/**
 * expression()方法
 * 实现对应于文法中的 <表达式>
 * <表达式>→[+|-]项 | <表达式> <加法运算符> <项>
 * <加法运算符>→ + | -
*/
string Parser::expression(){
    // 正负号
    bool negative =false;
	nextToken();
	if (token.getType() == TokenType::PLUS || token.getType() == TokenType::MINUS) {
		// 语义处理
		negative = true;
		nextToken();
	}
    string result = term(); // <项>
    while(token.getType() == TokenType::PLUS || token.getType() == TokenType::MINUS) {
        string temp = getTempVar();    // 临时变量
        string op = token.getValue();   // <加法运算符>
        string arg1 = result;
        nextToken();
        string arg2 = term();   // <项>
        storeIRCode(op, arg1, arg2, temp);  // 生成中间代码
        result = temp;
        // 语义分析与中间代码生成

    }
    return result;
}

/**
 * term()方法
 * 实现对应于文法中的 <项>
 * <项>→<因子>{<乘法运算符><因子>}
 * 或者 <项>→<因⼦> | <项><乘法运算符> <因⼦>
 * <乘法运算符>→*|/
*/
string Parser::term(){
    string result = factor();   // <因子>
    nextToken();
    while(token.getType() == TokenType::MULTIPLY || token.getType() == TokenType::DIVIDE) {
        string temp = getTempVar();    // 临时变量
        string op = token.getValue();   // <乘法运算符>
        string arg1 = result;
        nextToken();
        string arg2 = factor();   // <因子>
        storeIRCode(op, arg1, arg2, temp);  // 生成中间代码
        result = temp;
        nextToken();
        // 语义分析与中间代码生成
    }
    return result;
}

/**
 * factor()方法
 * 实现对应于文法中的 <因子>
 * <因子>→<标识符> | <无符号整数> | (<表达式>)
*/
string Parser::factor(){
    string result;
    switch(token.getType()) {
        case TokenType::IDENTIFIER:
            if(idTable.find(token.getValue()) == idTable.end()) {
                error(token, "Identifier not declared.");
            } else{
                result = token.getValue();
            }
            break;
        case TokenType::NUMBER:
            result = token.getValue();
            break;
        case TokenType::LEFT_PAREN:
            result = expression();  // <表达式>
            nextToken();
            if(token.getType() != TokenType::RIGHT_PAREN) {
                error(token, "Expect ')' in factor.");
            }
            break;
        default:
            error(token, "Expect factor.");
    }
    return result;
}

/*Token Parser::consume(TokenType type, const std::string& message) {
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
*/
/*void Parser::error(const Token& token, const std::string& message) {
    // 抛出一个解析错误
    throw std::runtime_error("Error at [" + std::to_string(token.line) + ":" + std::to_string(token.column) + "]: " + message);
}
*/
