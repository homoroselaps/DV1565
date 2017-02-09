#pragma once
#include <memory>
#include <string>

class Table;
class Function;

enum ValueType
{
	NIL,
	BOOL,
	NUMBER,
	STRING,
	FUNCTION,
	TABLE,
	MULTI,
};

class Value
{
	ValueType m_type;
public:

	Value(): Value(ValueType::NIL) {}
	Value(ValueType type) : m_type{ type } { };
	virtual ~Value() {};

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

	static void assign(std::shared_ptr<Value> left, std::shared_ptr<Value> right);

	const ValueType getType() { return m_type; }
};
