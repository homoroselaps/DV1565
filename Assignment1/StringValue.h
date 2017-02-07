#pragma once
#include "Value.h"
class StringValue :
	public Value
{
	std::string m_value;
public:

	StringValue(bool value) :Value(Type::BOOL),
		m_value{ value }
	{ }

	~StringValue()
	{ }

	virtual std::string getString() override {
		return m_value;
	}
};

