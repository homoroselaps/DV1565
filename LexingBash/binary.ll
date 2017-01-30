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

[']				{ BEGIN(SGLQOT); }
<SGLQOT>[^'$]*	{ return yy::parser::make_SGLQUOTE(yytext); }
<SGLQOT>[']		{ BEGIN(0); }

["]				{ BEGIN(DBLQOT); }
<DBLQOT>[^"$]*	{ return yy::parser::make_DBLQUOTE(yytext); }
<DBLQOT>["]		{ BEGIN(0); }

<INITIAL,SQLQOT,DBLQOT>[$] { yy_push_state(VAR); }
<VAR>[a-zA-Z]+  { yy_pop_state(); return yy::parser::make_VAR(yytext); }

\n        	   	{ return yy::parser::make_NL(strlen(yytext)); }
[ \t]+			{ return yy::parser::make_BLANK(strlen(yytext)); }
[;]				{ return yy::parser::make_SEMI(yytext); }
[|]				{ return yy::parser::make_PIPE(yytext); }
([^$\n|;\\'" ]|(\\;)|(\\\|)|(\\\\)|(\\[ ])|(\\$))+     { return yy::parser::make_TEXT(yytext); }
<<EOF>>         { return yy::parser::make_END(); }
%%
