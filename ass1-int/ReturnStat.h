#pragma once
#include "Statement.h"
#include "Expr.h"
#include "Table.h"
#include "Value.h"
#include "NilLiteral.h"
class ReturnStat : public Statement
{
	std::shared_ptr<Expr> m_exprList;
public:

	ReturnStat()
	{
		m_exprList = std::make_shared<NilLiteral>();
	}

	ReturnStat(std::shared_ptr<Expr> exprList)
	{
		m_exprList = exprList;
	}

	virtual ~ReturnStat()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		control = ExecControl::RETURN;
		return m_exprList->evaluate(environment);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		if (m_exprList)
			children.push_back(std::static_pointer_cast<Node>(m_exprList));
		return children;
	}
	virtual std::string to_string() override {
		return "Return(Statement)";
	}
};
