#pragma once
#include <memory>
#include "Statement.h"
#include "Expr.h"
#include "Value.h"
#include "Table.h"
class ExprStatement : public Statement
{
	std::shared_ptr<Expr> m_expr;
public:

	ExprStatement(std::shared_ptr<Expr> expr):
		m_expr{expr}
	{
	}

	~ExprStatement()
	{
	}
	
	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) {
		m_expr->evaluate(environment);
		return std::make_shared<Value>();
	}
};

