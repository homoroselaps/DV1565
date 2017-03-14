#pragma once
#include "Symbol.h"
#include "Block.h"
#include <memory>
class FunctionSymbol :
	public Symbol
{
public:
	FunctionSymbol(std::string name) : Symbol(ValueType::FUNCTION, name) { }

	virtual int calculate_offset(int nextOffset) override {
		return nextOffset;
	}
};

