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
%type <Node> chunk __stat _semi laststat block stat __elseif varlist funcname
%type <Node> __dotname var namelist explist exp prefixexp functioncall args
%type <Node> function funcbody parlist tableconstructor fieldlist
%type <Node> __fieldsepfield field fieldsep binop unop

%token IF THEN ELSEIF ELSE END FOR DO REPEAT UNTIL BREAK IN WHILE LOCAL
%token <std::string> ANY

%token LENGTH NOT RETURN '='


%left <Binop> COMP
%left <Binop> AND OR
%left '+' '-'
%left '*' '/' '%'
%right '^'
%right CONCAT

%token <Value> NIL FALSE TRUE NUMBER STRING
%token <Name> NAME
%token NL
%token BLK
%token FUNCTION
%token <Node> DDDOT

%token EOOF 0 "end of file"

%%

chunk			: __stat {
						$$ = Node("block", "");
						for (auto & child : $1.children) {
							$$.add(child);
						}
						root = $$;
 					}
					| __stat laststat _semi {
						$$ = Node("block", "");
						for (auto & child : $1.children) {
							$$.add(child);
						}
						$$.add($2);
						root = $$;
					}
					;

__stat  	: /* */ { $$ = Node(); }
					| __stat stat _semi {
						$$ = $1;
						if ($$.tag != "stats") {
							$$ = Node("stats", "");
						}
						$$.add($2);
					}
					;

_semi			: /* */ { }
					| ';' { }
					;

laststat	: RETURN explist { $$ = Node("return", ""); }
					| RETURN { $$ = Node("return", ""); }
					| BREAK { $$ = Node("break", ""); }
					;

block			: chunk { $$ = $1; }
					;

stat			: varlist '=' explist {
						$$ = Node("assign", "");
						$$.add($1);
						$$.add($3);
					}
					| functioncall { $$ = $1; }
					| DO block END {
						$$ = Node("DoEnd","");
						$$.add($2);
					}
					| WHILE exp DO block END {
						$$ = Node("While","");
						$$.add($2);
						$$.add($4);
					}
					| REPEAT block UNTIL exp {
						$$ = Node("Repeat", "");
						$$.add($2);
						$$.add($4);
					}
					| IF exp THEN block __elseif END {
						$$ = Node("selection", "");
						auto first = Node("if", "");
						first.add($2);
						first.add($4);
						$$.add(first);
						for (auto & child : $5.children) {
							$$.add(child);
						}
					}
					| IF exp THEN block __elseif ELSE block END {
						$$ = Node("selection", "");
						auto first = Node("if", "");
						first.add($2);
						first.add($4);
						$$.add(first);
						for (auto & child : $5.children) {
							$$.add(child);
						}
						auto last = Node("else", "");
						last.add($7);
						$$.add(last);
					}
					| FOR NAME '=' exp ',' exp DO block END {
						$$ = Node("forrange", "");
						$$.add($2);
						$$.add($4);
						$$.add($6);
						$$.add($8);
					}
					| FOR NAME '=' exp ',' exp ',' exp DO block END {
						$$ = Node("foriter", "");
						$$.add($2);
						$$.add($4);
						$$.add($6);
						$$.add($8);
						$$.add($10);
					}
					| FOR namelist IN explist DO block END {
						$$ = Node("forlist", "");
						$$.add($2);
						$$.add($4);
						$$.add($6);
					}
					| FUNCTION funcname funcbody {
						$$ = Node("funcdef", "");
						$$.add($2);
						$$.add($3);
					}
					| LOCAL FUNCTION NAME funcbody {
						$$ = Node("funcdeflocal", "");
						$$.add($3);
						$$.add($4);
					}
					| LOCAL namelist {
						$$ = Node("deflocal", "");
						$$.add($2);
					}
					| LOCAL namelist '=' explist {
						$$ = Node("localassign", "");
						$$.add($2);
						$$.add($4);
					}
					;

__elseif	: /* */ { $$ = Node(); }
					| __elseif ELSEIF exp THEN block {
						$$ = $1;
						if ($$.tag != "elseiflist") {
							$$ = Node("elseiflist", "");
						}
						auto elseif = Node("if", "");
						elseif.add($3);
						elseif.add($5);
						$$.add(elseif);
					}
					;

varlist		: var {
						$$ = Node("varlist", "");
						$$.add($1);
					}
					| varlist ',' var {
						$$ = $1;
						if ($$.tag != "varlist") {
							$$ = Node("varlist", "");
							$$.add($1);
						}
						$$.add($3);
					}
					;

funcname	: NAME __dotname {
						$$ = Node("funcname", "");
						$$.add($1);
						for (auto & child : $2.children) {
								$$.add(child);
						}
					}
					| NAME __dotname ':' NAME {
						$$ = Node("funcnamethis", "");
						$$.add($1);
						for (auto & child : $2.children) {
								$$.add(child);
						}
						$$.add($4);
					}
					;

__dotname	: /* */ { $$ = Node(); }
					| __dotname '.' NAME {
						$$ = $1;
						if ($$.tag != "funcname") {
							$$ = Node("funcname", "");
						}
						$$.add($3);
					}
					;

