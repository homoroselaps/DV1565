#pragma once
#include "Statement.h"
#include "NameList.h"
class LocalDef : public Statement
{
	std::shared_ptr<NameList> m_nameList;
public:

	LocalDef(std::shared_ptr<NameList> nameList) : m_nameList { nameList}
	{
	}

	virtual ~LocalDef()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) {
		for (auto name : m_nameList->getStrings()) {
			environment->castTable()->create(name, std::make_shared<Value>());
		}
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(m_nameList);
		return children;
	}
	virtual std::string to_string() override {
		return "LocalDef(Statement)";
	}
};

