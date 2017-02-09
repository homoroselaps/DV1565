
#include "Function.h"

Function::Function(std::shared_ptr<Value> context, Func func) : Value(ValueType::FUNCTION)
{
	m_context = context;
	m_function = func;
}

std::shared_ptr<Value> Function::invoke(std::vector<std::shared_ptr<Value>> & args) {
	return m_function(m_context, args);
}

void Function::setContext(std::shared_ptr<Value> context) {
	this->m_context = context;
}