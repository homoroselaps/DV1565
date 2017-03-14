#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include "statement/Chunk.h"
#include "Block.h"
#include "LibraryStd.h"
#include "StringSectionManager.h"

class Compiler
{
	std::shared_ptr<Chunk> m_root;

public:

	Compiler(std::shared_ptr<Chunk> root): m_root(root)	{ }

	std::string compile() {
		auto symTable = std::make_shared<SymbolTable>("mem");
		auto libs = std::make_shared<Block>();
		// Load Libraries
		libs = LibraryStd::convert(libs, symTable);
		
		auto main = std::make_shared<Block>();
		// Convert Lua Code
		main = m_root->convert(main, symTable);

		auto end = std::make_shared<Block>();
		end->visited = true;
		main->tExit = end;
		main->fExit = end;

		auto symTableSize = symTable->calculate_offset(0);
		
		// includes
		std::stringstream output;
		output << "#include <iostream>" << std::endl;
		output << "#include <string>" << std::endl;
		output << "int main() {" << std::endl;
		// mem array definition
		output << "long " << symTable->name << "[" << symTableSize << "];" << std::endl;
		output << "__asm__(" << std::endl;
		output << StringSectionManager::get().to_asm() << std::endl;
		output << R"(".text;")" << std::endl;
		output << "\".globl " << main->sym->to_asm() << ";\"" << std::endl;
		output << "\"jmp "    << main->sym->to_asm() << ";\"" << std::endl;

		auto open_queue = std::queue<std::shared_ptr<Block>>{};
		auto open_stack = std::stack<std::shared_ptr<Block>>{};

		open_queue.push(libs);
		open_queue.push(main);
		while (true) {
			std::shared_ptr<Block> blk;
			if (open_stack.size()) {
				blk = open_stack.top();
				open_stack.pop();
			}
			else if (open_queue.size()) {
				blk = open_queue.front();
				open_queue.pop();
			}		
			else {
				break;
			}
			if (blk->visited) continue;
			blk->visited = true;
			output << blk->to_asm() << std::endl;
			if (blk->tExit)
				open_stack.push(blk->tExit);
			if (blk->fExit)
				open_queue.push(blk->fExit);
		}
		output << end->to_asm() << std::endl;
		
		//asm Constraints
		output << ":" << std::endl;
		output << ": [mem] \"r\" (mem)" << std::endl;
		output << ": \"rax\", \"rbx\", \"rcx\", \"rdx\", \"cc\"" << std::endl;
		output << ");" << std::endl;
		output << "}" << std::endl;
		return output.str();
	}

	virtual ~Compiler() { }
};

