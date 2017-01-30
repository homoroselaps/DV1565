%top{
    #include "binary.tab.hh"
    #include "string.h"
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput

%x VAR

%%
[$]				{ BEGIN(VAR); }
<VAR>[a-zA-Z]+  { BEGIN(INITIAL); return yy::parser::make_VAR(yytext); }
\n        	   	{ return yy::parser::make_NL(strlen(yytext)); }
[ \t]+			{ return yy::parser::make_BLANK(strlen(yytext)); }
[;]				{ return yy::parser::make_SEMI(yytext); }
[|]				{ return yy::parser::make_PIPE(yytext); }
([^$\n|;\\ ]|(\\;)|(\\\|)|(\\\\)|(\\[ ])|(\\$))+     { return yy::parser::make_TEXT(yytext); }
<<EOF>>         { return yy::parser::make_END(); }
%%
