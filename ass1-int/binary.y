%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires {
	#define YYDEBUG 1
	#include "Assignment.h"
	#include "BoolLiteral.h"
	#include "BreakStat.h"
	#include "Chunk.h"
	#include "BoolComparator.h"
	#include "Expr.h"
	#include "ExprList.h"
	#include "ExprStatement.h"
	#include "FieldCount.h"
	#include "FieldIndex.h"
	#include "FieldList.h"
	#include "FunctionCall.h"
	#include "FunctionBody.h"
	#include "ForLoop.h"
	#include "GlobalFunctionDef.h"
	#include "IfStatement.h"
	#include "NilLiteral.h"
	#include "Node.hpp"
	#include "NodeList.h"
	#include "NameList.h"
	#include "NumLiteral.h"
	#include "NumOperator.h"
	#include "NotOperator.h"
	#include "LengthOperator.h"
	#include "LocalAssignment.h"
	#include "LocalDef.h"
	#include "LocalFunctionDef.h"
	#include "ReturnStat.h"
	#include "RepeatLoop.h"
	#include "Selection.h"
	#include "Statement.h"
	#include "StringLiteral.h"
	#include "TableConstructor.h"
	#include "VarName.h"
	#include "VarIndex.h"
	#include "WhileLoop.h"

	#include <string>
	#include <memory>
}

%code {
	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;
	#define spc std::static_pointer_cast
	#define dpc std::dynamic_pointer_cast

	std::shared_ptr<Node> root;

	void debug(std::string text) {
		std::cout << text << std::endl;
	}
}
%type <std::shared_ptr<Node>> chunk __stat _semi laststat block stat __elseif varlist funcname
%type <std::shared_ptr<Node>> __dotname var namelist explist exp prefixexp functioncall args
%type <std::shared_ptr<Node>> function funcbody parlist tableconstructor fieldlist
%type <std::shared_ptr<Node>> __fieldsepfield field fieldsep binopexp unop

%token IF THEN ELSEIF ELSE END FOR DO REPEAT UNTIL BREAK IN WHILE LOCAL
%token <std::string> ANY

%token LENGTH NOT RETURN '='


%left <BoolComparatorType> OR
%left <BoolComparatorType> AND
%left <BoolComparatorType> COMP
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
						$$ = $1;
						root = $$;
 					}
					| __stat laststat _semi {
						auto node = dpc<Chunk>($1);
						node->addStatement(dpc<Statement>($2));
						$$ = spc<Node>(node);
						root = $$;
					}
					;

__stat  	: /* */ {
						auto node = std::make_shared<Chunk>();
						$$ = spc<Node>(node);
					}
					| __stat stat _semi {
						auto node = dpc<Chunk>($1);
						node->addStatement(dpc<Statement>($2));
						$$ = spc<Node>(node);
					}
					;

_semi			: /* */ { }
					| ';' { }
					;

laststat	: RETURN explist {
						auto node = std::make_shared<ReturnStat>(dpc<ExprList>($2));
						$$ = spc<Node>(node);
 					}
					| RETURN {
						auto node = std::make_shared<ReturnStat>();
						$$ = spc<Node>(node);
					}
					| BREAK {
						auto node = std::make_shared<BreakStat>();
						$$ = spc<Node>(node);
					}
					;

block			: chunk { $$ = $1; }
					;

stat			: varlist '=' explist {
						auto node = std::make_shared<Assignment>(dpc<Expr>($1), dpc<Expr>($3));
						$$ = spc<Node>(node);
					}
					| DO block END {
						$$ = $2;
					}
					| WHILE exp DO block END {
						auto node = std::make_shared<WhileLoop>(dpc<Expr>($2), dpc<Statement>($4));
						$$ = spc<Node>(node);
					}
					| REPEAT block UNTIL exp {
						auto node = std::make_shared<RepeatLoop>(dpc<Expr>($4), dpc<Statement>($2));
						$$ = spc<Node>(node);
					}
					| IF exp THEN block __elseif END {
						auto node = std::make_shared<Selection>();
						auto ifStat = std::make_shared<IfStatement>(dpc<Expr>($2),dpc<Statement>($4));
						node->addElseIfStat(ifStat);
						for (auto child : dpc<NodeList>($5)->getChildren()){
							node->addElseIfStat(dpc<IfStatement>(child));
						}
						$$ = spc<Node>(node);
					}
					| IF exp THEN block __elseif ELSE block END {
						auto node = std::make_shared<Selection>();
						auto ifStat = std::make_shared<IfStatement>(dpc<Expr>($2),dpc<Statement>($4));
						node->addElseIfStat(ifStat);
						for (auto child : dpc<NodeList>($5)->getChildren()){
							node->addElseIfStat(dpc<IfStatement>(child));
						}
						node->setElseStat(dpc<Statement>($7));
						$$ = spc<Node>(node);
					}
					| FOR NAME '=' exp ',' exp DO block END {
						auto node = std::make_shared<ForLoop>($2,
							dpc<Expr>($4),
							dpc<Expr>($6),
							dpc<Expr>(std::make_shared<NumLiteral>(1)),
							dpc<Statement>($8)
							);
						$$ = spc<Node>(node);
					}
					| FOR NAME '=' exp ',' exp ',' exp DO block END {
						auto node = std::make_shared<ForLoop>($2,
							dpc<Expr>($4),
							dpc<Expr>($6),
							dpc<Expr>($8),
							dpc<Statement>($10)
							);
						$$ = spc<Node>(node);
					}
					| FOR namelist IN explist DO block END {
						$$ = std::make_shared<Node>("forlist", "");
					}
					| FUNCTION funcname funcbody {
						auto node = std::make_shared<GlobalFunctionDef>(
							dpc<NameList>($2),
							dpc<FunctionBody>($3)
							);
						$$ = spc<Node>(node);
					}
					| LOCAL FUNCTION NAME funcbody {
						auto node = std::make_shared<LocalFunctionDef>(
							$3,
							dpc<FunctionBody>($4)
							);
						$$ = spc<Node>(node);
					}
					| LOCAL namelist {
						auto node = std::make_shared<LocalDef>(dpc<NameList>($2));
						$$ = spc<Node>(node);
					}
					| LOCAL namelist '=' explist {
						auto node = std::make_shared<LocalAssignment>(dpc<NameList>($2), dpc<Expr>($4));
						$$ = spc<Node>(node);
					}
					;

