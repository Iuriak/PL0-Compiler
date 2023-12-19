// Parser.h

/* 语法分析器（Parser）
 * 使用LR算法实现语法分析功能
 * 根据词法分析器生成的Token序列，构建出一棵抽象语法树（AST）
 */

#include "Lexer.h"
#include <stack>
#include <map>

class ASTNode {
    // AST节点的相关定义

};

enum class Action {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
};

struct LRItem {
    Action action;
    int nextState; // 用于SHIFT操作
    int productionRule; // 用于REDUCE操作
};

class Parser {
    std::vector<Token> tokens;  // 词法分析器生成的Token序列
    std::stack<int> states;     // 状态栈
    std::stack<ASTNode*> nodes; // 节点栈
    std::map<std::pair<int, TokenType>, LRItem> parsingTable;

public:
    // 构造函数，接收词法分析器生成的Token序列
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}
    ASTNode* parse();   // 执行语法分析
private:
    void shift(int state);
    void reduce(int rule);
    void accept();
    void error();
    LRItem getAction(int state, TokenType tokenType);
    ASTNode* executeProductionRule(int rule);
};

// parse()方法的实现
ASTNode* Parser::parse() {
    // 初始化状态栈和符号栈
    states.push(0);                 // 假设0是初始状态
    Token lookahead = tokens[0];    // 设置第一个Token作为前瞻
    size_t tokenIndex = 0;          // 当前Token的索引

    while (true) {
        LRItem action = getAction(states.top(), lookahead.type);

        switch (action.action) {
            case Action::SHIFT:     // 移入
                shift(action.nextState);
                lookahead = tokens[++tokenIndex];
                break;
            case Action::REDUCE:    // 归约
                reduce(action.productionRule);
                break;
            case Action::ACCEPT:    // 接受
                accept();
                return nodes.top();
            case Action::ERROR:     // 错误或其他情况
            default:
                error();
                return nullptr;
        }
    }
}

// getAction()方法的实现
LRItem Parser::getAction(int state, TokenType tokenType) {
    // 从分析表中获取动作
    auto it = parsingTable.find({state, tokenType});
    if (it != parsingTable.end()) {
        return it->second;  // 找到并返回对应的动作
    }
    // 没有找到对应的动作，返回错误
    return {Action::ERROR, -1, -1};
}

// shift()方法的实现
void Parser::shift(int state) {
    states.push(state);
    // 还需要将当前Token转换为AST节点并推入符号栈（nodes）
}

// reduce()方法的实现
void Parser::reduce(int rule) {
    // 根据归约规则创建AST节点，并进行状态和符号栈的相应操作
    // 这里需要定义每个规则的具体归约逻辑
}

// accept()和error()方法的实现
void Parser::accept() {
    // 解析成功
    
}
void Parser::error() {
    // 处理错误情况

}

// ... 其他实现细节 ...