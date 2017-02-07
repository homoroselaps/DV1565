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
  std::string tag, value;
  std::list<Node> children;
  Node(std::string t, std::string v) : tag(t), value(v) {}
  Node() { tag="uninitialized"; value="uninitialized"; } //Bison needs this

  void add(Node child) {
    children.push_back(child);
  }

  void dump(int depth=0) {
    for(int i=0; i<depth; ++i) {
      std::cout << "  ";
    }
    std::cout << tag << ":" << value << std::endl;
    for (auto i=children.begin(); i!=children.end(); i++) {
      (*i).dump(depth+1);
    }
  }
};

