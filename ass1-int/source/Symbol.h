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

	Symbol(ValueType type):Symbol(type,"s" + std::to_string(nCounter++))  {}

	virtual ~Symbol() { }

	std::string to_string() {
		return name +":" + Utils::to_string(type);
	}

	virtual std::string to_asm() {
		return "%[" + name + "]";
	}
};
int Symbol::nCounter = 0;


