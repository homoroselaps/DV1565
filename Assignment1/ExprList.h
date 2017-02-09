#pragma once
#include "Expr.h"
#include "MultiValue.h"

class ExprList : public Expr
{
	std::vector<std::shared_ptr<Expr>> m_exprs;
public:

	ExprList()
	{
		m_exprs = std::vector<std::shared_ptr<Expr>>{};
	}

	void addExpression(std::shared_ptr<Expr> expr) {
		m_exprs.push_back(expr);
	}

	virtual ~ExprList()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) {
		auto values = std::vector<std::shared_ptr<Value>>{};
		for (auto expr : m_exprs) {
			values.push_back(expr->evaluate(environment));
		}
		return std::make_shared<MultiValue>(values);
	};

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		for (auto child : m_exprs) {
			children.push_back(std::static_pointer_cast<Node>(child));
		}
		return children;
	}

	virtual std::string to_string() override {
		return "ExprList(Expression)";
	}

};

