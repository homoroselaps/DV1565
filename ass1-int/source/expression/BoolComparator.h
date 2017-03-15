#pragma once
#include "../Expr.h"
#include "../Node.h"
#include "../Utils.h"

class BoolComparator: public Expr
{
	BoolComparatorType m_type;
	std::shared_ptr<Expr> m_left;
	std::shared_ptr<Expr> m_right;
public:

	BoolComparator(BoolComparatorType type, std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
		: m_type{type}
		, m_left{left}
		, m_right{right}
	{ }

	virtual ~BoolComparator()
	{ }

	std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override
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
			return std::make_shared<Value>(result);
		}
		case ValueType::NUMBER: {
			double leftresult = leftValue->getNumber();
			double rightresult = rightValue->getNumber();
			result = compare(leftresult, rightresult);
			return std::make_shared<Value>(result);
		}
		case ValueType::STRING: {
			std::string leftresult = leftValue->getString();
			std::string rightresult = rightValue->getString();
			result = compare(leftresult, rightresult);
			return std::make_shared<Value>(result);
		}
		case ValueType::FUNCTION:
		case ValueType::TABLE: {
			result = compare(leftValue, rightValue);
			return std::make_shared<Value>(result);
		}
		case ValueType::NIL:
			return std::make_shared<Value>(rightValue->getType() == ValueType::NIL);
		case ValueType::MULTI:
			throw std::runtime_error("Cant compare MultiValue");
		}
	}

	bool compare(bool a, bool b) {
		switch (m_type)
		{
		case BoolComparatorType::EQUAL:
			return a == b;
		case BoolComparatorType::NEQUAL:
			return a != b;
		case BoolComparatorType::AND:
			return a && b;
		case BoolComparatorType::OR:
			return a || b;
		case BoolComparatorType::LESS:
		case BoolComparatorType::LEQUAL:
		case BoolComparatorType::GREATER:
		case BoolComparatorType::GEQUAL:
			throw std::runtime_error("Invalid comparison");
			break;
		}
	}

	bool compare(std::string a, std::string b) {
		switch (m_type)
		{
		case BoolComparatorType::EQUAL:
			return a == b;
		case BoolComparatorType::NEQUAL:
			return a != b;
		case BoolComparatorType::LESS:
			return a < b;
		case BoolComparatorType::LEQUAL:
			return a <= b;
		case BoolComparatorType::GREATER:
			return a > b;
		case BoolComparatorType::GEQUAL:
			return a >= b;
		case BoolComparatorType::OR:
		case BoolComparatorType::AND:
			throw std::runtime_error("Invalid comparison");
			break;
		}
	}

	bool compare(double a, double b) {
		switch (m_type)
		{
		case BoolComparatorType::EQUAL:
			return a == b;
		case BoolComparatorType::NEQUAL:
			return a != b;
		case BoolComparatorType::LESS:
			return a < b;
		case BoolComparatorType::LEQUAL:
			return a <= b;
		case BoolComparatorType::GREATER:
			return a > b;
		case BoolComparatorType::GEQUAL:
			return a >= b;
		case BoolComparatorType::OR:
		case BoolComparatorType::AND:
			throw std::runtime_error("Invalid comparison");
			break;
		}
	}

	bool compare(std::shared_ptr<Value> a, std::shared_ptr<Value> b) {
		switch (m_type)
		{
		case BoolComparatorType::EQUAL:
			return a == b;
		case BoolComparatorType::NEQUAL:
			return a != b;
		case BoolComparatorType::LESS:
		case BoolComparatorType::LEQUAL:
		case BoolComparatorType::GREATER:
		case BoolComparatorType::GEQUAL:
		case BoolComparatorType::OR:
		case BoolComparatorType::AND:
			throw std::runtime_error("Invalid comparison");
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
		return "Comparator(Statement) Type: " + Utils::to_string(m_type);
	}

	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		current = m_left->convert(current, env);
		current = m_right->convert(current, env);
		result = env->createSymbol(ValueType::BOOL, NameGenerator::get().nextTemp());

		std::shared_ptr<ThreeAd> inst;

		switch (m_type)
		{
		case BoolComparatorType::EQUAL:
			inst = ThreeAdSymbol::create3Ad(Operator::EQUAL, result, m_left->result, m_right->result);
			break;
		case BoolComparatorType::NEQUAL:
			inst = ThreeAdSymbol::create3Ad(Operator::NEQUAL, result, m_left->result, m_right->result);
			break;
		case BoolComparatorType::LESS:
			inst = ThreeAdSymbol::create3Ad(Operator::LESS, result, m_left->result, m_right->result);
			break;
		case BoolComparatorType::LEQUAL:
			inst = ThreeAdSymbol::create3Ad(Operator::LEQUAL, result, m_left->result, m_right->result);
			break;
		case BoolComparatorType::GREATER:
			inst = ThreeAdSymbol::create3Ad(Operator::GREATER, result, m_left->result, m_right->result);
			break;
		case BoolComparatorType::GEQUAL:
			inst = ThreeAdSymbol::create3Ad(Operator::GEQUAL, result, m_left->result, m_right->result);
			break;
		case BoolComparatorType::AND:
			inst = ThreeAdSymbol::create2Ad(Operator::AND, m_left->result, m_right->result);
			break;
		case BoolComparatorType::OR:
			inst = ThreeAdSymbol::create2Ad(Operator::OR, m_left->result, m_right->result);
			break;
		default:
			assert(false);
			break;
		}
		current->instrs.push_back(inst);

		return current;
	}
};
