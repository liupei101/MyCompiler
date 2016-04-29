#include <cstring>
#include <cstdio>
#include "lexical_analyzer.h"
const int MAX_LENGTH = 30;
const int TY_Idt = 0, TY_Dit = 1, TY_Oth = 2, TY_EOL = 3;
const int TY_OP = 0, TY_Unk = 1;
char ch;
int idx;
char token[MAX_LENGTH];

/*token 串初始化*/
void tokenInit()
{
    memset(token, 0, sizeof(token));
    idx = 0;
}

bool getChar(char* Line, int& i)
{
    ch = Line[i ++];
    return ch != '\0';
}

void getnbc(char* Line, int& i)
{
    while(getChar(Line, i))
    {
        if(ch != ' ') break;
    }
}

bool letter()
{
    return (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') ;
}

bool digit()
{
    return ch >= '0' && ch <= '9';
}

void concat()
{
    token[idx ++] = ch;
}

int reserve(const char* str)
{
    if(strcmp(str, "begin") == 0) return 1;
    if(strcmp(str, "end") == 0) return 2;
    if(strcmp(str, "integer") == 0) return 3;
    if(strcmp(str, "if") == 0) return 4;
    if(strcmp(str, "then") == 0) return 5;
    if(strcmp(str, "else") == 0) return 6;
    if(strcmp(str, "function") == 0) return 7;
    if(strcmp(str, "read") == 0) return 8;
    if(strcmp(str, "write") == 0) return 9;
    return 10;
}

int table(const char* str)
{
    if(strcmp(str, "=") == 0) return 12;
    if(strcmp(str, "<>") == 0) return 13;
    if(strcmp(str, "<=") == 0) return 14;
    if(strcmp(str, "<") == 0) return 15;
    if(strcmp(str, ">=") == 0) return 16;
    if(strcmp(str, ">") == 0) return 17;
    if(strcmp(str, "-") == 0) return 18;
    if(strcmp(str, "*") == 0) return 19;
    if(strcmp(str, ":=") == 0) return 20;
    if(strcmp(str, "(") == 0) return 21;
    if(strcmp(str, ")") == 0) return 22;
    if(strcmp(str, ";") == 0) return 23;
    return 24;
}

void successful(const char* str, int type)
{
    freopen("outfile/example.dyd", "a+", stdout);
    if(type == TY_Idt) //符号属于保留字类别
    {
        printf("%16s %2d\n", str, reserve(str));
    }
    else if(type == TY_Dit) // 符号为常数
    {
        printf("%16s %2d\n", str, 11);
    }
    else if(type == TY_Oth) // 符号为比较运算符及其他
    {
        printf("%16s %2d\n", str, table(str));
    }
    else if(type = TY_EOL)
    {
        printf("%16s 24\n","EOLN");
    }
    fclose(stdout);
}

void error(int type, int cur_line)
{
	freopen("outfile/LexAnalyze.err", "a+", stdout);

	printf("***LINE%d:  ", cur_line);
	if(type == 0) printf("illegal operator\n");
	else printf("unknown character\n");

	fclose(stdout);
}
bool mainLexicalAnalyzer(char* Line, int& i, int cur_line)
{
    // 初始化token串
    tokenInit();

    getnbc(Line, i);

    switch(ch)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
	    case 'B':
	    case 'C':
	    case 'D':
	    case 'E':
	    case 'F':
	    case 'G':
	    case 'H':
	    case 'I':
	    case 'J':
	    case 'K':
	    case 'L':
	    case 'M':
	    case 'N':
	    case 'O':
	    case 'P':
	    case 'Q':
	    case 'R':
	    case 'S':
	    case 'T':
	    case 'U':
	    case 'V':
	    case 'W':
	    case 'X':
	    case 'Y':
	    case 'Z':
            while(letter() || digit())
            {
                concat();
                getChar(Line, i);
            }

            i --; // 回退一个字符
            successful(token, TY_Idt);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            while(digit())
            {
                concat();
                getChar(Line, i);
            }
            i --;
            successful(token, TY_Dit);
            break;
        case '<':
            getChar(Line, i);
            if(ch == '=')
            {
                successful("<=", TY_Oth);
            }
            else if(ch == '>')
            {
                successful("<>", TY_Oth);
            }
            else
            {
                i --;
                successful("<", TY_Oth);
            }
            break;
        case '>':
            getChar(Line, i);
            if(ch == '=')
            {
                successful(">=", TY_Oth);
            }
            else
            {
                i --;
                successful(">", TY_Oth);
            }
            break;
        case '=':
            successful("=", TY_Oth);
            break;
        case '-':
            successful("-", TY_Oth);
            break;
        case '*':
            successful("*", TY_Oth);
            break;
        case ':':
            getChar(Line, i);
            if(ch == '=')
            {
                successful(":=", TY_Oth);
            }
            else
            {
                error(TY_OP, cur_line);
                return false;
            }
            break;
        case '(':
            successful("(", TY_Oth);
            break;
        case ')':
            successful(")", TY_Oth);
            break;
        case ';':
            successful(";", TY_Oth);
            break;
        default:
            error(TY_Unk, cur_line);
            return false;
    }
    return true;
}
