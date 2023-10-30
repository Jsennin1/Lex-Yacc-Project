alpha [a-zA-Z]
digit [0-9]
white [\t ]
%%
{alpha}({alpha}|{digit})* { return IDENT; }
{digit}+ { return NUM; }
[\n/+*^()=-] { return yytext[0]; }
{white} { ; }
%%