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
class FunctionCall : public Statement
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
	virtual std::shared_ptr<Value> execute(std::shared_ptr<Table> environment, bool &isBreak) {
		auto base = m_base->evaluate(environment);
		
		auto context = m_context->evaluate(environment);
		auto function = std::dynamic_pointer_cast<Function>(base);
		if (!function)
			throw "cant call " + base->getString();
		function->setContext(context);
		
		return m_accessor->evaluate(base, environment);
	}

};

