#pragma once
#include "../Expr.h"
#include "../Value.h"
#include "../MemorySymbol.h"
#include "../NameGenerator.h"
#include "../StringSectionManager.h"
#include "../ThreeAdSymbol.h"
#include <string>
#include <memory>
class StringLiteral: public Expr
{
public:
	std::string m_value;

	StringLiteral(std::string value): m_value{value}
	{
	}

	virtual ~StringLiteral()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		return std::make_shared<Value>(m_value);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "StringLiteral(Expression) Value: " + m_value;
	}
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		auto name = NameGenerator::get().nextName("str");
		StringSectionManager::get().addString(name, m_value);
		auto sym = std::make_shared<Symbol>(ValueType::STRING, name);
		result = env->addSymbol(sym);
		return current;
	}
};