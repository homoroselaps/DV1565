#pragma once
#include "Statement.h"
class ForInLoop : public Statement
{
public:

	ForInLoop()
	{
	}

	virtual ~ForInLoop()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) = 0;

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "ForInLoop(Statement)";
	}
};

