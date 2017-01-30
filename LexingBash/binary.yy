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
%type <std::string> input
%type <std::string> part
%token <int> NL
%token <std::string> TEXT
%token <std::string> SEMI
%token <std::string> PIPE
%token <std::string> VAR
%token <int> BLANK
%token END 0 "end of file"
%%

input 	: /* NISCHT */ { }
		| input part { }
       	;

part	: NL { std::cout << "NL" << std::endl; }
		| BLANK { std::cout << "Blank " << $1 << " chars" << std::endl; }
		| TEXT { std::cout << "Text: ->" << $1 << "<-" << std::endl; }
		| VAR { std::cout << "Var: ->" << $1 << "<-" << std::endl; }
		| SEMI { std::cout << "Semi" << std::endl; }
		| PIPE { std::cout << "Pipe" << std::endl; }
       	;