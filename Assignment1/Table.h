#pragma once

#include <map>
#include <memory>
#include "Value.h"

class Table: public Value
{
public:
	Table * Create();
	Table * Create(std::shared_ptr<Value> parentScope);

	virtual ~Table()
	{
	}

	std::shared_ptr<Value> get(std::shared_ptr<Value> key);
	std::shared_ptr<Value> get(std::string name);
	std::shared_ptr<Value> create(std::string name);
	std::shared_ptr<Value> createGlobal(std::string name);

	std::shared_ptr<Value> Table::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
};