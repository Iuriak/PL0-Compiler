// IntermediateCodeGenerator.h
#include "Parser.h"

class IntermediateCodeGenerator {
    ASTNode* ast;
public:
    IntermediateCodeGenerator(ASTNode* ast) : ast(ast) {}
    void generate();
private:
    void visit(ASTNode* node);
    // ... 其他代码生成逻辑
};
