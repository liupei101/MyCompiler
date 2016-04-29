/**
* 语法分析处理函数
*/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
using std::string;
// 结构声明
typedef struct variable
{
    string vname,vproc,vtype;
    int vkind, vlev, vadr;
}var;

typedef struct procedure
{
    string pname, ptype;
    int plev, fadr, ladr;
}proc;

// 全局变量的初始化
void var_init();

// 输入一个二元式
void advance();

// 出错处理函数
void error(int type);

// 向符号表中添加新的符号
void var_add(int type);

// 检查符号表
bool var_check();

// 状态节点处理函数
void A();
void B();
void C();
void D();
void E();
void F();
void G();
void H();
void I();
void J();

#endif // PARSER_H_INCLUDED
