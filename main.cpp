#include <iostream>
#include <cstdio>
#include <cstring>
#include "lexical_analyzer.h"
using namespace std;
const int MAX_LENGTH = 105;
const int TY_EOL = 3, TY_EOF = 4;
void clearOutputFile()
{
    freopen("outfile/example.dyd", "w",stdout);
	fclose(stdout);
	freopen("outfile/LexAnalyze.err","w",stdout);
	fclose(stdout);
}
int main()
{
    freopen("example.pas", "r", stdin);
    clearOutputFile();
    //symbolTableInit();
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
    return 0;
}
