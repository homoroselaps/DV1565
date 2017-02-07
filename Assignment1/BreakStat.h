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
};

