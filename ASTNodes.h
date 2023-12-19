// ASTNodes.h
#ifndef ASTNODES_H
#define ASTNODES_H

#include <string>
#include <vector>
#include <memory>

// AST基类
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// 程序头部节点，可能包含程序名和可能的参数列表等
class ProgramHeaderNode : public ASTNode {
public:
    std::string programName;

    explicit ProgramHeaderNode(const std::string& programName) : programName(programName) {}
};

// 程序节点，代表整个程序
class ProgramNode : public ASTNode {
public:
    std::unique_ptr<ProgramHeaderNode> header;
    std::unique_ptr<BlockNode> block;

    ProgramNode(std::unique_ptr<ProgramHeaderNode> header, std::unique_ptr<BlockNode> block)
        : header(std::move(header)), block(std::move(block)) {}
};

// 分程序/代码块节点，可能包含声明和语句序列
class BlockNode : public ASTNode {
public:
    std::unique_ptr<ConstDeclarationNode> constDeclaration;
    std::unique_ptr<VarDeclarationNode> varDeclaration;
    std::vector<std::unique_ptr<StatementNode>> statements;

    BlockNode(std::unique_ptr<ConstDeclarationNode> constDeclaration,
              std::unique_ptr<VarDeclarationNode> varDeclaration,
              std::vector<std::unique_ptr<StatementNode>> statements)
        : constDeclaration(std::move(constDeclaration)), varDeclaration(std::move(varDeclaration)),
          statements(std::move(statements)) {}
};

// 常量声明节点
class ConstDeclarationNode : public ASTNode {
    public:
    std::string name;
    int value;

    ConstDeclarationNode(const std::string& name, int value)
        : name(name), value(value) {}
};

// 变量声明节点
class VarDeclarationNode : public ASTNode {
    std::string name;
    std::string type;

    VarDeclarationNode(const std::string& name, const std::string& type)
        : name(name), type(type) {}
};

// 语句节点的基类
class StatementNode : public ASTNode {
    // 你需要添加具体内容
    // 比如：ForStatementNode, IfStatementNode, AssignmentNode等
    // 实际的StatementNode通常是一个基类，你需要派生出具体的语句类型
    // 以下是一个示例
public:
    virtual void execute() = 0; // 假定语句节点可以执行
};

// 具体的语句类型，比如赋值语句
class AssignmentNode : public StatementNode {
    std::string variableName;
    std::unique_ptr<ASTNode> expression;

public:
    AssignmentNode(const std::string& variableName, std::unique_ptr<ASTNode> expression)
        : variableName(variableName), expression(std::move(expression)) {}

    void execute() override {
        // 实现赋值语句的执行
    }
};
// ... 其他AST节点类 ...

#endif // ASTNODES_H
