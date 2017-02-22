#pragma once
#include "Expr.h"
class NotOperator :
	public Expr
{
	std::shared_ptr<Expr> m_expr;
public:

	NotOperator(std::shared_ptr<Expr> expr) : m_expr{ expr }
	{
	}

	virtual ~NotOperator()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		auto res = m_expr->evaluate(environment);
		return std::make_shared<Value>(!res->getBool());
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_expr));
		return children;
	}
	virtual std::string to_string() override {
		return "NotOperator(Expression)";
	}
};
