#pragma once
#include "Node.hpp"
#include "StringLiteral.h"
#include <vector>
#include <memory>

class NameList : public Node
{
	std::vector<std::string> m_strings;
	std::string m_special;
public:

	NameList() {
		m_strings = std::vector<std::string>{};
		m_special = "";
	}

	virtual ~NameList() { }

	void addString(std::string str) {
		m_strings.push_back(str);
	}

	void setSpecial(std::string str) {
		m_special = str;
	}

	std::string getSpecial() {
		return m_special;
	}

	std::vector<std::string> getStrings() {
		return m_strings;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		for (auto str : m_strings) {
			children.push_back(std::static_pointer_cast<Node>(std::make_shared<StringLiteral>(str)));
		}
		if (m_special != "")
			children.push_back(std::static_pointer_cast<Node>(std::make_shared<StringLiteral>(m_special)));
		return children;
	}

	virtual std::string to_string() override {
		return "NameListList(Helper)";
	}
};