var 			: NAME {
						$$ = Node("var","");
						$$.add($1);
					}
					| prefixexp '[' exp ']' {
						$$ = Node("var","");
						auto accessor = Node("accindex", "");
						accessor.add($1);
						accessor.add($3);
						$$.add(accessor);
					}
					| prefixexp '.' NAME {
						$$ = Node("var","");
						auto accessor = Node("accmember", "");
						accessor.add($1);
						accessor.add($3);
						$$.add(accessor);
					}
					;

namelist	: NAME {
						$$ = Node("namelist", "");
						$$.add($1);
					}
					| namelist ',' NAME {
						$$ = $1;
						if ($$.tag != "namelist") {
							$$ = Node("namelist", "");
							$$.add($1);
						}
						$$.add($3);
					}
					;

explist		: exp {
						$$ = Node("explist", "");
						$$.add($1);
					}
					| explist ',' exp {
						$$ = $1;
						if ($$.tag != "explist") {
							$$ = Node("explist", "");
							$$.add($1);
						}
						$$.add($3);
					}
					;

exp				: NIL { $$ = $1; }
					| FALSE { $$ = $1; }
					| TRUE { $$ = $1; }
					| NUMBER { $$ = $1; }
					| STRING { $$ = $1; }
					| DDDOT { $$ = Node("DDDOT", ""); }
					| function { $$ = $1; }
					| prefixexp { $$ = $1; }
					| tableconstructor { $$ = $1; }
					| exp binop exp {
						$$ = $2;
						$$.add($1);
						$$.add($3);
					}
					| unop exp {
						$$ = $1;
						$$.add($2);
					}
					;

prefixexp	: var {
						$$ = Node("prefixexp","");
						$$.add($1);
						$$ = $1;
					}
					| functioncall {
						$$ = Node("prefixexp","");
						$$.add($1);
						$$ = $1;
					}
					| '(' exp ')' {
						$$ = Node("prefixexp","");
						$$.add($2);
						$$ = $2;
					}
					;

functioncall			: prefixexp args {
										$$ = Node("functioncall", "");
										$$.add($1);
										$$.add($2);
									}
									| prefixexp ':' NAME args {
										$$ = Node("functioncall", "");
										$$.add($1);
										$$.add($3);
										$$.add($4);
									}
									;

args		: '(' ')' { $$ = Node("args",""); }
				| '(' explist ')' {
					$$ = Node("args","");
					for (auto & child : $2.children) {
						$$.add(child);
					}
				}
				| tableconstructor {
					$$ = Node("args","");
					$$.add($1);
				}
				| STRING {
					$$ = Node("args","");
					$$.add($1);
				}
				;

function: FUNCTION funcbody {
					$$ = $2;
				}
				;

funcbody: '(' ')' block END {
					$$ = Node("function", "");
					$$.add(Node("parlist",""));
					$$.add($3);
				}
				| '(' parlist ')' block END {
					$$ = Node("function", "");
					$$.add($2);
					$$.add($4);
				}
				;

parlist	: namelist {
					$$ = Node("parlist", "");
					for (auto & child : $1.children) {
						$$.add(child);
					}
				}
				| namelist ',' DDDOT {
					$$ = Node("parlist", "");
					for (auto & child : $1.children) {
						$$.add(child);
					}
					$$.add($3);
				}
				| DDDOT {
					$$ = Node("namelist", "");
					$$.add($1);
				}
				;

tableconstructor	: '{' '}' { $$ = Node("tableconstructor", ""); }
									| '{' fieldlist '}' {
										$$ = Node("tableconstructor", "");
										$$.add($2);
									}
									;

fieldlist					: field __fieldsepfield {
										$$ = Node("fieldlist", "");
										$$.add($1);
										for (auto & child : $2.children) {
												$$.add(child);
										}
									}
									| field __fieldsepfield fieldsep {
										$$ = Node("fieldlist", "");
										$$.add($1);
										for (auto & child : $2.children) {
												$$.add(child);
										}
									}
									;

__fieldsepfield		: /* */ { $$ = Node(); }
									| __fieldsepfield fieldsep field {
										$$ = $1;
										if ($$.tag != "fieldlist") {
											$$ = Node("fieldlist", "");
										}
										$$.add($3);
									}
									;

field		: '[' exp ']' '=' exp {
					$$ = Node("IndexValue", "");
					$$.children.push_back($2);
					$$.children.push_back($5);
				}
				| NAME '=' exp {
					$$ = Node("KeyValue", "");
					$$.children.push_back($1);
					$$.children.push_back($3);
				}
				| exp { $$ = $1; }
				;

fieldsep: ',' { }
				| ';' { }
				;

binop		: '+' { $$ = Node("binop", "+"); }
				| '-' { $$ = Node("binop", "-"); }
				| '*' { $$ = Node("binop", "*"); }
				| '/' { $$ = Node("binop", "/"); }
				| '^' { $$ = Node("binop", "^"); }
				| '%' { $$ = Node("binop", "%%"); }
				| CONCAT { $$ = Node("concat", ".."); }
				| COMP{ $$ = $1; }
				| AND	{ $$ = $1; }
				| OR	{ $$ = $1; }
				;

unop		: '-' { $$ = Node("unop", "-"); }
				| NOT	{ $$ = Node("NOT", ""); }
				| LENGTH { $$ = Node("LENGTH", "("); }
				;

%%
