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
	std::vector<std::shared_ptr<ThreeAd>> m_instrs;
	bool m_global = false;
public:
	std::shared_ptr<Block> tExit, fExit;
	std::shared_ptr<Symbol> sym;
	bool visited = false;

	Block() 
	: tExit(nullptr)
	, fExit(nullptr)
	{
		sym = std::make_shared<Symbol>(ValueType::FUNCTION, NameGenerator::get().nextBlk());
	}

	Block(std::string name)
	: tExit(nullptr)
	, fExit(nullptr)
	, m_global(true)
	{
		sym = std::make_shared<Symbol>(ValueType::FUNCTION, name);
	}

	virtual ~Block() { }

	void addInstruction(std::shared_ptr<ThreeAd> inst) {
		m_instrs.push_back(inst);
	}
	
	std::string to_asm() {
		std::stringstream output;
		output << "\".text;\"";
		if (m_global)
			output << "\".globl " << sym->name << ";\"" << std::endl;
		output << "\"" << sym->name << ":" << "\"" << std::endl;
		for (auto inst : m_instrs) {
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

