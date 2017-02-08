#pragma once
#include "Expr.h"
class NilLiteral : public Expr
{
public:

	NilLiteral()
	{
	}

	virtual ~NilLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		return std::make_shared<Value>();
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "NilLiteral(Expression)";
	}
};
