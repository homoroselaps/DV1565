#pragma once
#include <memory>
#include "Value.h"
#include "Node.hpp"
class Statement : public Node
{
public:

	Statement()
	{
	}

	~Statement()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) = 0;

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "(Statement)";
	}
};

