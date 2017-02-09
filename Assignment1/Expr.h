#pragma once
#include <memory>
#include "Value.h"
#include "Table.h"
#include "Node.hpp"
class Expr : public Node
{
public:

	Expr()
	{
	}

	virtual ~Expr()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) = 0;

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "(Expression)";
	}
};
