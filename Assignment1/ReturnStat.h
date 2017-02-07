#pragma once
#include "Statement.h"
#include "Expr.h"
#include "Table.h"
#include "Value.h"
class ReturnStat : public Statement
{
	std::vector<std::shared_ptr<Expr>> m_exprList;
public:

	ReturnStat()
	{
	}

	~ReturnStat()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) override {
		std::shared_ptr<Value> result = nullptr;
		//TODO support Muliple Values
		for (auto expr : m_exprList) {
			result = expr->evaluate(environment);
		}
		return result;
	}
};

