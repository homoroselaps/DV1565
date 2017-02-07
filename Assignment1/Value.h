#pragma once
#include <memory>
#include <string>

class Function;
class Table;

enum ValueType
{
	NIL,
	BOOL,
	NUMBER,
	STRING,
	FUNCTION,
	TABLE,
};

class Value
{
	ValueType m_type;
public:
	
	Value(): Value(ValueType::NIL) {}
	Value(ValueType type) : m_type{ type } { };
	~Value() {};

	virtual bool getBool() {
		throw;
	}

	virtual double getNumber() {
		throw;
	}

	virtual std::string getString() {
		return "nil";
	}

	virtual std::shared_ptr<Function> getFunction() {
		throw;
	}
	virtual std::shared_ptr<Table> getTable() {
		throw;
	}
	const ValueType getType() { return m_type; }
};

#include "Table.h"
#include "Function.h"