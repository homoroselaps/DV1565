#pragma once
#include "Expr.h"
#include "Value.h"
#include "NumValue.h"
#include "Node.hpp"
#include <string>
#include <memory>
class NumLiteral: public Expr
{
	double m_value;
public:

	NumLiteral(double value): m_value{value}
	{
	}

	virtual ~NumLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		return std::make_shared<Value>(m_value);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "NumberLiteral(Expression) Value: " + std::to_string(m_value);
	}

};
