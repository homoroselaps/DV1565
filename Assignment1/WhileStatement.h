#pragma once
#include "Statement.h"
#include "Expr.h"
class WhileLoop : public Statement
{
	std::shared_ptr<Expr> m_condition;
	std::shared_ptr<Statement> m_block;

public:

	WhileLoop()
	{
	}

	~WhileLoop()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		std::shared_ptr<Value> result = nullptr;
		auto env = std::make_shared<Value>();
		auto _env = reinterpret_cast<Table*>(env.get())->Create(environment);
		while (true)
		{
			auto cond = m_condition->evaluate(environment);
			if (!cond->getBool() || control) {
				if (control == ExecControl::BREAK) control = ExecControl::NONE;
				return result;
			}
			result = m_block->execute(env, control);
		}
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_condition));
		children.push_back(std::static_pointer_cast<Node>(m_block));
		return children;
	}
	virtual std::string to_string() override {
		return "WhileLoop(Statement)";
	}

};

