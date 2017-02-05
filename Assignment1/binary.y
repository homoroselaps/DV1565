%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires {
	#define YYDEBUG 1
	#include "Node.hpp"
	#include "Constants.h"
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

%token IF THEN ELSEIF ELSE END FOR DO REPEAT UNTIL
%token <std::string> ANY
%right <int> ASSIGN
%right LENGTH NOT RETURN
%left <Comparison> COMP
%token <int> NL

%left <int> AND
%left <int> OR
%left '+' '-'
%left '*' '/' '%'
%left '^'
%left '.'
%token <Value> CONSTEXP
%token <std::string> NAME
%token BLK
%token FUNCTION
%token DDDOT

%token EOOF 0 "end of file"

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
				| COMP { $$ = Node("COMP", std::to_string((int)$1) ); }
				| '[' { $$ = Node("Sign", "["); }
				| ']' { $$ = Node("Sign", "]"); }
				| '{' { $$ = Node("Sign", "{"); }
				| '}' { $$ = Node("Sign", "}"); }
				| '(' { $$ = Node("Sign", "("); }
				| ')' { $$ = Node("Sign", ")"); }
				| '+' { $$ = Node("Sign", "+"); }
				| '-' { $$ = Node("Sign", "-"); }
				| '/' { $$ = Node("Sign", "/"); }
				| '*' { $$ = Node("Sign", "*"); }
				| ',' { $$ = Node("Sign", ","); }
				| '.' { $$ = Node("Sign", "."); }
				| NAME { $$ = Node("NAME", $1); }
				| CONSTEXP { $$ = $1; }
				| NOT { $$ = Node("Not", ""); }
				| NL { $$ = Node("NL", ""); }
				| ASSIGN { $$ = Node("Assign", ""); }
				| LENGTH { $$ = Node("Length", ""); }
				| IF { $$ = Node("IF", ""); }
				| THEN { $$ = Node("THEN", ""); }
				| ELSE { $$ = Node("ELSE", ""); }
				| ELSEIF { $$ = Node("ELSEIF", ""); }
				| END { $$ = Node("END", ""); }
				| FOR { $$ = Node("FOR", ""); }
				| DO { $$ = Node("DO", ""); }
				| REPEAT { $$ = Node("REPEAT", ""); }
				| UNTIL { $$ = Node("UNTIL", ""); }
				| BLK { $$ = Node("BLK", ""); }
				| FUNCTION { $$ = Node("FUNCTION", ""); }
				| RETURN { $$ = Node("RETURN", ""); }
				| DDDOT { $$ = Node("DDDOT", ""); }
				;
%%
