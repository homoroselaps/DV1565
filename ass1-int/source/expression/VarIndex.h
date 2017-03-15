#pragma once
#include "../Expr.h"
#include <cassert>
class VarIndex : public Expr
{
	std::shared_ptr<Expr> m_base;
	std::shared_ptr<Expr> m_index;
public:

	VarIndex(std::shared_ptr<Expr> base, std::shared_ptr<Expr> index) : m_base{ base }, m_index{ index }
	{
	}

	virtual ~VarIndex()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) {
		auto base = m_base->evaluate(environment)->castTable();
		auto index = m_index->evaluate(environment);
		return base->get(index);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_base));
		children.push_back(std::static_pointer_cast<Node>(m_index));
		return children;
	}
	virtual std::string to_string() override {
		return "VarIndex(Expression)";
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		current = m_base->convert(current, env);
		if (!std::dynamic_pointer_cast<SymbolTable>(m_base->result))
			throw std::runtime_error("Index base is not a symboltable");
		if (!std::dynamic_pointer_cast<StringLiteral>(m_index))
			throw std::runtime_error("only StringLiterals for Index supported");
		auto member = std::dynamic_pointer_cast<StringLiteral>(m_index)->m_value;
		auto table = std::dynamic_pointer_cast<SymbolTable>(m_base->result);
		result = table->getSymbol(member);
		if (!result)
			result = table->createSymbol(ValueType::NIL, member);
		return current;
	}
};
