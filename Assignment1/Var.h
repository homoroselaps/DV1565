#pragma once
#include "Node.hpp"
#include "Expr.h"
#include "Accessor.h"
#include "Accessor.h"
#include <memory>
#include <vector>
class Var : public Expr
{
	std::shared_ptr<Expr> m_base;
	std::vector<std::shared_ptr<Accessor>> m_accessors;
public:

	Var()
	{
	}

	~Var()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {

	}


	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_base));
		for (auto child : m_accessors) {
			children.push_back(std::static_pointer_cast<Node>(child));
		}
		return children;
	}
	virtual std::string to_string() override {
		return "Var(Expression)";
	}
};

