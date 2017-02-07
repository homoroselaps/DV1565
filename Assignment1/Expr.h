#pragma once
#include <memory>
#include "Value.h"
class Expr
{
public:

	Expr()
	{
	}

	~Expr()
	{
	}

	virtual std::shared_ptr<Value> evaluate();
};

