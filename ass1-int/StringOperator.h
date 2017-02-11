#pragma once
#include "Expr.h"
class StringOperator :
	public Expr
{
	std::shared_ptr<Expr> m_left;
	std::shared_ptr<Expr> m_right;
public:

	StringOperator(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) : m_left{left}, m_right{right}
	{
	}

	virtual ~StringOperator()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		std::string left = m_left->evaluate(environment)->getString();
		std::string right = m_right->evaluate(environment)->getString();
		return std::make_shared<Value>(left + right);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_left));
		children.push_back(std::static_pointer_cast<Node>(m_right));
		return children;
	}
	virtual std::string to_string() override {
		return "Concat(Expression)";
	}
};

