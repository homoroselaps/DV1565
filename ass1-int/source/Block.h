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
	std::vector<std::shared_ptr<ThreeAd>> instrs;
public:
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

	void addInstruction(std::shared_ptr<ThreeAd> inst) {
		instrs.push_back(inst);
	}
	
	std::string to_asm() {
		std::stringstream output;
		output << "\"" << sym->name << ":" << "\"" << std::endl;
		for (auto inst : instrs) {
			assert(inst);
			output << "/*" << inst->to_string() << "*/" << std::endl;
			output << inst->to_asm() << std::endl;
		}
		if (tExit && fExit) {
			output << "\"je " << fExit->sym->to_asm(Operator::JMP) << ";\"" << std::endl;
			output << "\"jmp " << tExit->sym->to_asm(Operator::JMP) << ";\"" << std::endl;
		}
		else if (tExit) {
			output << "\"jne " << tExit->sym->to_asm(Operator::JMP) << ";\"" << std::endl;
		}
		else if (fExit) {
			output << "\"je " << fExit->sym->to_asm(Operator::JMP) << ";\"" << std::endl;
		}
		return output.str();
	}
};

