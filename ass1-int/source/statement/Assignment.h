#pragma once
#include "../Statement.h"
#include "../expression/ExprList.h"

class Assignment :
	public Statement
{
	std::shared_ptr<Expr> m_base;
	std::shared_ptr<Expr> m_values;
public:

	Assignment(std::shared_ptr<Expr> base, std::shared_ptr<Expr> values) : m_base{base}, m_values{values}
	{
	}

	virtual ~Assignment()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) {
		auto base = m_base->evaluate(environment);
		auto values = m_values->evaluate(environment);
		base->assign(values->copy());
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_base));
		children.push_back(std::static_pointer_cast<Node>(m_values));
		return children;
	}

	virtual std::string to_string() override {
		return "Assignment(Statement)";
	}

	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		current = m_values->convert(current, env);
		current = m_base->convert(current, env);
		auto inst = std::make_shared<ThreeAd>(
			Operator::MOV
			, m_base->result
			, m_values->result
			);
		m_base->result->type = m_values->result->type;
		current->instrs.push_back(inst);
		return current;
	}
};

