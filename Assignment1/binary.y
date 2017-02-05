%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires {
	#define YYDEBUG 1
	#include "Node.hpp"
	#include <string>
}

%code {
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;

	Node root;

	void debug(std::string text) {
		std::cout << text << std::endl;
	}
}
%type <Node> all
%type <Node> unit

%token <std::string> ANY
%token END 0 "end of file"
%%
all		 	: unit { $$ = $1;
					root = $$;
 				}
				| all unit {
					$$ = $1;
					if ($1.tag != "all" ) {
						$$ = Node("all", "");
						$$.add($1);
					}
					$$.add($2);
					root = $$;
				 }
				;

unit		: ANY { $$ = Node("ANY", $1); }
				;
%%
