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

using namespace std;
struct Identifier {
    string type;
    string value;
    bool initialized;

    Identifier() : type(""), value("null"), initialized(false) {} // 默认构造函数
    Identifier(string type, string value) : type(type), value(value) {} // 自定义构造函数
};

map<string, Identifier> idTable;    // 变量表<id, Identifier>
map<string, string> tempTable;  // 临时变量表
int tempVarNum = 1;             // 临时变量编号
int base_addr = 100;            // 变量基地址

vector<array<string, 4>> IR;    // 中间代码(三地址代码)
void storeIRCode(string op, string arg1, string arg2, string result) {
    IR.push_back({op, arg1, arg2, result});
};

string getTempVar(){
    while(idTable.find("T"+to_string(tempVarNum)) != idTable.end()
        || tempTable.find("T"+to_string(tempVarNum)) != tempTable.end()) {
        tempVarNum++;
    }
    tempTable.insert(pair<string, string>("T"+to_string(tempVarNum), "Temp"));
    return "T"+to_string(tempVarNum);
}

void Parser::output(std::ofstream &IRout, std::ofstream &ITout) {
    // 输出中间代码
    int ord = base_addr;
    for(auto i : IR) {
        IRout << ord++ << " (" << i[0] << ", " << i[1] << ", " << i[2] << ", " << i[3] << ")" << endl;
    }
    // 输出变量表
    ITout << "Identifier,Type,Value" << endl;
    for(auto &entry : idTable) {
        ITout << entry.first << "," << entry.second.type << "," << entry.second.value << endl;
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
        storeIRCode("END", "_", "_", "_");
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
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    nextToken();
    if(token.getType() != TokenType::PROGRAM) {
        error(tempToken, "Expect 'PROGRAM' at the beginning of program header.");
    }
    tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    nextToken();
    if(token.getType() != TokenType::IDENTIFIER) {
        error(tempToken, "Expect program name after 'PROGRAM'.");
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
        nextToken();
    }
    if(token.getType() == TokenType::VAR) {
        varDeclaration();   // <变量声明>
        nextToken();
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
    // token 指向 CONST
    constDefinition();
    nextToken();
    while(token.getType() == TokenType::COMMA) {
        constDefinition();
        nextToken();
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
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    nextToken();
    string id = token.getValue();   // <标识符>
    if(token.getType() == TokenType::INVALID) {
        error(tempToken, "Invalid identifier '"+token.getValue()+"'. Identifiers must begin with a letter.");
    }
    if(token.getType() != TokenType::IDENTIFIER) {
        error(tempToken, "Expect identifier at the beginning of const definition.");
    }
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());
    nextToken();
    if(token.getType() != TokenType::ASSIGN) {
        error(tempToken, "Expect ':=' in const definition.");
    }
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());
    // 正负号
    //bool sign_MINUS =false;
    //string op_PLUS_MINUS;
	nextToken();
    /*
	if (token.getType() == TokenType::PLUS || token.getType() == TokenType::MINUS) {
		// 语义处理
        op_PLUS_MINUS = token.getValue();   // <加法运算符>
        if(op_PLUS_MINUS == "-")
		    sign_MINUS = true;
		nextToken();
	}
    if(token.getType() != TokenType::NUMBER) {
        error(tempToken, "Expect number in const definition.");
    }
    if(sign_MINUS) {
        idTable[id] = Identifier("const", op_PLUS_MINUS + token.getValue()); // 将常量加入变量表
    } else {
        idTable[id] = Identifier("const", token.getValue()); // 将常量加入变量表
    }*/
    idTable[id] = Identifier("const", token.getValue()); // 将常量加入变量表
    idTable[id].initialized = true; // 常量已经初始化
    //idTable.insert(pair<string, string>(token.getValue(), "const")); // 将常量加入变量表
    int value = std::stoi(token.getValue());    // 获取常量值
    // 语义分析与中间代码生成
}

/**
 * varDeclaration()方法
 * 实现对应于文法中的 <变量声明>
 * <变量说明>→VAR<标识符>{，<标识符>};
*/
void Parser::varDeclaration() {
    // token 指向 VAR
    /*nextToken();
    if(token.getType() != TokenType::VAR) {
        error(token, "Expect 'VAR' at the beginning of var declaration.");
    }*/
    //idTable.insert(pair<string, string>(token.getValue(), "var")); // 将变量加入变量表
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());
    nextToken();
    if(token.getType() == TokenType::INVALID) {
        error(tempToken, "Invalid identifier '"+token.getValue()+"'. Identifiers must begin with a letter.");
    }
    if(token.getType() != TokenType::IDENTIFIER) {
        error(tempToken, "Expect identifier in var declaration.");
    }
    idTable[token.getValue()] = Identifier("var", "null"); // 将变量加入变量表
    //idTable.insert(pair<string, string>(token.getValue(), "var")); // 将变量加入变量表
    
    tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    nextToken();
    if(token.getType() != TokenType::COMMA && token.getType() != TokenType::SEMICOLON) {
        error(tempToken, "Expect ',' or ';' in var declaration.");
    }

    while(token.getType() == TokenType::COMMA) {
        tempToken = token;
        tempToken.setColumn(lexer->getColumn());
        tempToken.setLine(lexer->getLine());
        nextToken();
        if(token.getType() != TokenType::IDENTIFIER) {
            error(token, "Expect identifier in var declaration.");
        }
        idTable[token.getValue()] = Identifier("var", "null"); // 将变量加入变量表
        // idTable.insert(pair<string, string>(token.getValue(), "var")); // 将变量加入变量表
        tempToken = token;
        tempToken.setColumn(lexer->getColumn());
        tempToken.setLine(lexer->getLine());
        nextToken();
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
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

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
            // <空语句>
            break;
        case TokenType::END:
            // <空语句>
            break;
        case TokenType::END_OF_FILE:
            // <空语句>
            break;
        default:
            error(tempToken, "Expect statement.");
    }
}


