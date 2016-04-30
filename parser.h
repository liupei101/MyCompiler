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
    variable(string _vname, string _vproc, string _vtype, int _vkind, int _vlev, int _vadr)
    {
        vname = _vname, vproc = _vproc, vtype = _vtype;
        vkind = _vkind, vlev = _vlev, vadr = _vadr;
    }
}var;

typedef struct procedure
{
    string pname, ptype;
    int plev, fadr, ladr;
    procedure(string _pname, string _ptype, int _plev, int _fadr, int _ladr)
    {
        pname = _pname, ptype = _ptype;
        plev = _plev, fadr = _fadr, ladr = _ladr;
    }
}proc;

// 全局变量的初始化
void var_init();

// 输入一个二元式
void advance();

// 出错处理函数
void error(int type);

// 向符号表中添加新的符号
void add_var(int type);

// 检查符号表
bool check_var();

// 添加新的过程信息
void add_proc();

// 更新过程表
void update_proc();

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
