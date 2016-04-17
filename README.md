## 编译器的实现


#### 要求设计的程序语言描述如下：

语法结构类似于pascal

最终要求实现下面程序的编译运行, 要求给出词法, 语法分析的结果

```pascal
begin
  integer k;
  integer function F(n);
    begin
      integer n;
      if n<=0 then F:=1
      else F:=n*F(n-1)
    end;
  read(m);
  k:=F(m);
  write(k);
end
```

----
#### 文件说明：
- main.cpp 主程序文件
- lexical_analyzer.h **词法分析相关函数声明**
- lexical_analyzer.cpp **词法分析相关函数实现**
- outfile/example.dyd **词法分析得到的二元组**
- outfile/LexAnalyze.err **词法分析得到的词法出错提示**

----
#### update：
- 目前实现了词法分析功能

