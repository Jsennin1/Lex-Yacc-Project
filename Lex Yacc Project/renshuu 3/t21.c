/* t20.c -- compiler for a simple language */
#include <stdio.h>
struct stab {
int val;
char name[20]; } stab[100];
int stabuse = 0;
struct node {
int type, left, right; } ntab[400];
int ntabuse = 1;
#define T_STLIST 1
#define T_ASSIGN 2
#define T_READ 3
#define T_PRINT 4
#define T_ADD 5
#define T_SUB 6
#define T_MUL 7
#define T_DIV 8
#define T_REM 9
#define T_NUM 10
#define T_VAR 11
#define T_WHILE 12
#define T_IF 13
#define T_LT 14
#define T_GT 15
int lookup(char*);
int node(int, int, int);
void dotree(int);
extern char *yytext;
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


void emittree(int i)
{
switch(ntab[i].type) {
case T_STLIST: if(ntab[i].left) emittree(ntab[i].left);
emittree(ntab[i].right);
break;
case T_READ: printf(" movq $.Lprompt,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
printf(" leaq %d(%%rbp),%%rsi\n", -(ntab[i].left+1)*8);
printf(" movq $.Lread,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call scanf\n");
break;
case T_PRINT: emittree(ntab[i].left);
printf(" popq %%rsi\n");
printf(" movq $.Lprint,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
break;
case T_NUM: printf(" pushq $%d\n", ntab[i].left);
break;
case T_VAR: printf(" pushq %d(%%rbp)\n", -(ntab[i].left+1)*8);
break;
case T_ASSIGN: emittree(ntab[i].right);
printf(" popq %d(%%rbp)\n", -(ntab[i].left+1)*8);
break;
case T_ADD: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rdx\n");
printf(" popq %%rax\n");
printf(" addq %%rdx,%%rax\n");
printf(" pushq %%rax\n");
break;
case T_MUL: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rdx\n");
printf(" popq %%rax\n");
printf(" imulq %%rdx\n");
printf(" pushq %%rax\n");
break;
default: printf("NotImplemented: %d\n", ntab[i].type);
break;
}
}


void dotree(int i) {
int stk;
printf(" .section .rodata\n");
printf(".Lprompt: .string\"> \"\n"); /* プロンプト */
printf(".Lread: .string\"%%ld\"\n"); /* 読み取り用書式 */
printf(".Lprint: .string\"%%ld\\n\"\n"); /* 書き出し用書式 */
printf(" .text\n");
printf(".global main\n");
printf("main:\n");
printf(" pushq %%rbp\n");
printf(" movq %%rsp,%%rbp\n");
stk = (8*stabuse + 15) / 16; /* 変数の個数*8 で 16 の倍数へ切り上げ */
stk *= 16;
printf(" subq $%d,%%rsp\n", stk);
emittree(i);
printf(" leave\n");
printf(" ret\n");
}

int node(int t, int l, int r) {
int i = ntabuse++;
ntab[i].type = t;
ntab[i].left = l;
ntab[i].right = r;
return i;
}