%top{
    #include "binary.tab.h"
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput
%%
[0-9]+         { return yy::parser::make_ANY(yytext); }
[ \t]+         /* nix */
[\n]+             { return yy::parser::make_ANY(yytext); }
<<EOF>>     { return yy::parser::make_END(); }
%%
