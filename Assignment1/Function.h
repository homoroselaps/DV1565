#pragma once
#include <vector>
#include <functional>
#include "Value.h"

typedef std::function<std::shared_ptr<Value>(std::shared_ptr<Value>, std::vector<std::shared_ptr<Value>>)> Func;

class Function : public Value
{
	Func m_function;
	std::shared_ptr<Value> m_context = nullptr;
public:

	Function(std::shared_ptr<Value> context, Func func);

	virtual ~Function()
	{
	}

	std::shared_ptr<Value> invoke(std::vector<std::shared_ptr<Value>> & args);

	void setContext(std::shared_ptr<Value> context);
};