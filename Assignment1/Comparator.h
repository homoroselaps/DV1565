#pragma once
#include "Expr.h"
#include "BoolValue.h"
#include "NumValue.h"
#include "StringValue.h"
#include "Node.hpp"

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

class BoolComparator: public Expr
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

	virtual ~BoolComparator()
	{ }

	std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override
	{
		auto leftValue = m_left->evaluate(environment);
		auto rightValue = m_right->evaluate(environment);
		bool result;
		switch (leftValue->getType())
		{
		case ValueType::BOOL: {
			bool leftresult = leftValue->getBool();
			bool rightresult = rightValue->getBool();
			result = compare(leftresult, rightresult);
			return std::make_shared<BoolValue>(result);
		}
		case ValueType::NUMBER: {
			double leftresult = leftValue->getNumber();
			double rightresult = rightValue->getNumber();
			result = compare(leftresult, rightresult);
			return std::make_shared<BoolValue>(result);
		}
		case ValueType::STRING: {
			std::string leftresult = leftValue->getString();
			std::string rightresult = rightValue->getString();
			result = compare(leftresult, rightresult);
			return std::make_shared<BoolValue>(result);
		}
		case ValueType::FUNCTION:
		case ValueType::TABLE: {
			result = compare(leftValue, rightValue);
			return std::make_shared<BoolValue>(result);
		}
		case ValueType::NIL:
			return std::make_shared<BoolValue>(rightValue->getType() == ValueType::NIL);
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

	bool compare(std::shared_ptr<Value> a, std::shared_ptr<Value> b) {
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

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_left));
		children.push_back(std::static_pointer_cast<Node>(m_right));
		return children;
	}
	virtual std::string to_string() override {
		return "Comparator(Statement) Type: " + (int)m_type;
	}
};
