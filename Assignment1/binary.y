%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires {
	#define YYDEBUG 1
	#include "Node.hpp"
	#include "Value.h"
	#include "BoolLiteral.h"
	#include "NumLiteral.h"
	#include "StringLiteral.h"
	#include "NilLiteral.h"
	#include <string>
	#include <memory>
}

%code {
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;

	std::shared_ptr<Node> root;

	void debug(std::string text) {
		std::cout << text << std::endl;
	}
}
%type <std::shared_ptr<Node>> chunk __stat _semi laststat block stat __elseif varlist funcname
%type <std::shared_ptr<Node>> __dotname var namelist explist exp prefixexp functioncall __args args
%type <std::shared_ptr<Node>> function funcbody parlist tableconstructor fieldlist
%type <std::shared_ptr<Node>> __fieldsepfield field fieldsep binopexp unop

%token IF THEN ELSEIF ELSE END FOR DO REPEAT UNTIL BREAK IN WHILE LOCAL
%token <std::string> ANY

%token LENGTH NOT RETURN '='


%left OR
%left AND
%left COMP
%right CONCAT
%left '+' '-'
%left '*' '%'
%left '/'
%right LENGTH NOT
%right '^'

%token NIL FALSE TRUE
%token <int> NUMBER
%token <std::string> STRING
%token <std::string> NAME
%token NL
%token BLK
%token FUNCTION
%token DDDOT

%token EOOF 0 "end of file"

%%

chunk			: __stat {
						$$ = std::make_shared<Node>("block", "");
						for (auto child : $1->getChildren()) {
							$$->add(child);
						}
						root = $$;
 					}
					| __stat laststat _semi {
						$$ = std::make_shared<Node>("block", "");
						for (auto child : $1->getChildren()) {
							$$->add(child);
						}
						$$->add($2);
						root = $$;
					}
					;

__stat  	: /* */ { $$ = std::make_shared<Node>(); }
					| __stat stat _semi {
						$$ = $1;
						if ($$->m_tag != "stats") {
							$$ = std::make_shared<Node>("stats", "");
						}
						$$->add($2);
					}
					;

_semi			: /* */ { }
					| ';' { }
					;

laststat	: RETURN explist { $$ = std::make_shared<Node>("return", ""); }
					| RETURN { $$ = std::make_shared<Node>("return", ""); }
					| BREAK { $$ = std::make_shared<Node>("break", ""); }
					;

block			: chunk { $$ = $1; }
					;

stat			: varlist '=' explist {
						$$ = std::make_shared<Node>("assign", "");
						$$->add($1);
						$$->add($3);
					}
					| DO block END {
						$$ = std::make_shared<Node>("DoEnd","");
						$$->add($2);
					}
					| WHILE exp DO block END {
						$$ = std::make_shared<Node>("While","");
						$$->add($2);
						$$->add($4);
					}
					| REPEAT block UNTIL exp {
						$$ = std::make_shared<Node>("Repeat", "");
						$$->add($2);
						$$->add($4);
					}
					| IF exp THEN block __elseif END {
						$$ = std::make_shared<Node>("selection", "");
						auto first = std::make_shared<Node>("if", "");
						first->add($2);
						first->add($4);
						$$->add(first);
						for (auto child : $5->getChildren()) {
							$$->add(child);
						}
					}
					| IF exp THEN block __elseif ELSE block END {
						$$ = std::make_shared<Node>("selection", "");
						auto first = std::make_shared<Node>("if", "");
						first->add($2);
						first->add($4);
						$$->add(first);
						for (auto child : $5->getChildren()) {
							$$->add(child);
						}
						auto last = std::make_shared<Node>("else", "");
						last->add($7);
						$$->add(last);
					}
					| FOR NAME '=' exp ',' exp DO block END {
						$$ = std::make_shared<Node>("forrange", "");
						//$$->add($2);
						$$->add($4);
						$$->add($6);
						$$->add($8);
					}
					| FOR NAME '=' exp ',' exp ',' exp DO block END {
						$$ = std::make_shared<Node>("foriter", "");
						//$$->add($2);
						$$->add($4);
						$$->add($6);
						$$->add($8);
						$$->add($10);
					}
					| FOR namelist IN explist DO block END {
						$$ = std::make_shared<Node>("forlist", "");
						$$->add($2);
						$$->add($4);
						$$->add($6);
					}
					| FUNCTION funcname funcbody {
						$$ = std::make_shared<Node>("funcdef", "");
						$$->add($2);
						$$->add($3);
					}
					| LOCAL FUNCTION NAME funcbody {
						$$ = std::make_shared<Node>("funcdeflocal", "");
						//$$->add($3);
						$$->add($4);
					}
					| LOCAL namelist {
						$$ = std::make_shared<Node>("deflocal", "");
						$$->add($2);
					}
					| LOCAL namelist '=' explist {
						$$ = std::make_shared<Node>("localassign", "");
						$$->add($2);
						$$->add($4);
					}
					;

