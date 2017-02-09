#pragma once
#include <vector>
#include "Value.h"

class Function : public Value
{
public:
	Function * Create(std::shared_ptr<Value> context, int paraCount, Func func);

	std::shared_ptr<Value> invoke(std::vector<std::shared_ptr<Value>> & args);

	void setContext(std::shared_ptr<Value> context);
};