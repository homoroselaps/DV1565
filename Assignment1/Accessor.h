#pragma once
#include "Node.hpp"
#include "Table.h"
#include <memory>
class Accessor : public Node
{
public:

	Accessor()
	{
	}

	~Accessor()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> base, std::shared_ptr<Table> environment) = 0;
};

