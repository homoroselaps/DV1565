#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include "statement/Chunk.h"
#include "Block.h"

class Compiler
{
	std::shared_ptr<Chunk> m_root;

public:

	Compiler(std::shared_ptr<Chunk> root): m_root(root)	{ }

	std::string compile() {
		auto symTable = std::make_shared<SymbolTable>("mem");
		auto end = std::make_shared<Block>();
		end->visited = true;
		auto main = std::make_shared<Block>();
		main = m_root->convert(main, symTable);
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
		output << "asm(" << std::endl;

		auto open_queue = std::queue<std::shared_ptr<Block>>{};
		auto open_stack = std::stack<std::shared_ptr<Block>>{};

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
			open_stack.push(blk->tExit);
			open_queue.push(blk->fExit);
		}
		output << end->to_asm() << std::endl;
		
		//asm Constraints
		output << ":" << std::endl;
		output << ": [mem] \"r\" (mem)" << std::endl;
		output << ": \"rax\", \"rbx\", \"rdx\", \"cc\"" << std::endl;
		output << ");" << std::endl;
		output << "}" << std::endl;
		return output.str();
	}

	virtual ~Compiler() { }
};

