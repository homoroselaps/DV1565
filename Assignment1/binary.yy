%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code {
	std::vector<int> nums{0};
	int index = 0;
	#include <string>
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;
	void debug(std::string text) {
		std::cout << text << std::endl;
	}
}
%token <std::string> BIT
%token <std::string> SPACE
%type <std::string> number
%token END 0 "end of file"
%%
