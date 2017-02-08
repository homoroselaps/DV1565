#pragma once
#include "Statement.h"
#include "ReturnStat.h"
#include <memory>
#include <vector>
class Chunk : public Statement
{
	std::vector<std::shared_ptr<Statement>> m_stats;
public:

	Chunk()
	{
		m_stats = std::vector<std::shared_ptr<Statement>>{};
	}

	virtual ~Chunk()
	{
	}

	void addStatement(std::shared_ptr<Statement> stat) {
		m_stats.push_back(stat);
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) override {
		auto env = std::make_shared<Table>(environment);
		for (auto stat : m_stats) {
			auto result = stat->execute(env, isBreak);
			if (std::dynamic_pointer_cast<ReturnStat>(stat) || isBreak) {
				return result;
			}
		}
		isBreak = false;
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		for (auto child : m_stats) {
			children.push_back(std::static_pointer_cast<Node>(child));
		}
		return children;
	}
	virtual std::string to_string() override {
		return "Chunk(Statement)";
	}
};
