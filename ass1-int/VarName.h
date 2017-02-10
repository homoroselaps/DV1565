#pragma once
#include "Expr.h"
#include "Table.h"
#include "Value.h"
#include "StringValue.h"
#include <memory>
#include <string>
class VarName : public Expr
{
	std::string m_name;
public:

	VarName(std::string name): m_name{name}
	{
	}

	virtual ~VarName()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		return environment->castTable()->get(std::make_shared<Value>(m_name));
	};

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "VarName(Expression) Value: " + m_name;
	}
};
