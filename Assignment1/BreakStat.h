#pragma once
#include "Statement.h"
class BreakStat : public Statement
{
public:

	BreakStat()
	{
	}

	~BreakStat()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) override {
		isBreak = true;
		return nullptr;
	}
	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		return std::vector<std::shared_ptr<Node>>{};
	}
	virtual std::string to_string() override {
		return "Statement Base Class";
	}
};

