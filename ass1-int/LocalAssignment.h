#pragma once
#include "Statement.h"
#include "ExprList.h"
#include "NameList.h"
class LocalAssignment :
	public Statement
{
	std::shared_ptr<NameList> m_nameList;
	std::shared_ptr<Expr> m_values;
public:

	LocalAssignment(std::shared_ptr<NameList> nameList, std::shared_ptr<Expr> values) : m_nameList{ nameList }, m_values{ values }
	{
	}

	virtual ~LocalAssignment()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) {
		auto values = m_values->evaluate(environment);

		auto vars = std::vector<std::shared_ptr<Value>>{};
		for (auto name : m_nameList->getStrings()) {
			vars.push_back(environment->castTable()->create(name, std::make_shared<Value>()));
		}
		std::shared_ptr<Value> base = std::make_shared<Value>();
		auto _base = reinterpret_cast<MultiValue*>(base.get())->Create(vars);
		base->assign(values);
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_nameList));
		children.push_back(std::static_pointer_cast<Node>(m_values));
		return children;
	}

	virtual std::string to_string() override {
		return "LocalAssignment(Statement)";
	}
};
