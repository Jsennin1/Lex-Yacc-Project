digit [0-9]
alpha [a-zA-Z]
white [\n\t ]
%%
{digit}+ { return NUM; }
{alpha}({alpha}|{digit})* { return IDENT; }
{white} { ; }
%%