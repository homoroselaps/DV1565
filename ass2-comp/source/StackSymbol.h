#pragma once
#include <memory>
#include "Symbol.h"
class StackSymbol :
	public Symbol
{
	int offset;
public:
	StackSymbol(ValueType type, std::string name) : Symbol(type, name)
	{
		offset = 42;
	}

	virtual std::string to_asm() override {
		return std::to_string(offset) + "(%%rbp)";
	}

	virtual int calculate_offset(int nextOffset, bool global = true) override {
		if (!global) {
			nextOffset += 8;
			offset = -nextOffset; //first symbol at -8(%%rbp)
		}
		return nextOffset;
	}
};

