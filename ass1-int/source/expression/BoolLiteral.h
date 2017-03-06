#pragma once
#include "../Expr.h"
#include "../Value.h"
#include "../Node.h"
#include "../ConstSymbol.h"
#include "../SymbolTable.h"
#include <string>
#include <memory>

class BoolLiteral: public Expr
{
	bool m_value;
public:

	BoolLiteral(bool value): m_value{value}
	{
	}

	virtual ~BoolLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		return std::make_shared<Value>(m_value);
	};
	virtual std::vector<std::shared_ptr<Node>> getChildren()override {
		return std::vector<std::shared_ptr<Node>>{};
	}
	virtual std::string to_string() override {
		return "BoolLiteral(Expression) Value: " + std::string(m_value ? "true" : "false");
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current) override {
		result = SymbolTable::get().createSymbol(ValueType::BOOL);
		auto inst = std::make_shared<ThreeAd>(
			Operator::MOV
			, result
			, std::make_shared<ConstSymbol>((double)m_value)
		);
		current->instrs.push_back(inst);
		return current;
	}
};
