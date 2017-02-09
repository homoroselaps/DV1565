#pragma once
#include "Statement.h"
#include "IfStatement.h"
class Selection :
	public Statement
{
	std::vector<std::shared_ptr<IfStatement>> m_ifStats;
	std::shared_ptr<Statement> m_else = nullptr;
public:

	Selection()
	{
		m_ifStats = std::vector<std::shared_ptr<IfStatement>>{};
	}

	virtual ~Selection() { }

	void addElseIfStat(std::shared_ptr<IfStatement> stat) {
		m_ifStats.push_back(stat);
	}

	void setElseStat(std::shared_ptr<Statement> stat) {
		m_else = stat;
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, ExecControl &control) {
		for (auto stat : m_ifStats) {
			if (stat->evaluateCondition(environment)->getBool()) {
				return stat->execute(environment, control);
			}
		}
		if (m_else) {
			return m_else->execute(environment, control);
		}
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		for (auto child : m_ifStats) {
			children.push_back(std::static_pointer_cast<Node>(child));
		}
		return children;
	}

	virtual std::string to_string() override {
		return "If(Statement)";
	}

};

