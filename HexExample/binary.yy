%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code {
	unsigned int total = 0;
	#include <string>
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;

	void addNUM(char character) {
		total += character-'0';
	}

	void addCHR(char character) {
		total += character-'A'+10;
	}

	void shift() {
		total = total<<4;
	}
}
%token <std::string> START
%token <std::string> NUM
%token <std::string> CHR

%type <std::string> number
%type <std::string> hex
%type <std::string> sym

%token END 0 "end of file"
%%
hex    : START number { }
	   | number       { }
	   ;

number : NUM          { addNUM($1[0]); }   
	   | CHR          { addCHR($1[0]); }
       | number NUM		{ shift(); addNUM($2[0]); }
       | number CHR		{ shift(); addCHR($2[0]); }
       ;