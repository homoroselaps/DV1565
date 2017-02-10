#include "Function.h"

Function * Function::Create(int paraCount, Func func)
{
	m_function = std::make_shared<FunctionData>(paraCount, func);
	m_type = ValueType::FUNCTION;
	return this;
}

std::shared_ptr<Value> Function::invoke(std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> & args) {
	if (m_function->m_paraCount > 0 && args.size() != m_function->m_paraCount)
		throw std::runtime_error("Parameters do not match");
	return m_function->m_func(context, args);
}