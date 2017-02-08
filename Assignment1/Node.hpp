#pragma once

#include <string>
#include <list>
#include <iostream>

enum ComparisonType {
  EQUAL,
  NEQUAL,
  LESS,
  LEQUAL,
  GREATER,
  GEQUAL,
  AND,
  OR
};

class Node {
public:
  std::string m_tag, value;
  Node(std::string t, std::string v) : m_tag(t), value(v) {}
  Node() { m_tag="uninitialized"; value="uninitialized"; } //Bison needs this

  void dump(int depth=0) {
    for(int i=0; i<depth; ++i) {
      std::cout << "  ";
    }
	auto children = getChildren();
	std::cout << to_string() << std::endl;
    for (auto child : children) {
      child->dump(depth+1);
    }
  }

  virtual std::vector<std::shared_ptr<Node>> getChildren()=0;
  virtual std::string to_string() {
	  return "Node Base Class";
  }
};

