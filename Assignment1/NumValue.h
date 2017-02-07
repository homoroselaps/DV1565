#pragma once
#include "Value.h"
class NumValue :
	public Value
{
	double m_value;
public:

	NumValue(double value) :Value(Type::NUMBER),
		m_value{ value }
	{ }

	~NumValue()
	{ }

	virtual std::string getString() override {
		return std::to_string(m_value);
	}
};

