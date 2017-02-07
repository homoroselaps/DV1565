#pragma once
#include "Expr.h"
class NilLiteral : public Expr
{
public:

	NilLiteral()
	{
	}

	~NilLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		return std::make_shared<Value>();
	}
};

