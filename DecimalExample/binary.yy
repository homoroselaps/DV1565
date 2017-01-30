%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code {
	unsigned int total = 0;
	#include <string>
	#include <cmath>
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;

	void shift() {
		total *= 10;
	}
}
%token <std::string> NUM
%type <std::string> number
%token END 0 "end of file"
%%
number : NUM			{          total += $1[0]-'0'; }
       | number NUM		{ shift(); total += $2[0]-'0'; }
       ;