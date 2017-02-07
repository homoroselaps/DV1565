#pragma once
#include "Expr.h"
#include "Value.h"
#include "NumValue.h"
#include <string>
#include <memory>
class NumLiteral: public Expr
{
	double m_value;
public:

	NumLiteral(double value): m_value{value}
	{
	}

	~NumLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		return std::make_shared<NumValue>(m_value);
	};

};

