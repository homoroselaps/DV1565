#pragma once
#include <memory>
#include "Value.h"
#include "Table.h"
#include "Node.h"
#include "Symbol.h"
#include "Block.h"

class Expr : public Node
{
public:

	Expr() { }

	virtual ~Expr() { }

	std::shared_ptr<Symbol> result;

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) = 0;

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "(Expression)";
	}

	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) {
		return current;
	}
};
