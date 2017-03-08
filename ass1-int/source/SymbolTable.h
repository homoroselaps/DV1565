#pragma once
#include <memory>
#include <map>
#include <string>
#include "Symbol.h"
#include "MemorySymbol.h"

class SymbolTable: public Symbol
{
	std::map<std::string, std::shared_ptr<Symbol>> m_symbols;
public:
	SymbolTable(std::string name) : Symbol(ValueType::TABLE, name) {
	}
	std::shared_ptr<Symbol> addSymbol(std::shared_ptr<Symbol> sym) {
		m_symbols[sym->name] = sym;
		return sym;
	}

	std::shared_ptr<Symbol> getSymbol(std::string name) {
		if (m_symbols.count(name))
			return m_symbols[name];
		return nullptr;
	}

	std::shared_ptr<MemorySymbol> createSymbol(ValueType type, std::string name) {
		auto s = std::make_shared<MemorySymbol>(type, name);
		addSymbol(s);
		return s;
	}

	virtual int calculate_offset(int nextOffset) override {
		for (auto pair : m_symbols) {
			nextOffset = pair.second->calculate_offset(nextOffset);
		}
		return nextOffset;
	}
};

