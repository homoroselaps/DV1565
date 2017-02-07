#pragma once
#include <memory>
#include <string>
#include "Table.h"

enum Type
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
private:
	Type m_type;
public:
	
	Value(): Value(Type::NIL) {}
	Value(Type type) : m_type{ type } { };
	~Value() {};

	virtual bool getBool() {
		throw;
	}

	virtual double getNumber() {
		throw;
	}

	virtual std::string getString() {
		throw;
	}

	virtual std::shared_ptr<Function> getFunction() {
		throw;
	}
	virtual std::shared_ptr<Table> getTable() {
		throw;
	}
	const Type getType() { return m_type; }
};

