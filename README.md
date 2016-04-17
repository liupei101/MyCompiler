## 编译器的实现


#### 要求设计的程序语言描述如下：

语法结构类似于pascal

最终要求实现下面程序的编译运行：

```pascal
begin
  integer k;
  integer function F(n);
    begin
      integer n;
      if n<=0 then F:=1
      else F:=n*F(n-1)&&
    end;
  read(m);
  k:=F(m);
  write(k)
end
```

#### update：
- 目前实现了词法分析功能

