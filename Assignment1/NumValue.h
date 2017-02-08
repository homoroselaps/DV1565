#pragma once
#include "Value.h"
class NumValue : public Value
{
	double m_value;
public:

	NumValue(double value) :Value(ValueType::NUMBER),
		m_value{ value }
	{ }

	virtual ~NumValue()
	{ }

	virtual double getNumber() override {
		return m_value;
	}

	virtual std::string getString() override {
		return std::to_string(m_value);
	}
};
