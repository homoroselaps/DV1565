#include "Value.h"
#include "MultiValue.h"
#include "Function.h"
#include "Table.h"

void Value::assignMultiValue(std::shared_ptr<Value> other)
{
	auto _other = other->castMultiValue();
	switch (m_type)
	{
	case ValueType::NIL:
	case ValueType::BOOL:
	case ValueType::NUMBER:
	case ValueType::STRING:
	case ValueType::FUNCTION:
	case ValueType::TABLE:
		assign(_other->getFirst());
		break;
	case ValueType::MULTI:
		castMultiValue()->assignMultiValue(other);
		break;
	}
}

void Value::assignNil()
{
	m_type = ValueType::NIL;
}

void Value::assignBool(bool value)
{
	m_type = ValueType::BOOL;
	m_boolValue = value;
}

void Value::assignNumber(double value)
{
	m_type = ValueType::NUMBER;
	m_numValue = value;
}

void Value::assignString(std::string value)
{
	m_type = ValueType::STRING;
	m_stringValue = value;
}

void Value::assignTable(std::shared_ptr<Value> other)
{
	m_type = ValueType::TABLE;
	m_table = other->m_table;
}

void Value::assignFunction(std::shared_ptr<Value> other)
{
	m_type = ValueType::FUNCTION;
	m_function = other->m_function;
}

std::string Value::to_string() {
	switch (m_type)
	{
		case ValueType::NIL: 
			return "nil";
		case ValueType::BOOL: 
			return std::to_string(m_boolValue);
		case ValueType::NUMBER: {
			auto result = std::to_string(m_numValue);
			result.erase(result.find_last_not_of('0') + 2, std::string::npos );
			return result;
		}
		case ValueType::STRING: 
			return m_stringValue;
		case ValueType::FUNCTION: 
			return "Function{" + pointerToStr((void*)m_function.get()) + "}";
		case ValueType::TABLE: 
			return "Table{" + pointerToStr((void*)m_table.get()) + "}";
		case ValueType::MULTI: {
			auto output = "MultiValue{" + pointerToStr((void*)this) + ": ";
			for (auto value : castMultiValue()->getValues()) output += value->to_string() + ", ";
			return  output + "}";
		}
	}
	return "Invalid Object";
}

void Value::assign(std::shared_ptr<Value> right) {
	switch (right->m_type)
	{
	case ValueType::NIL:
		assignNil();
		break;
	case ValueType::BOOL:
		assignBool(right->getBool());
		break;
	case ValueType::NUMBER:
		assignNumber(right->getNumber());
		break;
	case ValueType::STRING:
		assignString(right->getString());
		break;
	case ValueType::FUNCTION:
		assignFunction(right);
		break;
	case ValueType::TABLE:
		assignTable(right);
		break;
	case ValueType::MULTI:
		assignMultiValue(right);
		break;
	}
}

std::shared_ptr<Value> Value::copy() {
	auto val = std::make_shared<Value>();
	switch (m_type)
	{
	case ValueType::NIL:
		val->assignNil();
		break;
	case ValueType::BOOL:
		val->assignBool(m_boolValue);
		break;
	case ValueType::NUMBER:
		val->assignNumber(m_numValue);
		break;
	case ValueType::STRING:
		val->assignString(m_stringValue);
		break;
	case ValueType::FUNCTION:
		return castFunction()->copy();
	case ValueType::TABLE:
		return castTable()->copy();
	case ValueType::MULTI:
		return castMultiValue()->copy();
	}
	return val;
}

Function * Value::castFunction()
{
	assert(m_type == ValueType::FUNCTION);
	return reinterpret_cast<Function*>(this);
}

Table * Value::castTable()
{
	assert(m_type == ValueType::TABLE);
	return reinterpret_cast<Table*>(this);
}

MultiValue * Value::castMultiValue()
{
	assert(m_type == ValueType::MULTI);
	return reinterpret_cast<MultiValue*>(this);
}
