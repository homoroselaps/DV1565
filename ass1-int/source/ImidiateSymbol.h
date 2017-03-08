#pragma once
#include "Symbol.h"
class ImidiateSymbol :
	public Symbol
{
	double m_numValue;
public:
	ImidiateSymbol() : Symbol(ValueType::NIL,"") {
		m_numValue = 0;
	}
	ImidiateSymbol(double val) : Symbol(ValueType::NUMBER, "") {
		m_numValue = val;
	}
	virtual std::string to_asm() override {
		//TODO: support string values
		return "$" + std::to_string((int)m_numValue);
	}

	virtual int calculate_offset(int nextOffset) override {
		return nextOffset;
	}
};

