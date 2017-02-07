#pragma once
#include <memory>
#include "Value.h"
#include "Node.hpp"
class Statement
{
public:

	Statement()
	{
	}

	~Statement()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) = 0;
};

