int func(int a, int b, int c) {
extern int func2(int,int);
return func2(a,b+c);
}
