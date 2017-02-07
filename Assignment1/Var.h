#pragma once
#include "Node.hpp"
#include "Expr.h"
#include "Accessor.h"
#include "Accessor.h"
#include <memory>
#include <vector>
class Var : public Expr
{
	std::shared_ptr<Expr> m_base;
	std::vector<std::shared_ptr<Accessor>> m_accessors;
public:

	Var()
	{
	}

	~Var()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {

	}
};

