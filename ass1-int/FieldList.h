#pragma once
#include "Field.h"
class FieldList : public Field
{
	std::vector<std::shared_ptr<Field>> m_fields;
public:

	FieldList()
	{
		m_fields = std::vector<std::shared_ptr<Field>>{};
	}

	virtual ~FieldList()
	{
	}

	void addField(std::shared_ptr<Field> field) {
		m_fields.push_back(field);
	}

	virtual void execute(std::shared_ptr<Value> environment, std::shared_ptr<Value> base, int index = 0) override {
		int index = 1;
		for (auto field : m_fields) {
			field->execute(environment, base, index);
			index++;
		}
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		return children;
	}
	virtual std::string to_string() override {
		return "(Field)";
	}
};

