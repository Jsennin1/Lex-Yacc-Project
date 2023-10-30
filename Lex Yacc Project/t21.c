#include <stdio.h>

struct stab {
  int val;
  char* name; 
} stab[100];
int stabuse = 0;
struct node { int type, left, right; } ntab[400];
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
#define T_EQ 16
#define T_PRINTX 17
#define T_DO_WHILE 18
#define T_AND 19
#define T_OR 20


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
stab[stabuse].name = (char*)malloc(sizeof(char) * (strlen(s)));
strcpy(stab[stabuse].name, s); return stabuse++;
}


int node(int t, int l, int r) {
int i = ntabuse++;
ntab[i].type = t;
ntab[i].left = l;
ntab[i].right = r;
return i;
}

void emittree(int i)
{
  static int labelno = 1;
int l;
int k;
switch(ntab[i].type) {
case T_STLIST: if(ntab[i].left) emittree(ntab[i].left);
emittree(ntab[i].right);
break;
case T_READ:
printf(" movq $.Lr%d,%%rdi\n", ntab[i].left);
printf(" movq $0,%%rax\n");
printf(" call printf\n");
printf(" movq $.Lprompt,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
printf(" leaq %d(%%rbp),%%rsi\n", -(ntab[i].left+1)*8);
printf(" movq $.Lread,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call scanf\n");
printf(" movq %%rax, %d(%%rbp)\n", -(lookup("readStat")+1)*8);
break;
case T_PRINT: emittree(ntab[i].left);
if(ntab[ntab[i].left].type == T_VAR)
{
printf(" movq $.Lr%d,%%rdi\n", ntab[ntab[i].left].left);
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");

printf(" movq $.Lequal,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
}

printf(" popq %%rsi\n");
printf(" movq $.Lprint,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
break;
case T_PRINTX: emittree(ntab[i].left);
if(ntab[ntab[i].left].type == T_VAR)
{
printf(" movq $.Lr%d,%%rdi\n", ntab[ntab[i].left].left);
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");

printf(" movq $.Lequal,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
}

printf(" popq %%rsi\n");
printf(" movq $.Lprintx,%%rdi\n");
printf(" movq $0,%%rax\n"); /* 浮動小数点レジスタを使わない */
printf(" call printf\n");
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
case T_SUB: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rdx\n");
printf(" popq %%rax\n");
printf(" subq %%rdx,%%rax\n");
printf(" pushq %%rax\n");
break;
case T_MUL: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rdx\n");
printf(" popq %%rax\n");
printf(" imulq %%rdx\n");
printf(" pushq %%rax\n");
break;
case T_DIV: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rdi\n");
printf(" popq %%rax\n");
printf(" movq $0,%%rdx\n");
printf(" idivq %%rdi\n");
printf(" pushq %%rax\n");
break;
case T_REM: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rdi\n");
printf(" popq %%rax\n");
printf(" movq $0,%%rdx\n");
printf(" idivq %%rdi\n");
printf(" pushq %%rdx\n");
break;
case T_LT: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rcx\n");
printf(" popq %%rax\n");
printf(" cmp %%rcx,%%rax\n");
printf(" jge ");
break;
case T_GT: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rcx\n");
printf(" popq %%rax\n");
printf(" cmp %%rcx,%%rax\n");
printf(" jle ");
break;
case T_IF: l = labelno++;
emittree(ntab[i].left);
printf(".L%d\n", l);
emittree(ntab[i].right);
printf(".L%d:\n", l);
break;
case T_WHILE: l = labelno++;
k = labelno++;
printf(".L%d:\n", l);
emittree(ntab[i].left);
printf(".L%d\n", k);
emittree(ntab[i].right);
printf(" jmp ");
printf(".L%d\n", l);
printf(".L%d:\n", k);
break;
case T_DO_WHILE: l = labelno++;
k = labelno++;
printf(".L%d:\n", l);
emittree(ntab[i].right);
emittree(ntab[i].left);
printf(".L%d\n", k);
printf(" jmp ");
printf(".L%d\n", l);
printf(".L%d:\n", k);
break;
case T_EQ: emittree(ntab[i].left);
emittree(ntab[i].right);
printf(" popq %%rcx\n");
printf(" popq %%rax\n");
printf(" cmp %%rcx,%%rax\n");
printf(" jne ");
break;
case T_AND: 
l = labelno++;
k = labelno++;
emittree(ntab[i].left);
printf(".L%d\n", l);
emittree(ntab[i].right);
printf(".L%d\n", l);
printf(" movq $1,%%r10\n");
printf(" jmp .L%d\n", k);
printf(".L%d:\n", l);
printf(" movq $0,%%r10\n");
printf(".L%d:\n", k);
printf(" cmp $1,%%r10\n");
printf(" jne ");
break;
case T_OR:
printf(" movq $0,%%r10\n");
l = labelno++;
k = labelno++;
emittree(ntab[i].left);
printf(".L%d\n", l);
printf(" movq $1,%%r10\n");
printf(" jmp .L%d\n", k);
printf(".L%d:\n", l);
emittree(ntab[i].right);
printf(".L%d\n", k);
printf(" movq $1,%%r10\n");
printf(".L%d:\n", k);
printf(" cmp $1,%%r10\n");
printf(" jne ");
break;
case T_NUM: printf(" pushq $%d\n", ntab[i].left);
break;
case T_VAR: printf(" pushq %d(%%rbp)\n", -(ntab[i].left+1)*8);
break;
default: printf("NotImplemented: %d\n", ntab[i].type);
break;
}
}

void dotree(int i) {
int stk;
printf(" .section .rodata\n");
printf(".Lprompt: .string\"> \"\n"); /* プロンプト */
printf(".Lequal: .string\"= \"\n"); /* プロンプト */
int a;
for ( a = 0; a < stabuse; a++)
{
printf(".Lr%d: .string\"%s \"\n",a,stab[a].name); /* プロンプト */
}
printf(".Lread: .string\"%%ld\"\n"); /* 読み取り用書式 */
printf(".Lprint: .string\"%%ld\\n\"\n"); /* 書き出し用書式 */
printf(".Lprintx: .string\"%%lx\\n\"\n"); /* 書き出し用書式 */
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
for (a = 0; a < stabuse; a++) {
    free(stab[a].name); 
  }
}

