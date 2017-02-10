#pragma once

#include <string>
#include <list>
#include <iostream>
#include <memory>
#include <vector>

class Node {
public:
  std::string m_tag, m_value;
  Node(std::string t, std::string v) : m_tag(t), m_value(v) {}
  Node() { m_tag="uninitialized"; m_value="uninitialized"; } //Bison needs this

  void add(std::shared_ptr<Node> child) {
    // only legacy
  }

  void dump(int depth=0) {
    for(int i=0; i<depth; ++i) {
      std::cout << "  ";
    }
    std::cout << to_string() << std::endl;
  	auto children = getChildren();
    for (auto child : children) {
      child->dump(depth+1);
    }
  }

  static std::string to_graphviz(Node &node) {
	  std::string result = "digraph {";
	  int count = 0;
	  result += node.dump_graphviz(-1, count);
	  result += "}";
	  return result;
  }

  std::string dump_graphviz(int parent_id, int &count) {
	  auto id = count++;
	  auto result = "node"+std::to_string(id) + " [" + to_string() + " ]\n";
	  if (parent_id >= 0) {
		  result += "node" + std::to_string(parent_id) + " -> " + "node" + std::to_string(id) + "\n";
	  }
	  auto children = getChildren();
	  for (auto child : children) {
		  result += child->dump_graphviz(id, count);
	  }
	  return result;
  }

  virtual std::vector<std::shared_ptr<Node>> getChildren() {
    return std::vector<std::shared_ptr<Node>>{};
  };

  virtual std::string to_string() {
	  return "Node Base Class";
  }
};
