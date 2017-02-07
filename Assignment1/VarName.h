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

	~VarName()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		return environment->get(std::make_shared<StringValue>(m_name));
	};
};

