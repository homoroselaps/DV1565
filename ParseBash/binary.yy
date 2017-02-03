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
%type <Node> command
%type <Node> concat
%type <Node> pipeline
%type <Node> equal
%type <Node> subshell


%token <std::string> NL
%token <std::string> SGLQUOTE
%token <std::string> DBLQUOTE
%token <std::string> SEMI
%token <std::string> PIPE
%token <std::string> EQUAL
%token <std::string> VAR
%token <std::string> BLANK
%token <std::string> WORD
%token <std::string> SUBSHELL
%token <std::string> CLSBRACE
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

line		: pipeline {
					$$ = $1;
				}
				| line SEMI pipeline {
					if ($1.tag!="line") {
						$$ = Node("line", "");
						$$.children.push_back($1);
					} else {
						$$ = $1;
					}
					$$.children.push_back($3);
				}
				| line SEMI BLANK pipeline {
				if ($1.tag!="line") {
					$$ = Node("line", "");
					$$.children.push_back($1);
				} else {
					$$ = $1;
				}
				$$.children.push_back($4);
				}
				;

pipeline	: equal { $$ = $1; }
					| pipeline PIPE equal {
						$$ = Node("pipeline", "");
						$$.children.push_back($1);
						$$.children.push_back($3);
	 				}
					;

equal		: command { $$ = $1; }
				| unit EQUAL concat BLANK equal {
					$$ = Node("equal", "");
					$$.children.push_back($1);
					$$.children.push_back($3);
					$$.children.push_back($5);
				}
				;


command	: concat {
					$$ = Node("command", "");
					$$.children.push_back($1);
				}
				| command BLANK concat
				{
					$$ = $1;
					$$.children.push_back($3);
				}
				| equal {
					$$ = $1;
				}
				;

concat	: unit {
					$$ = $1;
				}
				| concat unit {
					if ($1.tag!="concatenate") {
						$$ = Node("concatenate", "");
						$$.children.push_back($1);
					} else {
						$$ = $1;
					}
					$$.children.push_back($2);
				}
				;

unit		: WORD 	{ $$ = Node("WORD", $1); }
				| VAR { $$ = Node("VAR", $1); }
				| SGLQUOTE { $$ = Node("SGLQUOTE", $1); }
				| DBLQUOTE { $$ = Node("DBLQUOTE", $1); }
				| EQUAL { $$ = Node("EQUAL", $1); }
				| subshell { $$ = $1; }
      	;

subshell: SUBSHELL stream CLSBRACE {
					$$ = Node("subshell", "");
					$$.children.push_back($2);
				}
				;
