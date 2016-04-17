/**
* 词法分析处理函数
*/
#ifndef LEXICAL_ANALYZER_H_INCLUDED
#define LEXICAL_ANALYZER_H_INCLUDED

/*词法分析主程序*/
bool mainLexicalAnalyzer(char* Line, int& i, int cur_line);

/*读进一个字符*/
bool getChar(char* Line, int& i);

/*读进下一个非空白字符*/
void getnbc(char* Line, int& i);

/*把字符ch连接到token的末尾*/
void concat();

/*判断是否为数字*/
bool digit();

/*判断是否为字母*/
bool letter();

/*得到标识符在符号表中的编码*/
int reserve(const char* str);

/*得到其余字符在符号表中的编码*/
int table(const char* str);

/*正确识别单词处理*/
void successful(const char* str, int type);

/*错误处理*/
void error(int type, int cur_line);
#endif // LEXICAL_ANALYZER_H_INCLUDED
