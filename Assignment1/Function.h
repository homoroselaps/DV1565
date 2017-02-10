#pragma once
#include <vector>
#include "Value.h"

class Function : public Value
{
public:
	Function * Create(int paraCount, Func func);

	std::shared_ptr<Value> invoke(std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> & args);
};