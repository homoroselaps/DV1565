#pragma once
#include "Value.h"
class StringValue : public Value
{
	std::string m_value;
public:

	StringValue(std::string value) :Value(ValueType::STRING),
		m_value{ value }
	{ }

	virtual ~StringValue()
	{ }

	virtual std::string getString() override {
		return m_value;
	}
};
