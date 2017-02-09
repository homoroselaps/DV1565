#include "stdafx.h"
#include "MultiValue.h"
#include <cassert>

MultiValue::MultiValue(std::vector<std::shared_ptr<Value>> &values) : Value(ValueType::MULTI) {
	m_values = std::vector<std::shared_ptr<Value>>{};
	for (auto value : values) {
		assert(value->getType() != ValueType::MULTI);
		m_values.push_back(value);
	}
}

MultiValue::MultiValue(std::initializer_list<std::shared_ptr<Value>> values) : Value(ValueType::MULTI)
{
	m_values = std::vector<std::shared_ptr<Value>>{};
	for (auto value : values) {
		assert(value->getType() != ValueType::MULTI);
		m_values.push_back(value);
	}
}

void MultiValue::assignMulti(std::shared_ptr<MultiValue> other) {
	auto otherChild = other->m_values.begin();
	for (auto child = m_values.begin(); child != m_values.end(); child++) {
		Value::assign(*child, *otherChild);
	}
}

void MultiValue::assignSingle(std::shared_ptr<Value> other) {
	Value::assign(m_values.front(), other);
}

std::vector<std::shared_ptr<Value>> MultiValue::getValues()
{
	return m_values;
}

const std::shared_ptr<Value> MultiValue::getFirst() {
	return m_values.front();
}