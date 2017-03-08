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
public:
	std::vector<std::shared_ptr<ThreeAd>> instrs;
	std::shared_ptr<Block> tExit, fExit;
	std::shared_ptr<Symbol> sym;
	bool visited = false;

	Block() 
	: tExit(nullptr)
	, fExit(nullptr)
	{
		sym = std::make_shared<Symbol>(ValueType::FUNCTION, NameGenerator::get().nextBlk());
	}

	virtual ~Block()
	{
	}
	
	std::string to_asm() {
		std::stringstream output;
		output << "\"" << sym->name << ":" << "\"" << std::endl;
		for (auto inst : instrs) {
			output << "/*" << inst->to_string() << "*/" << std::endl;
			output << inst->to_asm() << std::endl;
		}
		return output.str();
	}
};

