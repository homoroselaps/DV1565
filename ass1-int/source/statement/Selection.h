#pragma once
#include "../Statement.h"
#include "IfStatement.h"
#include "../ThreeAdSymbol.h"
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

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) {
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
			assert(children.back());
		}
		if (m_else) {
			children.push_back(std::static_pointer_cast<Node>(m_else));
			assert(children.back());
		}
		return children;
	}

	virtual std::string to_string() override {
		return "Selector(Statement)";
	}

	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		auto endBlk = std::make_shared<Block>();
		for (auto stat : m_ifStats) {
			current = stat->m_cond->convert(current, env);
			auto testInst = ThreeAdSymbol::create1Ad(Operator::TEST, stat->m_cond->result);
			current->instrs.push_back(testInst);
			
			auto tempBlk = std::make_shared<Block>();
			current->tExit = tempBlk;
			tempBlk = stat->m_stat->convert(tempBlk, env);
			tempBlk->tExit = endBlk;
			tempBlk->fExit = endBlk;
			
			auto nextCnd = std::make_shared<Block>();
			current->fExit = nextCnd;
			current = nextCnd;
		}
		if (m_else) {
			current = m_else->convert(current, env);
		}
		current->tExit = endBlk;
		current->fExit = endBlk;

		return endBlk;
	};

};
