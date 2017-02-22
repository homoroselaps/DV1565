#pragma once
#include "Expr.h"
#include "FieldList.h"
class TableConstructor :
	public Expr
{
	std::shared_ptr<FieldList> m_fieldList;
public:

	TableConstructor() {};
	TableConstructor(std::shared_ptr<FieldList> fieldList) : m_fieldList{fieldList}
	{
	}

	virtual ~TableConstructor()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) override {
		auto table = std::make_shared<Value>();
		reinterpret_cast<Table*>(table.get())->Create();
		if (m_fieldList) {
			m_fieldList->execute(environment, table, 1);
		}
		std::cout << to_string() << environment->castTable()->get(std::make_shared<Value>((double)2))->to_string() << std::endl;
		return table;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		if (m_fieldList)
			children.push_back(std::static_pointer_cast<Node>(m_fieldList));
		return children;
	}
	virtual std::string to_string() override {
		return "TableConstructor(Expression)";
	}
};
