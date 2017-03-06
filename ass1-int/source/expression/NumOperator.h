#pragma once
#include "../Expr.h"
#include "../Node.h"
#include <cmath>
#include "../Utils.h"

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
		case NumOperatorType::PLUS:
			result =  a + b;
			break;
		case NumOperatorType::MINUS:
			result = a - b;
			break;
		case NumOperatorType::DIV:
			result = a / b;
			break;
		case NumOperatorType::MUL:
			result = a * b;
			break;
		case NumOperatorType::MOD:
			result = doubleToInt(a) % doubleToInt(b);
			break;
		case NumOperatorType::POW:
			result = std::pow(a,b);
			break;
		}
		return std::make_shared<Value>(result);
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
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current) override {
		current = m_left->convert(current);
		current = m_right->convert(current);
		if (m_left->result->type != ValueType::NUMBER || m_right->result->type != ValueType::NUMBER) {
			throw std::runtime_error("NumOperator only supports Numbers. got:" + Utils::to_string(m_left->result->type) + ", " + Utils::to_string(m_right->result->type));
		}
		result = SymbolTable::get().createSymbol(ValueType::NUMBER);
		std::shared_ptr<ThreeAd> inst;
		switch (m_type)
		{
		case NumOperatorType::PLUS:
			inst = std::make_shared<ThreeAd>(Operator::ADD, result, m_left->result, m_right->result);
			break;
		case NumOperatorType::MINUS:
			inst = std::make_shared<ThreeAd>(Operator::SUB, result, m_left->result, m_right->result);
			break;
		case NumOperatorType::DIV:
			inst = std::make_shared<ThreeAd>(Operator::DIV, result, m_left->result, m_right->result);
			break;
		case NumOperatorType::MUL:
			inst = std::make_shared<ThreeAd>(Operator::MUL, result, m_left->result, m_right->result);
			break;
		case NumOperatorType::MOD:
			throw std::runtime_error("Not Implemented");
			break;
		case NumOperatorType::POW:
			throw std::runtime_error("Not Implemented");
			break;
		}
		current->instrs.push_back(inst);
		return current;
	}
};
