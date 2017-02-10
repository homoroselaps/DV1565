#pragma once
#include "Node.hpp"
#include <vector>
#include <memory>

class NodeList : public Node
{
	std::vector<std::shared_ptr<Node>> m_nodes;
public:

	NodeList() {
		m_nodes = std::vector<std::shared_ptr<Node>>{};
	}

	virtual ~NodeList() { }

	void addChild(std::shared_ptr<Node> node) {
		m_nodes.push_back(node);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		return  m_nodes;
	}

	virtual std::string to_string() override {
		return "NodeList(Helper)";
	}
};
