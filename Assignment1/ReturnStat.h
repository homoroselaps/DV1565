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

	virtual ~ReturnStat()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		std::shared_ptr<Value> result = nullptr;
		//TODO support Muliple Values
		for (auto expr : m_exprList) {
			result = expr->evaluate(environment);
		}
		control = ExecControl::RETURN;
		return result;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "Return(Statement)";
	}
};
