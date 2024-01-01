// main.cpp
#include "Lexer.h"
#include "Parser.h"
#include "IntermediateCodeGenerator.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // 从命令行参数获取源代码文件名
    string inputFileName;
    #include <iostream>

    string IRFile = "IR.txt";
    string ITFile = "IT.csv";

    // 读取源代码文件
    ifstream file(inputFileName);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    // 读取源代码到缓冲区
    stringstream buffer;
    buffer << file.rdbuf();
    // 存储源代码为字符串
    string source = buffer.str();
    // 关闭文件！
    file.close(); 
      
    // 词法分析器
    Lexer lexer(source);    // 传入源代码完成初始化
    Parser parser(lexer);   // 语法分析器调用词法分析器的接口，获取Token序列
    bool success = parser.program(); // 执行语法分析

    // ... 输出或保存中间代码和四元式
    ofstream IRout(IRFile);
    ofstream ITout(ITFile);
    parser.output(IRout, ITout);
    IRout.close();
    ITout.close();

    return 0;
}
