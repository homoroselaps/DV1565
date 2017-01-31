%top{
    #include "binary.tab.hh"
    #include "string.h"
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput stack

%x VAR
%x SGLQOT
%x DBLQOT
%x COMMENT

%%
###				{ BEGIN(COMMENT); }
<COMMENT>[^#]*|[#]{1,2}|[#]{4,} {}
<COMMENT>###	{ BEGIN(0); }

\n        { return yy::parser::make_NL(yytext); }
[ \t]+		{ return yy::parser::make_BLANK(yytext); }
[;]				{ return yy::parser::make_SEMI(yytext); }
[|]				{ return yy::parser::make_PIPE(yytext); }
([^\n\t|\\'"; ]|(\\;)|(\\\|)|(\\\\)|(\\[ ])|(\\$))+     { return yy::parser::make_TEXT(yytext); }
<<EOF>>         { return yy::parser::make_END(); }
%%
