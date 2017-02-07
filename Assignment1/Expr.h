#pragma once
#include <memory>
#include "Value.h"
#include "Table.h"
class Expr
{
public:

	Expr()
	{
	}

	~Expr()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) = 0;
};

