#pragma once
#include "Expr.h"
#include "Value.h"
#include "BoolValue.h"
#include <string>
#include <memory>
class BoolLiteral: public Expr
{
	bool m_value;
public:

	BoolLiteral(bool value): m_value{value}
	{
	}

	~BoolLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		return std::make_shared<BoolValue>(m_value);
	};

};

