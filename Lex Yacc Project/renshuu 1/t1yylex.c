#include <stdio.h>
char yytext[100];
int nextc = 0;
int yylex(void) {
int i = 0;
if(nextc == 0) nextc = getchar();
while(nextc != EOF) {
if(nextc == ' ' || nextc == '\t' || nextc == '\n') {
nextc = getchar(); }
else if('0' <= nextc && nextc <= '9') {
do {
yytext[i++] = nextc; nextc = getchar();
} while('0' <= nextc && nextc <= '9');
yytext[i++] = 0; return NUM; }
else if(('a' <= nextc && nextc <= 'z') || ('A' <= nextc && nextc <= 'Z')) {
do {
yytext[i++] = nextc; nextc = getchar();
} while(('a' <= nextc && nextc <= 'z') || ('A' <= nextc && nextc <= 'Z') ||
('0' <= nextc && nextc <= '9'));
yytext[i++] = 0; return IDENT; }
else {
fprintf(stderr, "invalid char: %x\n", nextc); /* 練習 3 のときには削除 */
nextc = getchar(); }
}
return 0;
}