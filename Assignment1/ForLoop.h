#pragma once
#include "Statement.h"
#include "Expr.h"
#include "NumValue.h"
#include <string>
class ForLoop :
	public Statement
{
	std::string m_name;
	std::shared_ptr<Expr> m_start;
	std::shared_ptr<Expr> m_limit;
	std::shared_ptr<Expr> m_step;
	std::shared_ptr<Statement> m_block;
public:

	ForLoop(std::string name, std::shared_ptr<Expr> start, std::shared_ptr<Expr> limit, std::shared_ptr<Expr> step, std::shared_ptr<Statement> block) 
		: m_name  { name }
		, m_start { start }
		, m_limit { limit }
		, m_step  { step }
		, m_block { block }
	{ }

	virtual ~ForLoop() { }

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		double index = m_start->evaluate(environment)->getNumber();
		double step = m_step->evaluate(environment)->getNumber();
		double limit = m_limit->evaluate(environment)->getNumber();
		auto env = std::make_shared<Value>(environment);
		std::shared_ptr<Value> var = env->castTable()->create(m_name,std::make_shared<Value>());
		while (step > 0 && index <= limit || step <= 0 && index >= limit)
		{
			var->assignNumber(index);
			auto result = m_block->execute(env, control);
			if (control) {
				if (control == ExecControl::BREAK) control = ExecControl::NONE;
				return result;
			}
			index += step;
		}
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_start));
		children.push_back(std::static_pointer_cast<Node>(m_limit));
		children.push_back(std::static_pointer_cast<Node>(m_step));
		return children;
	}

	virtual std::string to_string() override {
		return "ForLoop(Statement) Name:" + m_name;
	}
};

