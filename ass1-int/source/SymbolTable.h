#pragma once
#include <memory>
#include <map>
#include <string>
#include "Symbol.h"

class SymbolTable
{
	SymbolTable(){}
	std::map<std::string, std::shared_ptr<Symbol>> m_symbols;
public:
	static SymbolTable& get()
	{
		static SymbolTable instance; // Guaranteed to be destroyed. Instantiated on first use.
		return instance;
	}
	SymbolTable(SymbolTable const&) = delete;
	void operator=(SymbolTable const&) = delete;

	std::shared_ptr<Symbol> addSymbol(std::shared_ptr<Symbol> sym) {
		m_symbols[sym->name] = sym;
		return sym;
	}

	std::shared_ptr<Symbol> getSymbol(std::string name) {
		if (m_symbols.count(name))
			return m_symbols[name];
		return nullptr;
	}

	std::shared_ptr<Symbol> createSymbol(ValueType type) {
		auto sym = std::make_shared<Symbol>(type);
		addSymbol(sym);
		return sym;
	}

	std::shared_ptr<Symbol> createSymbol(ValueType type, std::string name) {
		auto sym = std::make_shared<Symbol>(type, name);
		addSymbol(sym);
		return sym;
	}
	std::string to_asm_start() {
		std::stringstream long_sym;
		for (auto key : m_symbols) {
			switch (key.second->type)
			{
			case ValueType::NIL:
			case ValueType::NUMBER:
			case ValueType::BOOL:
				long_sym << "long " << key.first << "=0;" << std::endl;
				break;
			default:
				break;
			}
		}
		return long_sym.str();
	}
	std::string to_asm_end() {
		std::stringstream output, output_operands, input_operands;
		bool first = true;
		for (auto key : m_symbols) {
			if (!(key.second->type == ValueType::NUMBER)) continue;
			if (!first) {
				output_operands << ", ";
				input_operands << ", ";
			}
			output_operands << "[" << key.second->name << "] \"+g\" (" << key.second->name << ")" << std::endl;
			input_operands << "[" << key.second->name << "] \"g\" (" << key.second->name << ")" << std::endl;
			first = false;
		}
		return ":" + output_operands.str() + "\n" + ":" + "\n";
	}
};

