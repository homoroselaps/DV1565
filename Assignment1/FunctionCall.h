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
	std::shared_ptr<Expr> m_context;
	std::shared_ptr<Expr> m_args;

public:

	FunctionCall(std::shared_ptr<Expr> base, std::shared_ptr<Expr> context, std::shared_ptr<Expr> args)
		: m_base{base}
		, m_context{context}
		, m_args{args}
	{
	}

	FunctionCall(std::shared_ptr<Expr> base, std::shared_ptr<Expr> args) : m_base{ base }, m_args{ args } {
		m_context = std::make_shared<NilLiteral>();
	}

	virtual ~FunctionCall()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		auto base = m_base->evaluate(environment);
		auto function = std::dynamic_pointer_cast<Function>(base);
		if (!function)
			throw "cant call " + base->getString();
		
		auto context = m_context->evaluate(environment);
		function->setContext(context);

		auto arg = m_args->evaluate(environment);
		std::vector<std::shared_ptr<Value>> arguments;
		if (std::dynamic_pointer_cast<MultiValue>(arg)) {
			arguments = std::dynamic_pointer_cast<MultiValue>(arg)->getValues();
		}
		else {
			arguments = std::vector<std::shared_ptr<Value>>{};
			arguments.push_back(arg);
		}
		return function->invoke(arguments);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_base));
		children.push_back(std::static_pointer_cast<Node>(m_context));
		children.push_back(std::static_pointer_cast<Node>(m_args));
		return children;
	}

	virtual std::string to_string() override {
		return "FunctionCall(Expression)";
	}

};
