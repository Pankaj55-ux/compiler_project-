%{
#include "../parser/parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"return"        { return RETURN; }
"<"             { return '<'; }
">"             { return '>'; }

"("             { return '('; }
")"             { return ')'; }

"{"             { return '{'; }
"}"             { return '}'; }

"for"           { return FOR; }

[0-9]+          { strcpy(yylval.text, yytext); return NUMBER; }

[a-zA-Z_][a-zA-Z0-9_]*  { strcpy(yylval.text, yytext); return IDENTIFIER; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }

";"             { return ';'; }
"="             { return '='; }

[ \t\n]+        ;

.               { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}