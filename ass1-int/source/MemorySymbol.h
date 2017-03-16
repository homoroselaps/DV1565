#pragma once
#include <memory>
#include "Symbol.h"
class MemorySymbol :
	public Symbol
{
	int offset;
public:
	MemorySymbol(ValueType type, std::string name) : Symbol(type, name)
	{
	}

	virtual std::string to_asm() override {
		return std::to_string(offset) + "(%[mem])";
	}

	virtual int calculate_offset(int nextOffset, bool global = true) override {
		if (global) {
			offset = nextOffset;
			nextOffset += 8;
		}
		return nextOffset;
	}
};

