
#include "MultiValue.h"
#include "Value.h"
#include <cassert>

MultiValue * MultiValue::Create(std::vector<std::shared_ptr<Value>> &values) {
	m_type = ValueType::MULTI;
	m_values = std::vector<std::shared_ptr<Value>>{};
	for (auto value : values) {
		assert(value->getType() != ValueType::MULTI);
		m_values.push_back(value);
	}
	return this;
}

void MultiValue::assignMultiValue(std::shared_ptr<Value> other) {
	auto _other = other->castMultiValue();
	auto otherChild = _other->m_values.begin();
	for (auto child = m_values.begin(); child != m_values.end(); child++) {
		(*child)->assign(*otherChild);
	}
}

std::vector<std::shared_ptr<Value>> MultiValue::getValues()
{
	return m_values;
}

const std::shared_ptr<Value> MultiValue::getFirst() {
	return m_values.front();
}