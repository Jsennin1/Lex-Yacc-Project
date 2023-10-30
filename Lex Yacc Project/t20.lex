alpha [a-zA-Z]
digit [0-9]
white [\n\t ]
%%
while                      { return WHILE; }
do                      { return DO; }
if                         { return IF; }
read                       { return READ; }
print                      { return PRINT; }
printx                      { return PRINTX; }
{alpha}({alpha}|{digit})* { return IDENT; }
{digit}+                   { return NUM; }
[-+()=;{}<>*/%]            { return yytext[0]; }
"=="                       { return EQ; }
"&&"                       { return AND; }
"||"                       { return OR; }
{white}                    { ; }
%%