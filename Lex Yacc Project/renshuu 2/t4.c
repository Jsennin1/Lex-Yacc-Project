#include <stdio.h>
#include <math.h>
struct stab {
int val;
char name[20]; } stab[100];
int stabuse = 0;
extern char *yytext;
int lookup(char*);
#include "y.tab.c"
#include "lex.yy.c"
int main() {
yyparse();
return 0;
}
int lookup(char *s) {
int i;
for(i = 0; i < stabuse; ++i)
if(strcmp(stab[i].name, s) == 0) return i;
if(stabuse >= 99) {
printf("table overflow.\n"); exit(1); }
strcpy(stab[stabuse].name, s); return stabuse++;
}
