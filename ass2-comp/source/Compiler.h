#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include "statement/Chunk.h"
#include "Block.h"
#include "LibraryIO.h"
#include "LibraryStd.h"
#include "StringSectionManager.h"
#include "BlockManager.h"

class Compiler
{
	std::shared_ptr<Chunk> m_root;

public:

	Compiler(std::shared_ptr<Chunk> root): m_root(root)	{ }

	std::tuple<std::string, std::string> compile() {
		auto symTable = std::make_shared<SymbolTable>("mem");
		// Load Libraries
		LibraryStd::load(symTable);
		LibraryIO::load(symTable);
		
		auto end = std::make_shared<Block>();
		end->visited = true;
		auto main = BlockManager::get().createRootBlock("root");
		StackManager::get().enterFrame(main);
		auto root = main;
		// Convert Lua Code
		main = m_root->convert(main, symTable, end, nullptr);
		if (main) {
			main->tExit = end;
			main->fExit = end;
		}
		StackManager::get().leaveFrame(end);

		auto symTableSize = symTable->calculate_offset(0);
		
		// includes
		std::stringstream output;
		output << "#include <cstdio>" << std::endl;
		output << "#include <iostream>" << std::endl;
		output << "#include <string>" << std::endl;
		output << "long " << symTable->name << "[" << symTableSize << "] = {};" << std::endl;
		output << "int main() {" << std::endl;
		// mem array definition
		output << "__asm__(" << std::endl;
		output << StringSectionManager::get().to_asm() << std::endl;
		output << R"(".text;")" << std::endl;
		output << "\".globl " << root->sym->to_asm(Operator::JMP) << ";\"" << std::endl;
		output << "\"jmp "    << root->sym->to_asm(Operator::JMP) << ";\"" << std::endl;

		std::stringstream graphviz;
		graphviz << "digraph R{" << std::endl;

		auto open_queue = std::queue<std::shared_ptr<Block>>{};
		auto open_stack = std::stack<std::shared_ptr<Block>>{};

		for (auto blk : BlockManager::get().getBlocks())
			open_queue.push(blk);
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
			graphviz << blockToGraphviz(blk) << std::endl;
			output << blk->to_asm() << std::endl;
			if (blk->tExit)
				open_stack.push(blk->tExit);
			if (blk->fExit)
				open_queue.push(blk->fExit);
		}
		output << end->to_asm() << std::endl;
		graphviz << blockToGraphviz(end) << std::endl;
		graphviz << "}";
		
		//asm Constraints
		output << ":" << std::endl;
		output << ": [mem] \"r\" (mem)" << std::endl;
		output << ": \"rax\", \"rbx\", \"rcx\", \"rdx\", \"rdi\", \"rsi\", \"cc\"" << std::endl;
		output << ");" << std::endl;
/*		output << R"(
unsigned char *p = (unsigned char *)&mem;
size_t i;
for (i=0; i < sizeof mem; ++i)
    printf("%x", p[i]);
		)";*/
		//output << "printf(\"%c\", (bool)mem[0]+6);";
		output << "}" << std::endl;

		return std::make_tuple<std::string, std::string>(output.str(), graphviz.str());
	}

	std::string blockToGraphviz(std::shared_ptr<Block> blk) {
		std::stringstream output;
		output << blk->sym->name << " [shape=record; label=\"{" << blk->sym->name << std::endl;
		for (auto i : blk->getInstructions()) {
			output << " | " << i->to_string();
		}
		output << "}\" ]" << std::endl;
		if (blk->tExit) {
			output << blk->sym->name << " -> " << blk->tExit->sym->name << std::endl;
		}
		if (blk->fExit && blk->tExit != blk->fExit) {
			output << blk->sym->name << " -> " << blk->fExit->sym->name << std::endl;
		}
		return output.str();
	}

	virtual ~Compiler() { }
};

