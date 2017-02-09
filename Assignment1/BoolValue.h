#pragma once
#include "Value.h"
class BoolValue : public Value
{
public:

	BoolValue(bool value): Value(value)
	{ }

	virtual ~BoolValue()
	{ }

	virtual std::string getString() override {
		return m_boolValue ? "true" : "false";
	}
};
