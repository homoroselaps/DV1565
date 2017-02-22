#pragma once
#include "Expr.h"
#include "BoolValue.h"
#include "NumValue.h"
#include "StringValue.h"
#include "Node.hpp"
#include <cmath>
#include "Utils.h"

class NumOperator : public Expr
{
	NumOperatorType m_type;
	std::shared_ptr<Expr> m_left;
	std::shared_ptr<Expr> m_right;

	int doubleToInt(double x) {
		return (int)(x+0.5f);
	}
public:

	NumOperator(NumOperatorType type, std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
		: m_type{ type }
		, m_left{ left }
		, m_right{ right }
	{ }

	virtual ~NumOperator()
	{ }

	std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override
	{
		auto a = m_left->evaluate(environment)->getNumber();
		auto b = m_right->evaluate(environment)->getNumber();
		double result;
		switch (m_type)
		{
		case PLUS:
			result =  a + b;
			break;
		case MINUS:
			result = a - b;
			break;
		case DIV:
			result = a / b;
			break;
		case MUL:
			result = a * b;
			break;
		case MOD:
			result = doubleToInt(a) % doubleToInt(b);
			break;
		case POW:
			result = std::pow(a,b);
			break;
		}
		return std::make_shared<NumValue>(result);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_left));
		children.push_back(std::static_pointer_cast<Node>(m_right));
		return children;
	}
	virtual std::string to_string() override {
		return "NumOperator(Expression) Type: " + Utils::to_string(m_type);
	}
};
