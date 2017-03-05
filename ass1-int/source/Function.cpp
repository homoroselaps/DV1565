#include "Function.h"

Function * Function::Create(int paraCount, Func func)
{
	m_function = std::make_shared<FunctionData>(paraCount, func);
	m_type = ValueType::FUNCTION;
	return this;
}

std::shared_ptr<Value> Function::invoke(std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> & args) {
	if (m_function->m_paraCount >= 0 && args.size() != m_function->m_paraCount)
		throw std::runtime_error("Parameters do not match:" + std::to_string(m_function->m_paraCount) + " != " + std::to_string(args.size()));
	return m_function->m_func(context, args);
}

std::shared_ptr<Value> Function::copy() {
	auto fun = std::make_shared<Value>();
	auto _fun = reinterpret_cast<Function*>(fun.get());
	_fun->m_function = m_function;
	_fun->m_type = m_type;
	return fun;
}
