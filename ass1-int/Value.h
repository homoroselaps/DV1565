#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <cassert>
#include <vector>
#include <sstream>


class Table;
class Function;
class Value;
class MultiValue;

typedef std::function<std::shared_ptr<Value>(std::shared_ptr<Value>, std::vector<std::shared_ptr<Value>>)> Func;

class FunctionData {
public:
	//Function member
	int m_paraCount;
	Func m_func;

	FunctionData(int paraCount, Func func)
		: m_paraCount{ paraCount }
		, m_func{ func } {}
};

class TableData {
public:
	std::shared_ptr<Value> m_parentScope = nullptr;

	std::map<bool, std::shared_ptr<Value>> m_boolMap;
	std::map<double, std::shared_ptr<Value>> m_numMap;
	std::map<std::string, std::shared_ptr<Value>> m_stringMap;
	std::map<std::shared_ptr<Value>, std::shared_ptr<Value>> m_refMap;

	TableData() {
		m_boolMap = std::map<bool, std::shared_ptr<Value>>{};
		m_numMap = std::map<double, std::shared_ptr<Value>>{};
		m_stringMap = std::map<std::string, std::shared_ptr<Value>>{};
		m_refMap = std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>{};
	}

	TableData(std::shared_ptr<Value> parentScope): TableData() {
		m_parentScope = parentScope;
	}
};

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

	//MultiValue member
	std::vector<std::shared_ptr<Value>> m_values;

	//Function member
	std::shared_ptr<FunctionData> m_function;

	//Table member
	std::shared_ptr<TableData> m_table;

	Value(ValueType type) {
		m_type = type;
	}

	std::string pointerToStr(const void * address) {
		std::stringstream ss;
		ss << address;
		return ss.str();
	}

public:

	Value(): Value(ValueType::NIL) {
		assignNil();
	}

	Value(std::string value) : Value(ValueType::STRING){
		assignString(value);
	}

	Value(int value) : Value((double)value) {}
	Value(unsigned int value) : Value((double)value) {}
	Value(long unsigned int value) : Value((double)value) {}
	Value(double value) : Value(ValueType::NUMBER) {
		assignNumber(value);
	}

	Value(bool value) : Value(ValueType::BOOL) {
		assignBool(value);
	}

	void assignNil();

	void assignBool(bool value);

	void assignNumber(double value);

	void assignString(std::string value);

	void assignTable(std::shared_ptr<Value> other);

	void assignFunction(std::shared_ptr<Value> other);

	void assignMultiValue(std::shared_ptr<Value> other);

	virtual ~Value() {};

	virtual bool getBool() {
		switch (m_type)
		{
		case NIL:
			return false;
		case BOOL:
			return m_boolValue;
		case NUMBER:
		case STRING:
		case FUNCTION:
		case TABLE:
			return true;
		case MULTI:
		default:
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
		default:
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
		default:
			throw std::runtime_error("Invalid Conversion from" + std::to_string(m_type) + "to Number");
		}
	}

	std::string to_string();

	void assign(std::shared_ptr<Value> right);

	const ValueType getType() { return m_type; }

	Function * castFunction();
	Table * castTable();
	MultiValue * castMultiValue();
};
