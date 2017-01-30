%top{
    #include "binary.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput
%%
0x           { return yy::parser::make_START(yytext); }
[0-9]        { return yy::parser::make_NUM(yytext); }
[A-Z]        { return yy::parser::make_CHR(yytext); }
\n           /* munch */
<<EOF>>      { return yy::parser::make_END(); }
%%