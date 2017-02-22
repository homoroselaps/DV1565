#pragma once
#include "Field.h"
#include "Expr.h"
class FieldIndex : public Field
{
	std::shared_ptr<Expr> m_key;
	std::shared_ptr<Expr> m_expr;
public:

	FieldIndex(std::shared_ptr<Expr> key, std::shared_ptr<Expr> expr)
		: m_key{ key }
		, m_expr{ expr }
	{
	}

	virtual ~FieldIndex()
	{
	}

	virtual void execute(std::shared_ptr<Value> environment, std::shared_ptr<Value> base, int index) override {
		auto key = m_key->evaluate(environment);
		auto value = base->castTable()->get(key);
		value->assign(m_expr->evaluate(environment));
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_key));
		children.push_back(std::static_pointer_cast<Node>(m_expr));
		return children;
	}
	virtual std::string to_string() override {
		return "FieldIndex(Field)";
	}

};

