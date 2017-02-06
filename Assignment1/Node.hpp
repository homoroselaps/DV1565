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

class Value: public Node {
  enum Type {
    INT,
    STR,
    BOOL,
    NIL
  };
  bool bool_value = false;
  int int_value = 0;
  std::string str_value = "";
  Type type = Type::NIL;
public:
  Value(): Node("Value", "nil") { }
  Value(int value): Node("Value", std::to_string(value)) {
     int_value = value;
     type = Type::INT;
  }
  Value(std::string value): Node("Value", value) {
    str_value = value;
    type = Type::STR;
  }
  Value(char * value): Value(std::string(value)) { }
  Value(bool value): Node("Value", std::to_string((int)value)) {
    bool_value = value;
    type = Type::BOOL;
  }
};

class Name: public Node {
  std::string str_value = "";
public:
  Name(): Node("Name", "undefined") { }
  Name(std::string value): Node("Name", value) {
    str_value = value;
  }
  Name(char * value): Name(std::string(value)) {}
};

class Binop: public Node {
    ComparisonType type;
public:
    Binop(): Node("Comparison", "") { }
    Binop(ComparisonType _type): Node("Comparison", std::to_string((int)_type)) {
      type = _type;
    }
};
