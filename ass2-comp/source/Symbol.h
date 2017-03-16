#pragma once

#include <string>
#include "Utils.h"

class Symbol
{
public:
	ValueType type;
	std::string name;

	Symbol(ValueType type, std::string name)
	: type(type)
	, name(name)
	{
	}

	virtual ~Symbol() { }

	virtual std::string to_string() {
		return name +":" + Utils::to_string(type);
	}

	virtual std::string to_asm() {
		return "$" + name;
	}

	virtual std::string to_asm(Operator op) {
		switch (op)
		{
		case Operator::CALL:
		case Operator::JMP:
			return name;
		default:
			return to_asm();
		}
	}

	virtual int calculate_offset(int nextOffset, bool global = true) {
		return nextOffset;
	}
};


