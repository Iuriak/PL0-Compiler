// main.cpp
#include "Lexer.h"
#include "Parser.h"
#include "IntermediateCodeGenerator.h"
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    std::stringstream buffer;
    buffer << file.rdbuf();

    Lexer lexer(buffer.str());
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto ast = parser.parse();

    IntermediateCodeGenerator codeGen(ast);
    codeGen.generate();

    // ... 输出或保存中间代码

    return 0;
}
