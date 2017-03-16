#pragma once
#include "../Expr.h"
#include "../Value.h"
#include "../Node.h"
#include "../SymbolTable.h"
#include "../MemorySymbol.h"
#include "../ImidiateSymbol.h"
#include "../ThreeAdSymbol.h"
#include "../StackManager.h"
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
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		result = StackManager::get().createSymbol(ValueType::NUMBER, NameGenerator::get().nextTemp());
		auto inst = ThreeAdSymbol::create2Ad(
			Operator::MOV
			, result
			, std::make_shared<ImidiateSymbol>((double)m_value)
			);
		current->addInstruction(inst);
		return current;
	}

};
