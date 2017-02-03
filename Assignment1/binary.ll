%top{
    #include "binary.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput
%%
[0-9]+         { return yy::parser::make_DIGIT(yytext); }
[ \t]+         /* nix */
[\n]+             { return yy::parser::make_NL(yytext); }
<<EOF>>     { return yy::parser::make_END(); }
%%
