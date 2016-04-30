#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include "parser.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

namespace ERR
{
    const int MISS_DECLARATION = 0;
    const int MISS_EXECUTIVE = 1;
    const int EXPT_END = 2;
    const int EXPT_BEGIN = 3;
    const int MISS_SEPARATOR = 4;
    const int ILG_VAR = 5;
    const int MISS_RBRACKET = 6;
    const int MISS_LBRACKET = 7;
    const int ILG_DECLARATION = 8;
    const int ILG_EXECUTIVE = 9;
    const int UNK_VAR = 10;
    const int ILG_OPT = 11;
    const int MISS_ELSE = 12;
    const int MISS_THEN = 13;
    const int REP_DECLARATION = 14;
};

namespace type
{
    int TY_ARG = 0;
    int TY_FML = 1;
};

int cur_line, cur_depth;
vector<var> v_table;
vector<proc> p_table;
string sym;
int val;
bool ended = false;

void var_init()
{
    cur_line = 1;
    cur_depth = 0;
    p_table.clear();
    v_table.clear();
    // 添加主函数层信息
    p_table.push_back(proc("", "", 0, 0, -1));
}

// 读入二元式(不包括 EOF EOLN)
void advance()
{
    freopen("outfile/example.dys", "a+", stdout);
    cin >> sym >> val;
    printf("%16s %2d\n",sym.c_str(), val);
    while(sym == "EOLN")
    {
        cur_line ++;
        cin >> sym >> val;
        printf("%16s %2d\n",sym.c_str(), val);
    }
    if(sym == "EOF") ended = true;
}

void add_var(int type)
{
    for (int i = p_table[cur_depth].fadr;i <= p_table[cur_depth].ladr;i ++)
    {
        if (v_table[i].vname == sym && v_table[i].vlev == cur_depth && v_table[i].vkind == type)
        {
            error(ERR::REP_DECLARATION);
            return ;
        }
    }

    int idx =v_table.size();
    v_table.push_back(var(sym, p_table[cur_depth].pname, "integer", type, cur_depth, idx));
    update_proc();
}

bool check_var()
{
    for(int i = p_table[cur_depth].fadr;i <= p_table[cur_depth].ladr;i ++)
    {
        if(v_table[i].vname == sym && v_table[i].vlev == cur_depth)
        {
            return true;
        }
    }
    return false;
}

void add_proc()
{
    cur_depth ++;
    int idx = v_table.size();
    p_table.push_back(proc(sym, "integer", cur_depth, idx, idx - 1));
}

void update_proc()
{
    p_table[cur_depth].ladr++;
}

void error(int type)
{
    freopen("outfile/SynAnalyze.err","a+",stdout);
    switch(type)
    {
        case ERR::REP_DECLARATION: printf("LINE %d: variable \"%s\" previously declared.\n", cur_line, sym.c_str()); break;
        case ERR::MISS_DECLARATION: printf("LINE %d: missing declaration here.\n", cur_line); break;
        case ERR::MISS_EXECUTIVE: printf("LINE %d: missing executive statement here.\n",cur_line); break;
        case ERR::EXPT_END: printf("LINE %d: expected \"end\" here.\n", cur_line); break;
        case ERR::EXPT_BEGIN: printf("LINE %d: expected \"begin\" here.\n", cur_line); break;
        case ERR::MISS_SEPARATOR: printf("LINE %d: missing \';\' here.\n", cur_line); break;
        case ERR::MISS_RBRACKET: printf("LINE %d: brackets doesn't matched.\n", cur_line); break;
        case ERR::ILG_VAR: printf("LINE %d: illegal variable here.\n", cur_line); break;
        case ERR::MISS_LBRACKET: printf("LINE %d: missing \'(\' here.\n", cur_line); break;
        case ERR::ILG_DECLARATION: printf("LINE %d: illegal declaration here.\n", cur_line); break;
        case ERR::ILG_EXECUTIVE: printf("LINE %d: illegal executive statement here.\n",cur_line); break;
        case ERR::UNK_VAR: printf("LINE %d: variable \"%s\" undeclared.\n", cur_line, sym.c_str()); break;
        case ERR::MISS_ELSE: printf("LINE %d: missing \"else\" here.\n", cur_line); break;
        case ERR::MISS_THEN: printf("LINE %d: missing \"then\" here.\n", cur_line); break;
        case ERR::ILG_OPT: printf("LINE %d: illegal operator here.\n", cur_line); break;
        default: printf("LINE %d: unknown error\n",cur_line);
    }
    advance();
    //fclose(stdout);
}

