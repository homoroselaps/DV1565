%top{
    #include "binary.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
}

%option noyywrap nounput batch noinput
%%
[0-9]        { return yy::parser::make_NUM(yytext); }
\n|[A-Za-z]+  /* munch */
<<EOF>>      { return yy::parser::make_END(); }
%%