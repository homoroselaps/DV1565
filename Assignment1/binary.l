%top{
    #include "binary.tab.h"
    #include <string>
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput stack

%x SGLQOT
%x DBLQOT

%%
[']				{ BEGIN(SGLQOT); }
<SGLQOT>[^']*	{ return yy::parser::make_STRING(yytext); }
<SGLQOT>[']		{ BEGIN(0); }

["]				{ BEGIN(DBLQOT); }
<DBLQOT>[^"]*	{ return yy::parser::make_STRING(yytext); }
<DBLQOT>["]		{ BEGIN(0); }

[+\-*\/^%,\.\{\}\[\]\(\);:]     { return (yy::parser::token::yytokentype)yytext[0]; }
"..."      { return yy::parser::make_DDDOT(); }
".."       { return yy::parser::make_CONCAT(); }
[<]        { return yy::parser::make_COMP(BoolComparatorType::LESS); }
"<="       { return yy::parser::make_COMP(BoolComparatorType::LEQUAL); }
[>]        { return yy::parser::make_COMP(BoolComparatorType::GREATER); }
">="       { return yy::parser::make_COMP(BoolComparatorType::GEQUAL); }
"=="       { return yy::parser::make_COMP(BoolComparatorType::EQUAL); }
"~="       { return yy::parser::make_COMP(BoolComparatorType::NEQUAL); }
"and"      { return yy::parser::make_AND(BoolComparatorType::AND); }
"or"       { return yy::parser::make_OR(BoolComparatorType::OR); }
[=]        { return (yy::parser::token::yytokentype)yytext[0]; }
[#]        { return yy::parser::make_LENGTH(); }
"not"      { return yy::parser::make_NOT(); }
"nil"      { return yy::parser::make_NIL(); }
"true"     { return yy::parser::make_TRUE(); }
"false"    { return yy::parser::make_FALSE(); }
"if"       { return yy::parser::make_IF(); }
"elseif"   { return yy::parser::make_ELSEIF(); }
"then"     { return yy::parser::make_THEN(); }
"else"     { return yy::parser::make_ELSE(); }
"end"      { return yy::parser::make_END(); }
"for"      { return yy::parser::make_FOR(); }
"while"    { return yy::parser::make_WHILE(); }
"do"       { return yy::parser::make_DO(); }
"in"       { return yy::parser::make_IN(); }
"local"    { return yy::parser::make_LOCAL(); }
"repeat"   { return yy::parser::make_REPEAT(); }
"until"    { return yy::parser::make_UNTIL(); }
"function" { return yy::parser::make_FUNCTION(); }
"return"   { return yy::parser::make_RETURN(); }
"break"   { return yy::parser::make_BREAK(); }

[0-9]+     { return yy::parser::make_NUMBER(atoi(yytext)); }
[ \t]+     { /*return yy::parser::make_BLK();*/ }
[\n]+      { /*return yy::parser::make_NL();*/ }
[^0-9+\-*\/^%,;:\.\{\}\[\]\(\)<>=~ \t\n'"#][a-zA-Z0-9]*  { return yy::parser::make_NAME(yytext); }

<<EOF>>    { return yy::parser::make_EOOF(); }
%%