__elseif	: /* */ {
						auto node = std::make_shared<NodeList>();
						$$ = spc<Node>(node);
					}
					| __elseif ELSEIF exp THEN block {
						auto node = dpc<NodeList>($1);
						auto ifStat = std::make_shared<IfStatement>(dpc<Expr>($3),dpc<Statement>($5));
						node->addChild(ifStat);
						$$ = spc<Node>(node);
					}
					;

varlist		: var {
						auto node = std::make_shared<ExprList>();
						node->addExpression(dpc<Expr>($1));
						$$ = spc<Node>(node);
					}
					| varlist ',' var {
						auto node = dpc<ExprList>($1);
						node->addExpression(dpc<Expr>($3));
						$$ = spc<Node>(node);
					}
					;

funcname	: NAME __dotname {
							auto node = std::make_shared<NameList>();
							node->addString($1);
							for (auto name : dpc<NameList>($2)->getStrings()) {
								node->addString(name);
							}
							$$ = spc<Node>(node);
					}
					| NAME __dotname ':' NAME {
						auto node = std::make_shared<NameList>();
						node->addString($1);
						for (auto name : dpc<NameList>($2)->getStrings()) {
							node->addString(name);
						}
						node->setSpecial($4);
						$$ = spc<Node>(node);
					}
					;

__dotname	: /* */ {
						auto node = std::make_shared<NameList>();
						$$ = spc<Node>(node);
					}
					| __dotname '.' NAME {
						auto node = dpc<NameList>($1);
						node->addString($3);
						$$ = spc<Node>(node);
					}
					;

var 			: NAME {
						auto node = std::make_shared<VarName>($1);
						$$ = spc<Node>(node);
					}
					| prefixexp '[' exp ']' {
						auto node = std::make_shared<VarIndex>(spc<Expr>($1),spc<Expr>($3));
						$$ = spc<Node>(node);
					}
					| prefixexp '.' NAME {
						auto node = std::make_shared<VarIndex>(spc<Expr>($1),spc<Expr>(std::make_shared<StringLiteral>($3)));
						$$ = spc<Node>(node);
					}
					;

namelist	: NAME {
						auto node = std::make_shared<NameList>();
						node->addString($1);
						$$ = spc<Node>(node);
					}
					| namelist ',' NAME {
						auto node = dpc<NameList>($1);
						node->addString($3);
						$$ = spc<Node>(node);
					}
					;

explist		: exp {
						auto node = std::make_shared<ExprList>();
						node->addExpression(spc<Expr>($1));
						$$ = spc<Node>(node);
					}
					| explist ',' exp {
						auto node = dpc<ExprList>($1);
						node->addExpression(spc<Expr>($3));
						$$ = spc<Node>(node);
					}
					;

exp				: NIL { $$ = std::make_shared<NilLiteral>(); }
					| FALSE { $$ = std::make_shared<BoolLiteral>(false); }
					| TRUE { $$ = std::make_shared<BoolLiteral>(true); }
					| NUMBER { $$ = std::make_shared<NumLiteral>($1); }
					| STRING { $$ = std::make_shared<StringLiteral>($1); }
					| DDDOT { $$ = std::make_shared<StringLiteral>("..."); }
					| function { $$ = $1; }
					| prefixexp { $$ = $1; }
					| tableconstructor { $$ = $1; }
					| binopexp { $$ = $1; }
					| '-' exp {
						$$ = std::make_shared<NumOperator>(NumOperatorType::MINUS,spc<Expr>(std::make_shared<NumLiteral>(0)),dpc<Expr>($2));
					}
					| NOT exp {
						auto node = std::make_shared<NotOperator>(dpc<Expr>($2));
						$$ = spc<Node>(node);
					}
					| LENGTH exp {
						auto node = std::make_shared<LengthOperator>(dpc<Expr>($2));
						$$ = spc<Node>(node);
					}
					;

