#pragma once
#include "Expr.h"
#include "BoolValue.h"
#include "NumValue.h"
#include "StringValue.h"

enum BoolComparatorType {
	EQUAL,
	NEQUAL,
	LESS,
	LEQUAL,
	GREATER,
	GEQUAL,
	AND,
	OR,
};

class BoolComparator: Expr
{
	BoolComparatorType m_type;
	std::shared_ptr<Expr> m_left;
	std::shared_ptr<Expr> m_right;
public:

	BoolComparator(std::shared_ptr<Expr> &left, std::shared_ptr<Expr> &right, BoolComparatorType type)
		: m_type{type}
		, m_left{left}
		, m_right{right}
	{ }

	~BoolComparator()
	{ }

	std::shared_ptr<Value> evaluate() override
	{
		auto leftValue = m_left->evaluate();
		auto rightValue = m_right->evaluate();
		bool result;
		switch (leftValue->getType())
		{
		case Type::BOOL: {
			bool leftresult = leftValue->getBool();
			bool rightresult = rightValue->getBool();
			result = compare(leftresult, rightresult);
			return std::make_shared<BoolValue>(result);
		}
		case Type::NUMBER: {
			double leftresult = leftValue->getNumber();
			double rightresult = rightValue->getNumber();
			result = compare(leftresult, rightresult);
			return std::make_shared<BoolValue>(result);
		}
		case Type::STRING: {
			std::string leftresult = leftValue->getString();
			std::string rightresult = rightValue->getString();
			result = compare(leftresult, rightresult);
			return std::make_shared<BoolValue>(result);
		}
		case Type::FUNCTION:
		case Type::TABLE: {
			result = compare(leftValue, rightValue);
			return std::make_shared<BoolValue>(result);
		}
		case Type::NIL:
			return std::make_shared<BoolValue>(rightValue->getType() == Type::NIL);
		}
	}

	bool compare(bool a, bool b) {
		switch (m_type)
		{
		case EQUAL:
			return a == b;
		case NEQUAL:
			return a != b;
		case AND:
			return a && b;
		case OR:
			return a || b;
		case LESS:
		case LEQUAL:
		case GREATER:
		case GEQUAL:
			throw "Invalid comparison";
			break;
		}
	}

	bool compare(std::string a, std::string b) {
		switch (m_type)
		{
		case EQUAL:
			return a == b;
		case NEQUAL:
			return a != b;
		case LESS:
			return a < b;
		case LEQUAL:
			return a <= b;
		case GREATER:
			return a > b;
		case GEQUAL:
			return a >= b;
		case OR:
		case AND:
			throw "Invalid comparison";
			break;
		}
	}

	bool compare(double a, double b) {
		switch (m_type)
		{
		case EQUAL:
			return a == b;
		case NEQUAL:
			return a != b;
		case LESS:
			return a < b;
		case LEQUAL:
			return a <= b;
		case GREATER:
			return a > b;
		case GEQUAL:
			return a >= b;
		case OR:
		case AND:
			throw "Invalid comparison";
			break;
		}
	}

	bool compare(std::shared_ptr<Value> &a, std::shared_ptr<Value> &b) {
		switch (m_type)
		{
		case EQUAL:
			return a == b;
		case NEQUAL:
			return a != b;
		case LESS:
		case LEQUAL:
		case GREATER:
		case GEQUAL:
		case OR:
		case AND:
			throw "Invalid comparison";
			break;
		}
	}
};

