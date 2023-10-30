%token NUM;
%token IDENT;
%token READ;
%token PRINT;
%token PRINTX;
%token WHILE;
%token DO;
%token IF;
%token AND;
%token OR;
%token EQ;
%left AND OR
%%
prog  : IDENT '{' stlist '}' { dotree($3); return 0; }
      ;
stlist : { $$ = 0; }
       | stlist stat  { $$ = node(T_STLIST, $1, $2); }
       ;
stat : var '=' expr ';'  { $$ = node(T_ASSIGN, $1, $3); }
     | READ var ';' { $$ = node(T_READ, $2, 0); }
     | PRINT expr ';' { $$ = node(T_PRINT, $2, 0); }
     | PRINTX expr ';' { $$ = node(T_PRINTX, $2, 0); }
     | WHILE '(' cond ')' stat { $$ = node(T_WHILE, $3, $5); }
     | DO '{' stlist '}' WHILE '(' cond ')' ';' { $$ = node(T_DO_WHILE, $7,$3); }
     | IF '(' cond ')' stat { $$ = node(T_IF, $3, $5); }
     | '{' stlist '}' { $$ = $2; }
     ;
cond  : expr '<' expr { $$ = node(T_LT, $1, $3); }
      | expr '>' expr { $$ = node(T_GT, $1, $3); }
      | expr EQ expr { $$ = node(T_EQ, $1, $3); }
      | cond AND cond { $$ = node(T_AND, $1, $3); }
      | cond OR cond { $$ = node(T_OR, $1, $3); }
      | '(' cond ')' { $$ = $2; }
      ;
formula : prim { $$ = $1; }
      | formula '*' prim { $$ = node(T_MUL, $1, $3); }
      | formula '/' prim { $$ = node(T_DIV, $1, $3); }
      | formula '%' prim { $$ = node(T_REM, $1, $3); }
      ;
expr  : formula { $$ = $1; }
      | expr '+' formula  { $$ = node(T_ADD, $1, $3); }
      | expr '-' formula  { $$ = node(T_SUB, $1, $3); }
      ;
prim  : NUM  { $$ = node(T_NUM, atoi(yytext), 0); }
      | var  { $$ = node(T_VAR, $1, 0); }
      | '(' expr ')' { $$ = $2; }
      ;
var : IDENT { $$ = lookup(yytext); }
    ;
