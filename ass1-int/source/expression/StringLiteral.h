#pragma once
#include "../Expr.h"
#include "../Value.h"
#include <string>
#include <memory>
class StringLiteral: public Expr
{
	std::string m_value;
public:

	StringLiteral(std::string value): m_value{value}
	{
	}

	virtual ~StringLiteral()
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
		return "StringLiteral(Expression) Value: " + m_value;
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current) override {
		result = SymbolTable::get().createSymbol(ValueType::STRING);
		auto inst = std::make_shared<ThreeAd>(
			Operator::MOV
			, result
			, std::make_shared<ConstSymbol>(m_value)
			);
		current->instrs.push_back(inst);
		return current;
	}
};
