#pragma once
#include "Value.h"
class BoolValue : public Value
{
	bool m_value;
public:

	BoolValue(bool value):Value(ValueType::BOOL),
		m_value{value}
	{ }

	virtual ~BoolValue()
	{ }

	virtual std::string getString() override {
		return m_value ? "true" : "false";
	}
};
