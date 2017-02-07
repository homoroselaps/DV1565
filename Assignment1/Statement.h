#pragma once
#include <memory>
#include "Value.h"
class Statement
{
public:

	Statement()
	{
	}

	~Statement()
	{
	}

	virtual std::shared_ptr<Value> execute();
};

