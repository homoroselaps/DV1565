#pragma once
#include "Statement.h"
#include "Expr.h"

class RepeatLoop :
	public Statement
{
	std::shared_ptr<Expr> m_condition;
	std::shared_ptr<Statement> m_block;
public:

	RepeatLoop(std::shared_ptr<Expr> cond, std::shared_ptr<Statement> block): m_condition{cond}, m_block{block}
	{
	}

	~RepeatLoop()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, ExecControl &control) override {
		std::shared_ptr<Value> result = nullptr;
		auto env = std::make_shared<Table>(environment);
		while (true)
		{
			result = m_block->execute(env, control);
			auto cond = m_condition->evaluate(environment);
			if (!cond->getBool() || control) {
				if (control == ExecControl::BREAK) control = ExecControl::NONE;
				return result;
			}
		}
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_block));
		children.push_back(std::static_pointer_cast<Node>(m_condition));
		return children;
	}
	virtual std::string to_string() override {
		return "RepeatLoop(Statement)";
	}
};

