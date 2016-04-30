begin
  integer k;
  integer n;
  integer function F(n);
    begin
      integer n;
      if n<=0 then F=1
      else5 F:=n*F(n-1)
    end;
  read(m);
  k:=F(m);
  write(k)
end
