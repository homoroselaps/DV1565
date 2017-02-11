#pragma once
#include "Node.hpp"
#include "Value.h"
class Field : public Node
{
public:

	Field()
	{
	}

	virtual ~Field()
	{
	}

	virtual void execute(std::shared_ptr<Value> environment, std::shared_ptr<Value> base, int index) = 0;

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "(Field)";
	}
};

