#pragma once

#include <map>
#include <memory>
#include "Value.h"

class Table: public Value
{
public:
	std::shared_ptr<Table> m_parentScope = nullptr;

	std::map<bool, std::shared_ptr<Value>> m_boolMap;
	std::map<double, std::shared_ptr<Value>> m_numMap;
	std::map<std::string, std::shared_ptr<Value>> m_stringMap;
	std::map<std::shared_ptr<Value>, std::shared_ptr<Value>> m_refMap;

	Table();
	Table(std::shared_ptr<Table> parentScope);

	virtual ~Table()
	{
	}

	std::shared_ptr<Value> get(std::shared_ptr<Value> key);
	std::shared_ptr<Value> get(std::string name);
	std::shared_ptr<Value> create(std::string name);
	std::shared_ptr<Value> createGlobal(std::string name);

	void set(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
};