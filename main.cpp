#include <iostream>
#include <cstdio>
#include <cstring>
#include "lexical_analyzer.h"
#include "parser.h"
const int MAX_LENGTH = 105;
const int TY_EOL = 3, TY_EOF = 4;
void clearOutputFile()
{
    freopen("outfile/example.dyd", "w", stdout);
	fclose(stdout);
	freopen("outfile/LexAnalyze.err", "w", stdout);
	fclose(stdout);

	freopen("outfile/example.dys", "w", stdout);
    fclose(stdout);
    freopen("outfile/example.var", "w", stdout);
    fclose(stdout);
    freopen("outfile/example.pro", "w", stdout);
    fclose(stdout);
    freopen("outfile/SynAnalyze.err", "w", stdout);
    fclose(stdout);
}
void lexical_analyzer()
{
    freopen("example.pas", "r", stdin);
    char Line[MAX_LENGTH];
    int cur_line = 1;
    while(gets(Line))
    {
        int len = strlen(Line);
        for(int i = 0;i < len;)
        {
            mainLexicalAnalyzer(Line, i, cur_line);
        }
        successful("", TY_EOL);
        cur_line ++;
    }
    successful("", TY_EOF);
    fclose(stdin);
}

void parser()
{
    freopen("outfile/example.dyd", "r", stdin);
    var_init();
    advance();
    A();
    fclose(stdin);
}
int main()
{
    clearOutputFile(); // 清空文件

    lexical_analyzer(); // 进行词法分析部分

    parser(); // 进行语法分析部分

    return 0;
}
