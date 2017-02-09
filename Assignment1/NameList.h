#pragma once
#include "Node.hpp"
#include <vector>
#include <memory>

class NameList : public Node
{
	std::vector<std::string> m_strings;
public:

	NameList() {
		m_strings = std::vector<std::string>{};
	}

	virtual ~NameList() { }

	void addString(std::string str) {
		m_strings.push_back(str);
	}

	std::vector<std::string> getStrings() {
		return m_strings;

	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		throw "use getStrings";
	}

	virtual std::string to_string() override {
		return "NameListList(Helper)";
	}
};
