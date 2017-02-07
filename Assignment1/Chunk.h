#pragma once
#include "Statement.h"
#include "ReturnStat.h"
#include <memory>
#include <vector>
class Chunk : public Statement
{
	std::vector<std::shared_ptr<Statement>> stats;
public:

	Chunk()
	{
		stats = std::vector<std::shared_ptr<Statement>>{};
	}

	~Chunk()
	{
	}

	void addStatement(std::shared_ptr<Statement> stat) {
		stats.push_back(stat);
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) override {
		auto env = std::make_shared<Table>(environment);
		for (auto stat : stats) {
			auto result = stat->execute(env, isBreak);
			if (std::dynamic_pointer_cast<ReturnStat>(stat) || isBreak) {
				return result;
			}
		}
		isBreak = false;
		return nullptr;
	}
};

