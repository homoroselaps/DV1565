#pragma once
#include "Value.h"
#include <vector>
#include <functional>

typedef std::function<std::shared_ptr<Value>(std::shared_ptr<Value>, std::vector<std::shared_ptr<Value>>&)> Func;

class Function : public Value
{
	Func m_function;
	std::shared_ptr<Value> m_context = nullptr;
public:
	
	Function(std::shared_ptr<Value> context, Func func): Value(ValueType::FUNCTION)
	{
		m_context = context;
		m_function = func;
	}

	~Function()
	{
	}
		
	std::shared_ptr<Value> invoke(std::vector<std::shared_ptr<Value>> & args) {
		return m_function(m_context, args);
	}

	void setContext(std::shared_ptr<Value> context) {
		this->m_context = context;
	}
};

