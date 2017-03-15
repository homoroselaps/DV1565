#pragma once

#include <vector>
#include <memory>
#include <string>
#include "ThreeAd.h"
#include "SymbolTable.h"
#include "NameGenerator.h"
#include "Symbol.h"

class Block
{
	BoolComparatorType m_cmpType;
public:
	std::vector<std::shared_ptr<ThreeAd>> instrs;
	std::shared_ptr<Block> tExit, fExit;
	std::shared_ptr<Symbol> sym;
	bool visited = false;

	Block() 
	: tExit(nullptr)
	, fExit(nullptr)
	, m_cmpType(BoolComparatorType::EQUAL)
	{
		sym = std::make_shared<Symbol>(ValueType::FUNCTION, NameGenerator::get().nextBlk());
	}

	virtual ~Block() { }

	void setType(BoolComparatorType type) {
		m_cmpType = type;
	}
	
	std::string to_asm() {
		std::stringstream output;
		output << "\"" << sym->name << ":" << "\"" << std::endl;
		for (auto inst : instrs) {
			output << "/*" << inst->to_string() << "*/" << std::endl;
			output << inst->to_asm() << std::endl;
		}
		if (tExit && fExit) {
			output << "\"je " << fExit->sym->to_asm() << ";\"" << std::endl;
			output << "\"jmp " << tExit->sym->to_asm() << ";\"" << std::endl;
		}
		else if (tExit) {
			output << "\"jne " << tExit->sym->to_asm() << ";\"" << std::endl;
		}
		else if (fExit) {
			output << "\"je " << fExit->sym->to_asm() << ";\"" << std::endl;
		}
		return output.str();
	}
};

