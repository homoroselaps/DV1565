#pragma once
#include "../Expr.h"

class LengthOperator :
	public Expr
{
	std::shared_ptr<Expr> m_expr;
public:

	LengthOperator(std::shared_ptr<Expr> expr) : m_expr{expr}
	{
	}

	virtual ~LengthOperator()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		auto res = m_expr->evaluate(environment);
		switch (res->getType())
		{
		case ValueType::TABLE:
			return std::make_shared<Value>(res->castTable()->getLength());
		case ValueType::STRING:
			return std::make_shared<Value>(res->getString().size());
		default:
			throw std::runtime_error("Can't get Length form this Type");
		}
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_expr));
		return children;
	}

	virtual std::string to_string() override {
		return "LengthOperator(Expression)";
	}
};
