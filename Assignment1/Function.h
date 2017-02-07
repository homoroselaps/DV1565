#pragma once
#include "Value.h"
#include <vector>
#include <functional>

typedef std::function<std::shared_ptr<Value>(std::vector<std::shared_ptr<Value>>)> Func;

class Function :
	public Value
{
public:
	Func function;
	Function(Func &func)
	{
		this->function = func;
	}

	~Function()
	{
	}
		
	std::shared_ptr<Value> Invoke(std::vector<std::shared_ptr<Value>> & args) {
		return function(args);
	}
};

