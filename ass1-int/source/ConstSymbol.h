#pragma once
#include "C:\Users\jt-1\Documents\Jan-Tobias\Ausbildung\Studium\2016Schweden\study\DV1565\Projects\ass1-int\source\Symbol.h"
class ConstSymbol :
	public Symbol
{
	double m_numValue;
	std::string m_stringValue;
public:
	ConstSymbol() : Symbol(ValueType::NIL) {
		m_numValue = 0;
	}
	ConstSymbol(std::string val) : Symbol(ValueType::STRING) {
		m_stringValue = val;
	}
	ConstSymbol(double val) : Symbol(ValueType::NUMBER) {
		m_numValue = val;
	}
	virtual std::string to_asm() override {
		//TODO: support string values
		return "$" + std::to_string((int)m_numValue);
	}
};

