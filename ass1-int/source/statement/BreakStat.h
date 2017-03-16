#pragma once
#include "../Statement.h"
class BreakStat : public Statement
{
public:

	BreakStat()
	{
	}

	virtual ~BreakStat()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		control = ExecControl::BREAK;
		return nullptr;
	}
	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		return std::vector<std::shared_ptr<Node>>{};
	}
	virtual std::string to_string() override {
		return "Statement Base Class";
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env, std::shared_ptr<Block> retBlock, std::shared_ptr<Block> breakBlock) {
		assert(breakBlock);
		current->tExit = breakBlock;
		current->fExit = breakBlock;
		return nullptr;
	};
};
