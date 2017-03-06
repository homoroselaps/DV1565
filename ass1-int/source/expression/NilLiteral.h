#pragma once
#include "../Expr.h"
#include "../ConstSymbol.h"

class NilLiteral : public Expr
{
public:

	NilLiteral()
	{
	}

	virtual ~NilLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		return std::make_shared<Value>();
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "NilLiteral(Expression)";
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current) override {
		result = SymbolTable::get().createSymbol(ValueType::NIL);
		auto inst = std::make_shared<ThreeAd>(
			Operator::MOV
			, result
			, std::make_shared<ConstSymbol>()
			);
		current->instrs.push_back(inst);
		return current;
	}
};
