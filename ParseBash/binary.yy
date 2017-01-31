%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires {
	#include "Node.hpp"
	#define YYDEBUG 1
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
%type <Node> unit
%type <Node> units
%type <Node> pipeline
%type <Node> expression

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

line		: expression {
					//$$ = Node("line", "");
					//$$.children.push_back($1);
					$$ = $1;
				}
				| line SEMI expression {
					$$ = Node("line", "");
					$$.children.push_back($1);
					$$.children.push_back($3);
				}
				;
expression	:	pipeline { $$ = $1; }
						| units { $$ = $1; }
						;

pipeline 	: expression PIPE expression {
						$$ = Node("pipeline", "");
						$$.children.push_back($1);
						$$.children.push_back($3);
					}
					;

units		: unit {
					$$ = Node("units", "");
					$$.children.push_back($1);
				}
				| units unit {
					$$ = $1;
					$$.children.push_back($2);
				}
				;

unit	: BLANK { $$ = Node("BLANK", ""); }
			| TEXT 	{ $$ = Node("TEXT", $1); }
      ;
