%top{
    #include "binary.tab.h"
    #include "Constants.h"
    #include <string>
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput stack

%x SGLQOT
%x DBLQOT

%%
[']				{ BEGIN(SGLQOT); }
<SGLQOT>[^']*	{ return yy::parser::make_CONSTEXP(yytext); }
<SGLQOT>[']		{ BEGIN(0); }

["]				{ BEGIN(DBLQOT); }
<DBLQOT>[^"]*	{ return yy::parser::make_CONSTEXP(yytext); }
<DBLQOT>["]		{ BEGIN(0); }

[+\-*\/^%,\.\{\}\[\]\(\);:]     { return (yy::parser::token::yytokentype)yytext[0]; }
"..."      { return yy::parser::make_DDDOT(); }
[<]        { return yy::parser::make_COMP(LESS); }
"<="       { return yy::parser::make_COMP(LEQUAL); }
[>]        { return yy::parser::make_COMP(GREATER); }
">="       { return yy::parser::make_COMP(GEQUAL); }
"=="       { return yy::parser::make_COMP(EQUAL); }
"~="       { return yy::parser::make_COMP(NEQUAL); }
"and"      { return yy::parser::make_AND(0); }
"or"       { return yy::parser::make_OR(0); }
[=]        { return yy::parser::make_ASSIGN(0); }
[#]        { return yy::parser::make_LENGTH(); }
"not"      { return yy::parser::make_NOT(); }
"true"     { return yy::parser::make_CONSTEXP(true); }
"false"    { return yy::parser::make_CONSTEXP(false); }
"if"       { return yy::parser::make_IF(); }
"elseif"   { return yy::parser::make_ELSEIF(); }
"then"     { return yy::parser::make_THEN(); }
"else"     { return yy::parser::make_ELSE(); }
"end"      { return yy::parser::make_END(); }
"for"      { return yy::parser::make_FOR(); }
"do"       { return yy::parser::make_DO(); }
"repeat"   { return yy::parser::make_REPEAT(); }
"until"    { return yy::parser::make_UNTIL(); }
"function" { return yy::parser::make_FUNCTION(); }
"return"   { return yy::parser::make_RETURN(); }

[0-9]+   { return yy::parser::make_CONSTEXP(Value(atoi(yytext))); }
[ \t]+    { return yy::parser::make_BLK(); }
[\n]+      { return yy::parser::make_NL(0); }
[^0-9+\-*\/^%,;\.\{\}\[\]\(\)<>=~ \t\n'"#][a-zA-Z0-9]*  { return yy::parser::make_NAME(yytext); }

<<EOF>>    { return yy::parser::make_EOOF(); }
%%
