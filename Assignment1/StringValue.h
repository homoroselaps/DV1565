#pragma once
#include "Value.h"
class StringValue : public Value
{
public:

	StringValue(std::string value) : Value(value)
	{ }

	virtual ~StringValue()
	{ }

	virtual std::string getString() override {
		return m_stringValue;
	}
};