/**
 * assignmentStatement()方法
 * 实现对应于文法中的 <赋值语句>
 * <赋值语句>→<标识符>:=<表达式>
*/
void Parser::assignmentStatement(){
    // token 已经指向 IDENTIFIER
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    string id = token.getValue();   // <标识符>
    nextToken();
    if(token.getType() != TokenType::ASSIGN) {
        error(tempToken, "Expect ':=' in assignment statement.");
    }
    tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    string exp = expression();   // <表达式>
    /*if(token.getType() != TokenType::SEMICOLON) {
        error(tempToken, "Expect ';' at the end of assignment statement.");
    }*/
    // 语义分析与中间代码生成
    if(idTable.find(id) == idTable.end()) {
        error(tempToken, "Identifier '"+ id +"' not declared.");
    } else{
        string arg1 = exp;
        string arg2 = "_";
        string result = id;
        storeIRCode(":=", arg1, arg2, result);  // 生成中间代码
        idTable[id].value = exp;
        idTable[id].initialized = true;
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
    string temp_IF = getTempVar();          // 临时变量代替条件表达式的值
    storeIRCode(orp, arg1, arg2, temp_IF);

    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    auto label2 = IR.size();
    storeIRCode("JUMPFALSE", temp_IF, "_", "M");
    // token 此时应该指向 THEN
    if(token.getType() != TokenType::THEN) {
        error(tempToken, "Expect 'THEN' in condition statement.");
    }
    nextToken();
    statement();    // <语句>
    IR[label2][3] = to_string(IR.size()+base_addr);

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
    string temp_WHILE = getTempVar();          // 临时变量代替条件表达式的值
    storeIRCode(orp, arg1, arg2, temp_WHILE);

    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());

    auto label2 = IR.size();
    storeIRCode("JUMPFALSE", temp_WHILE, "_", "M");
    // token 指向 DO
    if(token.getType() != TokenType::DO) {
        error(tempToken, "Expect 'DO' in cyclic statement.");
    }
    nextToken();
    // IR[label1][3] = to_string(IR.size());
    statement();    // <语句>
    storeIRCode("JUMP", "_", "_", to_string(label1 + base_addr));
    IR[label2][3] = to_string(IR.size() + base_addr);
    // 语义分析与中间代码生成
}