// 识别一个分程序
// <分程序> → begin <说明语句表>；<执行语句表> end
void A()
{
    if(sym == "begin")
    {
        advance();
        if(sym == "integer")
        {
            advance();
            B(); // 识别说明语句
        }
        else error(ERR::MISS_DECLARATION);
        if(sym == ";")
        {
            while(sym == ";")
            {
                advance();
                if(sym == "integer")
                {
                    advance();
                    B(); // 识别说明语句
                }
                else break;
            }
        }
        else error(ERR::MISS_EXECUTIVE);
        C(); //识别执行语句
        while(sym == ";")
        {
            advance();
            C(); // 识别执行语句
        }
        if(sym == "end")
        {
            advance();
            return ;
        }
        else error(ERR::EXPT_END);
    }
    else error(ERR::EXPT_BEGIN);
}

// 识别说明语句
// <说明语句>→<变量说明>│<函数说明>
// <函数说明>→integer function <标识符>（<参数>）；<函数体>
void B()
{
    if(val == 10) // 若为变量名
    {
        add_var(type::TY_ARG); // 符号表中加入变量
        advance();
    }
    else if(sym == "function") // 若为函数说明
    {
        advance();
        if(val == 10) // 若为标识符(函数名)
        {
            advance();
            add_proc(); // 添加新的过程信息
            if(sym == "(")
            {
                advance();
                if (val == 10) // 函数形参
                {
                    add_var(type::TY_FML); //加入形参
                    advance();
                    if (sym == ")")
                    {
                        advance();
                        if (sym == ";")
                        {
                            advance();
                            A(); //重新识别函数体
                            // 函数体识别完后 跳出当前层
                            cur_depth --;
                        }
                        else error(ERR::MISS_SEPARATOR);
                    }
                    else error(ERR::MISS_RBRACKET);
                }
                else error(ERR::ILG_VAR);
            }
            else error(ERR::MISS_LBRACKET);
        }
        else error(ERR::ILG_VAR);
    }
    else error(ERR::ILG_DECLARATION);
}

// 识别执行语句
// <执行语句>→<读语句>│<写语句>│<赋值语句>│<条件语句>
void C()
{
    if(sym == "read")
    {
        advance();
        D(); // 识别变量名
    }
    else if(sym == "write")
    {
        advance();
        D(); // 识别变量名
    }
    else if(val == 10) // 若为标识符
    {
        advance();
        E(); // 识别赋值语句s
    }
    else if(sym == "if")
    {
        advance();
        I(); // 识别条件语句
    }
    else error(ERR::ILG_EXECUTIVE);
}

// 识别 (变量名)
void D()
{
    if(sym == "(")
    {
        advance();
        if(val == 10) // 若该单词为标识符
        {
            if(check_var()) //检查变量是否存在
            {
                advance();
                if(sym == ")")
                {
                    advance();
                }
                else error(ERR::MISS_RBRACKET);
            }
            else error(ERR::UNK_VAR);
        }
        else error(ERR::ILG_VAR);
    }
    else error(ERR::MISS_LBRACKET);
}

// 识别赋值语句
void E()
{
    if(sym == ":=")
    {
        advance();
        F(); // 识别算术表达式
    }
    else error(ERR::ILG_OPT);
}

// 识别算术表达式
// <算术表达式> -> <项> | <算术表达式> - <项>
// 简化得到: <算术表达式> -> <项> ( - <项>)*
void F()
{
    G(); // 识别一个项
    while(sym == "-")
    {
        advance();
        F();
    }
}

// <项>→<项>*<因子>│<因子>
// 简化得到: <项>→<因子> (*<因子>)*
void G()
{
    H(); // 识别因子
    while(sym == "*")
    {
        advance();
        H();
    }
}

// 识别因子
// <因子>→<变量>│<常数>│<函数调用>
void H()
{
    if(sym == "F") // 若为函数调用
    {
        advance();
        if(sym == "(")
        {
            advance();
            F(); // 识别算术表达式
            if(sym == ")")
            {
                advance();
            }
            else error(ERR::MISS_RBRACKET);
        }
        else error(ERR::MISS_LBRACKET);
    }
    else if(val == 10) // 若为变量
    {
        if (check_var()) //检查变量是否存在
        {
            advance();
        }
        else error(ERR::UNK_VAR);
    }
    else if(val == 11) // 若为常量
    {
        advance();
    }
    else error(ERR::ILG_EXECUTIVE);
}

// 识别条件语句
// <条件语句>→if<条件表达式>then<执行语句>else <执行语句>
void I()
{
    J(); // 识别条件表达式
    if(sym == "then")
    {
        advance();
        C(); // 识别一条执行语句
        if(sym == "else")
        {
            advance();
            C(); // 识别一条执行语句
        }
        else error(ERR::MISS_ELSE);
    }
    else error(ERR::MISS_THEN);
}

// 识别条件表达式
// <条件表达式>→<算术表达式><关系运算符><算术表达式>
void J()
{
    F(); //识别算术表达式
    if(val <= 17 && val >= 13) // 若为关系运算符
    {
        advance();
        F(); // 识别算术表达式
    }
    else error(ERR::ILG_OPT);
}
