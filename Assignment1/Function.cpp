#include "Function.h"

Function * Function::Create(std::shared_ptr<Value> context, int paraCount, Func func)
{
	m_type = ValueType::FUNCTION;
	m_context = context;
	m_function = func;
	m_paraCount = paraCount;
	return this;
}

std::shared_ptr<Value> Function::invoke(std::vector<std::shared_ptr<Value>> & args) {
	if (m_paraCount > 0 && args.size() != m_paraCount)
		throw std::runtime_error("Parameters do not match");
	return m_function(m_context, args);
}

void Function::setContext(std::shared_ptr<Value> context) {
	this->m_context = context;
}