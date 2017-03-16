#pragma once
#include "../Statement.h"
#include "../Expr.h"
class IfStatement : public Statement
{
public:
	std::shared_ptr<Expr> m_cond;
	std::shared_ptr<Statement> m_stat;

	IfStatement(std::shared_ptr<Expr> cond, std::shared_ptr<Statement> stat) {
		m_cond = cond;
		m_stat = stat;
	}

	virtual ~IfStatement() { }

	std::shared_ptr<Value> evaluateCondition(std::shared_ptr<Value> environment) {
		return m_cond->evaluate(environment);
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		return m_stat->execute(environment, control);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_cond));
		children.push_back(std::static_pointer_cast<Node>(m_stat));
		return children;
	}

	virtual std::string to_string() override {
		return "If/ElseIf(Statement)";
	}
};