/**
 * compoundStatement()方法
 * 实现对应于文法中的 <复合语句>
 * <复合语句>→BEGIN <语句>{; <语句>} END
*/
void Parser::compoundStatement(){
    // token 已经指向 BEGIN
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());
    nextToken();
    if(token.getType() == TokenType::END_OF_FILE)
        error(tempToken, "Expect 'END' in compound statement.");
    /*
    if(token.getType() != TokenType::END_OF_FILE) {
        if(token.getType() != TokenType::END) {
            if(token.getType() != TokenType::IDENTIFIER && token.getType() != TokenType::IF
                && token.getType() != TokenType::WHILE && token.getType() != TokenType::BEGIN) {
                error(tempToken, "Expect statement in compound statement.");
            }
        }
        else {
            error(tempToken, "Expect statement in compound statement.");
        }
    }
    else {
        error(tempToken, "Expect 'END' in compound statement.");
    }*/
    statement();    // <语句>
    while(1) {
        if(token.getType() == TokenType::SEMICOLON) {
            tempToken = token;
            tempToken.setColumn(lexer->getColumn());
            tempToken.setLine(lexer->getLine());
            nextToken();
            if(token.getType() == TokenType::END) {
                error(tempToken, "Unexpect ';' in compound statement.");
            }
            // 一个语句已经结束，且后面可能跟着另一个语句或者空语句。
        } else {
            tempToken = token;
            tempToken.setColumn(lexer->getColumn());
            tempToken.setLine(lexer->getLine());
            if(token.getType() == TokenType::END) {
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
            else if(token.getType() == TokenType::END_OF_FILE){
                error(tempToken, "Expect 'END' in compound statement.");
            }
            else if(token.getType() != TokenType::SEMICOLON) {
                error(tempToken, "Expect ';' before this statement.");
            }
            nextToken();
            if(token.getType() == TokenType::SEMICOLON) {
                tempToken = token;
                tempToken.setColumn(lexer->getColumn());
                tempToken.setLine(lexer->getLine());
                nextToken();
            }
            else if(token.getType() == TokenType::END) { //   || token.getType() == TokenType::END_OF_FILE
                conpoundStatementFlag = true;
                break;
            }
            else {
                error(tempToken, "Expect 'END' in compound statement.");
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
    bool sign_MINUS =false;
    string op_PLUS_MINUS;
	nextToken();
	if (token.getType() == TokenType::PLUS || token.getType() == TokenType::MINUS) {
		// 语义处理
        op_PLUS_MINUS = token.getValue();   // <加法运算符>
        if(op_PLUS_MINUS == "-")
		    sign_MINUS = true;
		nextToken();
	}
    string result = term(); // <项>
    if(sign_MINUS) {
        result = op_PLUS_MINUS + result;
    }
    
    while(token.getType() == TokenType::PLUS || token.getType() == TokenType::MINUS) {
        string temp = getTempVar();    // 临时变量
        string op = token.getValue();   // <加法运算符>
        string arg1 = result;

        // 正负号
        //sign_MINUS =false;
        nextToken();
        /*
        if (token.getType() == TokenType::PLUS || token.getType() == TokenType::MINUS) {
            // 语义处理
            op_PLUS_MINUS = token.getValue();   // <加法运算符>
            if(op_PLUS_MINUS == "-")
                sign_MINUS = true;
            nextToken();
        }
        if(sign_MINUS) {
            arg2 = op_PLUS_MINUS + arg2;
        }*/
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
        token.setColumn(lexer->getColumn());
        token.setLine(lexer->getLine());
        string arg2 = factor();   // <因子>
        
        if(op == "/") {
            // 检查 arg2 是否为直接数字
            if (regex_match(arg2, regex("[+-]?\\d+(\\.\\d+)?")) && arg2 == "0") {
                error(token, "Divide by zero.");
            }
            // 检查 arg2 是否在 idTable 内，并且它的值是否为 0
            else if (idTable.count(arg2) > 0 && idTable[arg2].value == "0") {
                error(token, "Divide by zero.");
            }
        }
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
    Token tempToken = token;
    tempToken.setColumn(lexer->getColumn());
    tempToken.setLine(lexer->getLine());
    switch(token.getType()) {
        case TokenType::IDENTIFIER:
            if(idTable.find(token.getValue()) == idTable.end()) {
                error(tempToken, "Identifier not declared.");
            } else if (!idTable[token.getValue()].initialized) {
                error(tempToken, "Identifier '" + token.getValue() + "' used without being initialized.");
            } else{
                result = token.getValue();
            }
            break;
        case TokenType::NUMBER:
            result = token.getValue();
            break;
        case TokenType::LEFT_PAREN:
            result = expression();  // <表达式>
            // nextToken();
            if(token.getType() != TokenType::RIGHT_PAREN) {
                error(tempToken, "Expect ')' in factor.");
            }
            break;
        default:
            error(tempToken, "Expect factor.");
    }
    return result;
}

/**
 * condition()方法
 * 实现对应于文法中的 <条件>
 * <条件>→<表达式> <关系运算符> <表达式>
*/
array<string, 3> Parser::condition(){
    string arg1 = expression(); // <表达式>
    if(token.getType() != TokenType::EQUAL && token.getType() != TokenType::NOT_EQUAL
        && token.getType() != TokenType::LESS && token.getType() != TokenType::LESS_EQUAL
        && token.getType() != TokenType::GREATER && token.getType() != TokenType::GREATER_EQUAL) {
        error(token, "Expect relation operator in condition.");
    }
    string op = token.getValue();   // <关系运算符>
    string arg2 = expression(); // <表达式>
    // 语义分析与中间代码生成
    return {op, arg1, arg2};
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
void Parser::error(const Token& token, const string& message) {
    // 抛出一个解析错误
    throw runtime_error("Error at [" + std::to_string(token.getLine()) + ":" + std::to_string(token.getColumn()) + "]: " + message);
    //throw std::runtime_error("Error at [" + std::to_string(token.line) + ":" + std::to_string(token.column) + "]: " + message);
}

