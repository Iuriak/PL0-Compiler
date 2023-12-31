// main.cpp
#include "Lexer.h"
#include "Parser.h"
#include "IntermediateCodeGenerator.h"
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    // 读取源代码文件
    std::ifstream file(argv[1]);

    // 读取源代码到缓冲区
    std::stringstream buffer;
    buffer << file.rdbuf();
    // 存储源代码为字符串
    std::string source = buffer.str();
    // 关闭文件！
    file.close(); 
      
    // 词法分析器
    Lexer lexer(source);    // 传入源代码完成初始化
    Parser parser(lexer);   // 语法分析器调用词法分析器的接口，获取Token序列
    //auto tokens = lexer.tokenize();

    
    auto ast = parser.parse();

    IntermediateCodeGenerator codeGen(ast);
    codeGen.generate();

    // ... 输出或保存中间代码

    return 0;
}