__elseif	: /* */ { $$ = std::make_shared<Node>(); }
					| __elseif ELSEIF exp THEN block {
						$$ = $1;
						if ($$->m_tag != "elseiflist") {
							$$ = std::make_shared<Node>("elseiflist", "");
						}
						auto elseif = std::make_shared<Node>("if", "");
						elseif->add($3);
						elseif->add($5);
						$$->add(elseif);
					}
					;

varlist		: var {
						$$ = std::make_shared<Node>("varlist", "");
						$$->add($1);
					}
					| varlist ',' var {
						$$->add($3);
					}
					;

funcname	: NAME __dotname {
						$$ = std::make_shared<Node>("funcname", "");
						//$$->add($1);
						for (auto child : $2->getChildren()) {
								$$->add(child);
						}
					}
					| NAME __dotname ':' NAME {
						$$ = std::make_shared<Node>("funcnamethis", "");
						//$$->add($1);
						for (auto child : $2->getChildren()) {
								$$->add(child);
						}
						//$$->add($4);
					}
					;

__dotname	: /* */ { $$ = std::make_shared<Node>(); }
					| __dotname '.' NAME {
						$$ = $1;
						if ($$->m_tag != "funcname") {
							$$ = std::make_shared<Node>("funcname", "");
						}
						//$$->add($3);
					}
					;

var 			: NAME {
						$$ = std::make_shared<Node>("var","");
						//$$->add($1);
					}
					| prefixexp '[' exp ']' {
						$$ = std::make_shared<Node>("var","");
						auto accessor = std::make_shared<Node>("accindex", "");
						accessor->add($1);
						accessor->add($3);
						$$->add(accessor);
					}
					| prefixexp '.' NAME {
						$$ = std::make_shared<Node>("var","");
						auto accessor = std::make_shared<Node>("accmember", "");
						accessor->add($1);
						//accessor->add($3);
						$$->add(accessor);
					}
					;

namelist	: NAME {
						$$ = std::make_shared<Node>("namelist", "");
						//$$->add($1);
					}
					| namelist ',' NAME {
						$$ = $1;
						if ($$->m_tag != "namelist") {
							$$ = std::make_shared<Node>("namelist", "");
							$$->add($1);
						}
						//$$->add($3);
					}
					;

explist		: exp {
						$$ = std::make_shared<Node>("explist", "");
						$$->add($1);
					}
					| explist ',' exp {
						$$ = $1;
						if ($$->m_tag != "explist") {
							$$ = std::make_shared<Node>("explist", "");
							$$->add($1);
						}
						$$->add($3);
					}
					;

exp				: NIL { $$ = std::make_shared<NilLiteral>(); }
					| FALSE { $$ = std::make_shared<BoolLiteral>(false); }
					| TRUE { $$ = std::make_shared<BoolLiteral>(true); }
					| NUMBER { $$ = std::make_shared<NumLiteral>($1); }
					| STRING { $$ = std::make_shared<StringLiteral>($1); }
					| DDDOT { $$ = std::make_shared<Node>("DDDOT", ""); }
					| function { $$ = $1; }
					| prefixexp { $$ = $1; }
					| tableconstructor { $$ = $1; }
					| binopexp {
						$$ = $1;
					}
					| unop exp {
						$$ = $1;
						$$->add($2);
					}
					;

prefixexp	: var {
						$$ = std::make_shared<Node>("prefixexp","");
						$$->add($1);
						$$ = $1;
					}
					| functioncall {
						$$ = std::make_shared<Node>("prefixexp","");
						$$->add($1);
						$$ = $1;
					}
					| '(' exp ')' {
						$$ = std::make_shared<Node>("prefixexp","");
						$$->add($2);
						$$ = $2;
					}
					;
/* to promote reduction to prefixexp instead of stat */
stat			: functioncall { $$ = $1; }
					;

functioncall			: prefixexp args {
										$$ = std::make_shared<Node>("functioncall", "");
										$$->add($1);
										$$->add($2);
									}
									| prefixexp ':' NAME args {
										$$ = std::make_shared<Node>("functioncall", "");
										$$->add($1);
										//$$->add($3);
										$$->add($4);
									}
									;

