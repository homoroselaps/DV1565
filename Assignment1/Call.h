#pragma once
#include "Accessor.h"
#include "Function.h"
#include "Node.hpp"
#include <vector>
#include <memory>

enum ArgumentType
{
	LISTARG,
	TABLEARG
};

class Call : public Accessor
{

	ArgumentType m_type = ArgumentType::LISTARG;
	std::vector<std::shared_ptr<Expr>> m_exprArgs;
	std::shared_ptr<Expr> m_tableArg;
public:


	Call(ArgumentType type) : m_type{ type }
	{
		if (m_type == ArgumentType::LISTARG)
			m_exprArgs = std::vector<std::shared_ptr<Expr>>{};
	}

	virtual ~Call()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> base, std::shared_ptr<Table> environment) override {
		auto f = std::dynamic_pointer_cast<Function>(base);
		auto args = std::vector<std::shared_ptr<Value>>{};
		if (m_type == LISTARG) {
			for (auto expr : m_exprArgs) {
				args.push_back(expr->evaluate(environment));
			}
		}
		else {
			auto table = m_tableArg->evaluate(environment);
			args.push_back(table);
		}
		return f->invoke(args);
	}

	void addArgument(std::shared_ptr<Expr> argument) {
		if (m_type == ArgumentType::LISTARG)
			m_exprArgs.push_back(argument);
		else if (m_type == ArgumentType::TABLEARG) {
			m_tableArg = argument;
		}
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		if (m_type == ArgumentType::LISTARG) {
			for (auto expr : m_exprArgs)
				children.push_back(std::static_pointer_cast<Node>(expr));
		}
		else if (m_type == ArgumentType::TABLEARG) {
			children.push_back(std::static_pointer_cast<Node>(m_tableArg));
		}
		return  children;
	}

	virtual std::string to_string() override {
		return "Call(Accessor)";
	}
};
