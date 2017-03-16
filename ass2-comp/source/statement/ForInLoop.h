#pragma once
#include "../Statement.h"
#include "../Expr.h"
#include "../MultiValue.h"

class ForInLoop : public Statement
{
	std::shared_ptr<Expr> m_expr;
public:

	ForInLoop(std::shared_ptr<Expr> expr): m_expr{expr}
	{
	}

	virtual ~ForInLoop()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		auto values = m_expr->evaluate(environment)->castMultiValue()->getValues();
		auto env = std::make_shared<Value>();
		auto _env = reinterpret_cast<Table*>(env.get())->Create(environment);
		assert(values.size() >= 3);
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "ForInLoop(Statement)";
	}
};

