#pragma once
#include "Value.h"
class NumValue : public Value
{
public:

	NumValue(double value) :Value(value)
	{ }

	virtual ~NumValue()
	{ }

	virtual double getNumber() override {
		return m_numValue;
	}

	virtual std::string getString() override {
		return std::to_string(m_numValue);
	}
};
