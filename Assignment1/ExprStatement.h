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

	virtual ~ExprStatement()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, ExecControl &control) {
		m_expr->evaluate(environment);
		return std::make_shared<Value>();
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_expr));
		return children;
	}

	virtual std::string to_string() override {
		return "ExprStatement(Statement)";
	}
};
