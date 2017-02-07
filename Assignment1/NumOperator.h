#pragma once
#include "Expr.h"
#include "BoolValue.h"
#include "NumValue.h"
#include "StringValue.h"

enum NumOperatorType {
	PLUS,
	MINUS,
	MUL,
	DIV
};

class NumOperator : public Expr
{
	NumOperatorType m_type;
	std::shared_ptr<Expr> m_left;
	std::shared_ptr<Expr> m_right;
public:

	NumOperator(std::shared_ptr<Expr> &left, std::shared_ptr<Expr> &right, NumOperatorType type)
		: m_type{ type }
		, m_left{ left }
		, m_right{ right }
	{ }

	~NumOperator()
	{ }

	std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override
	{
		auto a = m_left->evaluate(environment)->getNumber();
		auto b = m_right->evaluate(environment)->getNumber();
		double result;
		switch (m_type)
		{
		case PLUS:
			result =  a + b;
		case MINUS:
			result = a - b;
		case DIV:
			result = a / b;
		case MUL:
			result = a * b;
		}
		return std::make_shared<NumValue>(result);
	}
};

