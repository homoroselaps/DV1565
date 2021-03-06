#pragma once
#include <memory>
#include "Value.h"
#include "Node.h"

enum ExecControl
{
	NONE = 0,
	BREAK,
	RETURN
};

class Statement : public Node
{
public:

	Statement()
	{
	}

	virtual ~Statement()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) = 0;

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "(Statement)";
	}
};
