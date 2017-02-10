#include "Function.h"

Function * Function::Create(std::shared_ptr<Value> context, int paraCount, Func func)
{
	m_function = std::make_shared<FunctionData>(context, paraCount, func);
	m_type = ValueType::FUNCTION;
	return this;
}

std::shared_ptr<Value> Function::invoke(std::vector<std::shared_ptr<Value>> & args) {
	if (m_function->m_paraCount > 0 && args.size() != m_function->m_paraCount)
		throw std::runtime_error("Parameters do not match");
	return m_function->m_func(m_function->m_context, args);
}

void Function::setContext(std::shared_ptr<Value> context) {
	m_function->m_context = context;
}