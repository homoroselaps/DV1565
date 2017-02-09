#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <cassert>
#include <vector>

class Table;
class Function;
class Value;
class MultiValue;

typedef std::function<std::shared_ptr<Value>(std::shared_ptr<Value>, std::vector<std::shared_ptr<Value>>)> Func;

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
protected:
	//Value member
	ValueType m_type;

	//BoolValue member
	bool m_boolValue;

	//NumValue member
	double m_numValue;


	//StringValue member
	std::string m_stringValue;


	//Table member
	std::shared_ptr<Value> m_parentScope = nullptr;

	std::map<bool, std::shared_ptr<Value>> m_boolMap;
	std::map<double, std::shared_ptr<Value>> m_numMap;
	std::map<std::string, std::shared_ptr<Value>> m_stringMap;
	std::map<std::shared_ptr<Value>, std::shared_ptr<Value>> m_refMap;

	//MultiValue member
	std::vector<std::shared_ptr<Value>> m_values;

	//Function member
	int m_paraCount;
	Func m_function;
	std::shared_ptr<Value> m_context = nullptr;

	Value(ValueType type) {
		m_type = type;
	}

public:

	Value(): Value(ValueType::NIL) {}

	Value(std::string value) : Value(ValueType::STRING){
		m_stringValue = value;
	}

	Value(double value) : Value(ValueType::NUMBER) {
		m_numValue = value;
	}

	Value(bool value) : Value(ValueType::BOOL) {
		m_boolValue = value;
	}

	virtual ~Value() {};

	virtual bool getBool() {
		switch (m_type)
		{
		case NIL:
			return false;
			return m_boolValue;
		case BOOL:
		case NUMBER:
		case STRING:
		case FUNCTION:
		case TABLE:
		case MULTI:
			throw std::runtime_error("Invalid Conversion from" + std::to_string(m_type) + "to Bool");
		}
	}

	virtual double getNumber() {
		switch (m_type)
		{
		case NUMBER:
			return m_numValue;
		case STRING:
			return std::stod(m_stringValue);
		case BOOL:
		case NIL:
		case FUNCTION:
		case TABLE:
		case MULTI:
			throw std::runtime_error("Invalid Conversion from" + std::to_string(m_type) + "to Number");
		}
	}

	virtual std::string getString() {
		switch (m_type)
		{
		case NUMBER:
			return std::to_string(m_numValue);
		case STRING:
			return m_stringValue;
		case BOOL:
		case NIL:
		case FUNCTION:
		case TABLE:
		case MULTI:
			throw std::runtime_error("Invalid Conversion from" + std::to_string(m_type) + "to Number");
		}
	}

	std::string to_string() {
		switch (m_type)
		{
		case NUMBER:
			return std::to_string(m_numValue);
		case STRING:
			return m_stringValue;
		case BOOL:
			return std::to_string(m_boolValue);
		case NIL:
			return "nil";
		case FUNCTION:
			return "Function{" + std::to_string((int)this) + "}";
		case TABLE:
			return "Table{" + std::to_string((int)this) + "}";
		case MULTI:
			return "MultiValue{" + std::to_string((int)this) + "}";
		}
	}

	static void assign(std::shared_ptr<Value> left, std::shared_ptr<Value> right);

	const ValueType getType() { return m_type; }

	Function * castFunction();
	Table * castTable();
	MultiValue * castMultiValue();
};
