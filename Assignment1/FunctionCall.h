#pragma once
#include "Statement.h"
#include "Expr.h"
#include "StringValue.h"
#include "Function.h"
#include "NilLiteral.h"
#include "MultiValue.h"
#include <memory>
#include <string>

class FunctionCall : public Expr
{
	std::shared_ptr<Expr> m_base;
	std::string m_special;
	std::shared_ptr<Expr> m_args;

public:

	FunctionCall(std::shared_ptr<Expr> base, std::string special, std::shared_ptr<Expr> args)
		: m_base{base}
		, m_special{special}
		, m_args{args}
	{
	}

	FunctionCall(std::shared_ptr<Expr> base, std::shared_ptr<Expr> args) : m_base{ base }, m_args{ args } {
		m_special = "";
	}

	virtual ~FunctionCall()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		Function* func;
		std::shared_ptr<Value> context;
		auto base = m_base->evaluate(environment);
		if (m_special == "") {
			func = base->castFunction();
			context = std::make_shared<Value>();
		} else {
			context = base;
			func = base->castTable()->get(std::make_shared<Value>(m_special))->castFunction();
		}

		if (!func)
			throw std::runtime_error("cant call " + base->getString());

		auto arg = m_args->evaluate(environment);
		std::vector<std::shared_ptr<Value>> arguments;
		if (arg->getType() == ValueType::MULTI) {
			arguments = arg->castMultiValue()->getValues();
		}
		else {
			arguments = std::vector<std::shared_ptr<Value>>{};
			arguments.push_back(arg);
		}
		return func->invoke(context, arguments);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_base));
		children.push_back(std::static_pointer_cast<Node>(m_args));
		return children;
	}

	virtual std::string to_string() override {
		if (m_special != "")
			return "MemberCall(Expression): " + m_special;
		return "FunctionCall(Expression)";
	}

};
