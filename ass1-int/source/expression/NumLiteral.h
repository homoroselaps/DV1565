#pragma once
#include "../Expr.h"
#include "../Value.h"
#include "../Node.h"
#include "../ImidiateSymbol.h"
#include "../MemorySymbol.h"
#include "../ThreeAdSymbol.h"
#include <string>
#include <memory>

class NumLiteral: public Expr
{
	double m_value;
public:

	NumLiteral(double value): m_value{value}
	{
	}

	virtual ~NumLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		return std::make_shared<Value>(m_value);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "NumberLiteral(Expression) Value: " + std::to_string(m_value);
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		result = env->createSymbol(ValueType::NUMBER, NameGenerator::get().nextTemp());
		auto inst = ThreeAdSymbol::create2Ad(
			Operator::MOV
			, result
			, std::make_shared<ImidiateSymbol>((double)m_value)
			);
		current->instrs.push_back(inst);
		return current;
	}
};