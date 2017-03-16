#pragma once
#include <string>
#include <memory>
#include "Symbol.h"
#include "Utils.h"
#include "SymbolTable.h"
#include "ImidiateSymbol.h"

class ThreeAd
{
public:
	virtual std::string to_string() = 0;
	virtual std::string to_asm() = 0;
};

