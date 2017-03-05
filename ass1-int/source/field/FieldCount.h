#pragma once
#include "../Field.h"
#include "../Expr.h"
class FieldCount : public Field
{
	std::shared_ptr<Expr> m_expr;
public:

	FieldCount(std::shared_ptr<Expr> expr)
		: m_expr{expr}
	{
	}

	virtual ~FieldCount()
	{
	}

	virtual void execute(std::shared_ptr<Value> environment, std::shared_ptr<Value> base, int index) override {
		auto value = base->castTable()->get(std::make_shared<Value>((double)index));
		value->assign(m_expr->evaluate(environment));
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_expr));
		return children;
	}
	virtual std::string to_string() override {
		return "FieldCount(Field)";
	}

};