prefixexp	: var {
						$$ = $1;
					}
					| functioncall {
						$$ = $1;
					}
					| '(' exp ')' {
						$$ = $2;
					}
					;
/* to promote reduction to prefixexp instead of stat */
stat			: functioncall {
						auto node = std::make_shared<ExprStatement>(dpc<Expr>($1));
						$$ = spc<Node>(node);
					}
					;

functioncall			: prefixexp args {
										auto node = std::make_shared<FunctionCall>(dpc<Expr>($1),dpc<Expr>($2));
										$$ = spc<Node>(node);
									}
									| prefixexp ':' NAME args {
										auto node = std::make_shared<FunctionCall>(dpc<Expr>($1), $3, dpc<Expr>($4));
										$$ = spc<Node>(node);
									}
									;

args		: '(' ')' {
					auto node = std::make_shared<ExprList>();
					$$ = spc<Node>(node);
				}
				| '(' explist ')' {
					$$ = $2;
				}
				| tableconstructor {
					auto node = std::make_shared<Node>();
					$$ = spc<Node>(node);
				}
				| STRING {
					auto node = std::make_shared<StringLiteral>($1);
					$$ = spc<Node>(node);
				}
				;

function: FUNCTION funcbody {
					$$ = $2;
				}
				;

funcbody: '(' ')' block END {
					auto node = std::make_shared<FunctionBody>(std::make_shared<NameList>(),dpc<Chunk>($3));
					$$ = spc<Node>(node);
				}
				| '(' parlist ')' block END {
					auto node = std::make_shared<FunctionBody>(dpc<NameList>($2),dpc<Chunk>($4));
					$$ = spc<Node>(node);
				}
				;

parlist	: namelist {
					$$ = $1;
				}
				| namelist ',' DDDOT {
					auto node = dpc<NameList>($1);
					node->addString("...");
					$$ = spc<Node>(node);
				}
				| DDDOT {
					auto node = std::make_shared<NameList>();
					node->addString("...");
					$$ = spc<Node>(node);
				}
				;

tableconstructor	: '{' '}' {
										auto node = std::make_shared<TableConstructor>();
										$$ = spc<Node>(node);
									}
									| '{' fieldlist '}' {
										auto node = std::make_shared<TableConstructor>(dpc<FieldList>($2));
										$$ = spc<Node>(node);
									}
									;

fieldlist					: __fieldsepfield {
										$$ = $1;
									}
									| __fieldsepfield fieldsep {
										$$ = $1;
									}
									;

__fieldsepfield		: field {
										auto node = std::make_shared<FieldList>();
										node->addField(dpc<Field>($1));
										$$ = spc<Node>(node);
 									}
									| __fieldsepfield fieldsep field {
										auto node = dpc<FieldList>($1);
										node->addField(dpc<Field>($3));
										$$ = spc<Node>(node);
									}
									;

field		: '[' exp ']' '=' exp {
					auto node = std::make_shared<FieldIndex>(dpc<Expr>($2),dpc<Expr>($5));
					$$ = spc<Node>(node);
				}
				| NAME '=' exp {
					auto node = std::make_shared<FieldIndex>(std::make_shared<StringLiteral>($1),dpc<Expr>($3));
					$$ = spc<Node>(node);
				}
				| exp {
					auto node = std::make_shared<FieldCount>(dpc<Expr>($1));
					$$ = spc<Node>(node);
				}
				;

fieldsep: ',' { }
				| ';' { }
				;

binopexp: exp '+' exp {
					$$ = std::make_shared<NumOperator>(NumOperatorType::PLUS,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp '-' exp {
					$$ = std::make_shared<NumOperator>(NumOperatorType::MINUS,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp '*' exp {
					$$ = std::make_shared<NumOperator>(NumOperatorType::MUL,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp '/' exp {
					$$ = std::make_shared<NumOperator>(NumOperatorType::DIV,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp '^' exp {
					$$ = std::make_shared<NumOperator>(NumOperatorType::POW,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp '%' exp {
					$$ = std::make_shared<NumOperator>(NumOperatorType::MOD,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp CONCAT exp {
					$$ = std::make_shared<Node>("concat", "-");
					$$->add($1);
					$$->add($3);
				}
				| exp COMP exp {
					 $$ = std::make_shared<BoolComparator>($2,dpc<Expr>($1),dpc<Expr>($3));
				 }
				| exp AND	exp {
					$$ = std::make_shared<BoolComparator>($2,dpc<Expr>($1),dpc<Expr>($3));
				}
				| exp OR exp {
					 $$ = std::make_shared<BoolComparator>($2,dpc<Expr>($1),dpc<Expr>($3));
				 }
				;
%%
