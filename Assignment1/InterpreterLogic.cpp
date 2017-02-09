// InterpreterLogic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "Table.h"
#include "Library.h"
#include "Chunk.h"
#include "ExprStatement.h"
#include "FunctionCall.h"
#include "VarName.h"
#include "StringLiteral.h"
#include "NumOperator.h"
#include "NumLiteral.h"

#define spc std::static_pointer_cast

int main()
{
	auto env = std::make_shared<Table>();
	Library::load(env);
	auto root = std::make_shared<Chunk>();
	auto call = std::make_shared<Call>(ArgumentType::LISTARG);
	auto str = std::make_shared<StringLiteral>("Hello World!");
	call->addArgument(std::static_pointer_cast<Expr>(str));
	auto plus = std::make_shared<NumOperator>(NumOperatorType::PLUS,
		spc<Expr>(std::make_shared<NumLiteral>(1.0f)),
		spc<Expr>(std::make_shared<NumOperator>(NumOperatorType::MUL,
			spc<Expr>(std::make_shared<NumLiteral>(2.0f)),
			spc<Expr>(std::make_shared<NumOperator>(NumOperatorType::DIV,
				spc<Expr>(std::make_shared<NumLiteral>(10.0)),
				spc<Expr>(std::make_shared<NumOperator>(NumOperatorType::PLUS,
					spc<Expr>(std::make_shared<NumLiteral>(5.0)),
					spc<Expr>(std::make_shared<NumLiteral>(3.0))
				))
			))
		))
	);
	call->addArgument(spc<Expr>(plus));
	
	auto funcCall = std::make_shared<FunctionCall>(
		std::static_pointer_cast<Expr>(
			std::make_shared<VarName>("print")),
		std::static_pointer_cast<Accessor>(call));
	auto expSt = std::make_shared<ExprStatement>(funcCall);
	root->addStatement(expSt);
	ExecControl control = ExecControl::NONE;
	root->execute(env, control);
	std::static_pointer_cast<Node>(root)->dump();
    return 0;
}

