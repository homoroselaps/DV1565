#pragma once

#include <string>
#include "Utils.h"

class Symbol
{
	static int nCounter;
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

	virtual int calculate_offset(int nextOffset) {
		switch (type)
		{
		case ValueType::NIL:
		case ValueType::BOOL:
		case ValueType::NUMBER: {
			nextOffset += 8;
			break;
		}
		case ValueType::STRING:
		case ValueType::FUNCTION:
		case ValueType::TABLE:
			break;
		}
		return nextOffset;
	}
};


