%token NUM;
%token IDENT;
%left  '+'  '-'
%left  '*'  '/'
%right '^'
%%

stlist :
| stlist stat '\n'
;
stat : var '=' expr { stab[$1].val = $3; printf("%d\n", $3); }
;
expr : prim { $$ = $1; }
| expr '*' expr { $$ = $1 * $3; }
| expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
| expr '/' expr { $$ = $1 / $3; }
| expr '^' expr { $$ = pow($1,$3); }
;
prim : NUM { $$ = atoi(yytext); }
| var { $$ = stab[$1].val; }
| '(' expr ')' { $$ = $2; }
;
var : IDENT { $$ = lookup(yytext); }
;
%%