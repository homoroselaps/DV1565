%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires {
	#include "Node.hpp"
}

%code {
	#include <string>
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;

	Node root;

	void debug(std::string text) {
		std::cout << text << std::endl;
	}
}
%type <Node> stream
%type <Node> line
%type <Node> optline
%type <Node> part

%token <std::string> NL
%token <std::string> SGLQUOTE
%token <std::string> DBLQUOTE
%token <std::string> SEMI
%token <std::string> PIPE
%token <std::string> VAR
%token <std::string> BLANK
%token <std::string> TEXT
%token END 0 "end of file"
%%

stream	: optline {
					$$ = Node("stream","");
					$$.children.push_back($1);
					root = $$;
				}
				| stream NL optline {
					$$ = root;
					$$.children.push_back($3);
					root = $$;
				}
				;

optline	: /* empty*/ { $$ = Node("optline","empty"); }
				| line {
					$$ = Node("optline", "has line");
					$$.children.push_back($1);
				}
				;

line		: part {
					$$ = $1;
				}
				| line part {
					$$ = Node("line", "");
					$$.children.push_back($1);
					$$.children.push_back($2);
				}
				;

part	: BLANK { $$ = Node("BLANK", ""); }
			| TEXT 	{ $$ = Node("TEXT", $1); }
			| VAR 	{ $$ = Node("VAR", $1); }
			| SEMI 	{ $$ = Node("SEMI", $1); }
			| PIPE 	{ $$ = Node("PIPE", $1); }
       	;
