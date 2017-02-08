#pragma once
#include "Statement.h"
#include "Expr.h"
#include "Accessor.h"
#include "StringValue.h"
#include "Function.h"
#include "NilLiteral.h"
#include "Call.h"
#include <memory>
#include <string>
class FunctionCall : public Expr
{
	std::shared_ptr<Expr> m_base;
	std::shared_ptr<Expr> m_context;
	std::shared_ptr<Accessor> m_accessor;

public:

	FunctionCall(std::shared_ptr<Expr> base, std::shared_ptr<Expr> context, std::shared_ptr<Accessor> accessor)
		: m_base{base}
		, m_context{context}
		, m_accessor{accessor}
	{
	}

	FunctionCall(std::shared_ptr<Expr> base, std::shared_ptr<Accessor> accessor) : m_base{ base }, m_accessor{ accessor } {
		m_context = std::make_shared<NilLiteral>();
	}

	~FunctionCall()
	{
	}
	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Table> environment) override {
		auto base = m_base->evaluate(environment);
		
		auto context = m_context->evaluate(environment);
		auto function = std::dynamic_pointer_cast<Function>(base);
		if (!function)
			throw "cant call " + base->getString();
		function->setContext(context);
		
		return m_accessor->evaluate(base, environment);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_base));
		children.push_back(std::static_pointer_cast<Node>(m_context));
		children.push_back(std::static_pointer_cast<Node>(m_accessor));
		return children;
	}

	virtual std::string to_string() override {
		return "FunctionCall(Expression)";
	}

};