__args	: args {
					$$ = std::make_shared<Node>("acclist", "");
					$$->add($1);
				}
				| __args args  {
					$$->add($2);
			 	}
				;

args		: '(' ')' { $$ = std::make_shared<Node>("args",""); }
				| '(' explist ')' {
					$$ = std::make_shared<Node>("args","");
					for (auto child : $2->getChildren()) {
						$$->add(child);
					}
				}
				| tableconstructor {
					$$ = std::make_shared<Node>("args","");
					$$->add($1);
				}
				| STRING {
					$$ = std::make_shared<Node>("args","");
					//$$->add($1);
				}
				;

function: FUNCTION funcbody {
					$$ = $2;
				}
				;

funcbody: '(' ')' block END {
					$$ = std::make_shared<Node>("function", "");
					$$->add(std::make_shared<Node>("parlist",""));
					$$->add($3);
				}
				| '(' parlist ')' block END {
					$$ = std::make_shared<Node>("function", "");
					$$->add($2);
					$$->add($4);
				}
				;

parlist	: namelist {
					$$ = std::make_shared<Node>("parlist", "");
					for (auto child : $1->getChildren()) {
						$$->add(child);
					}
				}
				| namelist ',' DDDOT {
					$$ = std::make_shared<Node>("parlist", "");
					for (auto child : $1->getChildren()) {
						$$->add(child);
					}
					//$$->add($3);
				}
				| DDDOT {
					$$ = std::make_shared<Node>("namelist", "");
					//$$->add($1);
				}
				;

tableconstructor	: '{' '}' { $$ = std::make_shared<Node>("tableconstructor", ""); }
									| '{' fieldlist '}' {
										$$ = std::make_shared<Node>("tableconstructor", "");
										$$->add($2);
									}
									;

fieldlist					: field __fieldsepfield {
										$$ = std::make_shared<Node>("fieldlist", "");
										$$->add($1);
										for (auto child : $2->getChildren()) {
												$$->add(child);
										}
									}
									| field __fieldsepfield fieldsep {
										$$ = std::make_shared<Node>("fieldlist", "");
										$$->add($1);
										for (auto child : $2->getChildren()) {
												$$->add(child);
										}
									}
									;

__fieldsepfield		: /* */ { $$ = std::make_shared<Node>(); }
									| __fieldsepfield fieldsep field {
										$$ = $1;
										if ($$->m_tag != "fieldlist") {
											$$ = std::make_shared<Node>("fieldlist", "");
										}
										$$->add($3);
									}
									;

field		: '[' exp ']' '=' exp {
					$$ = std::make_shared<Node>("IndexValue", "");
					$$->add($2);
					$$->add($5);
				}
				| NAME '=' exp {
					$$ = std::make_shared<Node>("KeyValue", "");
					//$$->add($1);
					$$->add($3);
				}
				| exp { $$ = $1; }
				;

fieldsep: ',' { }
				| ';' { }
				;

binopexp: exp '+' exp {
					$$ = std::make_shared<Node>("binop", "+");
					$$->add($1);
					$$->add($3);
				}
				| exp '-' exp {
					$$ = std::make_shared<Node>("binop", "-");
					$$->add($1);
					$$->add($3);
				}
				| exp '*' exp {
					$$ = std::make_shared<Node>("binop", "*");
					$$->add($1);
					$$->add($3);
				}
				| exp '/' exp {
					$$ = std::make_shared<Node>("binop", "/");
					$$->add($1);
					$$->add($3);
				}
				| exp '^' exp {
					$$ = std::make_shared<Node>("binop", "^");
					$$->add($1);
					$$->add($3);
				}
				| exp '%' exp {
					$$ = std::make_shared<Node>("binop", "%%");
					$$->add($1);
					$$->add($3);
				}
				| exp CONCAT exp {
					$$ = std::make_shared<Node>("concat", "-");
					$$->add($1);
					$$->add($3);
				}
				| exp COMP exp {
					 $$ = std::make_shared<Node>("COMP", "irgendwas");;
					 $$->add($1);
					 $$->add($3);
				 }
				| exp AND	exp {
					$$ = std::make_shared<Node>("binop", "and");;
					$$->add($1);
					$$->add($3);
				}
				| exp OR exp {
					 $$ = std::make_shared<Node>("binop", "or");;
					 $$->add($1);
					 $$->add($3);
				 }
				;

unop		: '-' { $$ = std::make_shared<Node>("unop", "-"); }
				| NOT	{ $$ = std::make_shared<Node>("NOT", ""); }
				| LENGTH { $$ = std::make_shared<Node>("LENGTH", "("); }
				;

%%
