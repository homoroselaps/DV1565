
#include "Table.h"

Table * Table::Create()
{
	m_table = std::make_shared<TableData>();
	m_type = ValueType::TABLE;
	return this;
}

Table * Table::Create(std::shared_ptr<Value> parentScope)
{
	m_table = std::make_shared<TableData>(parentScope);
	m_type = ValueType::TABLE;
	return this;
}

std::shared_ptr<Value> Table::get(std::shared_ptr<Value> key) {
	bool creatIfNotFound = m_table->m_parentScope ? false : true;

	switch (key->getType())
	{
	case ValueType::NIL:
		throw std::runtime_error("key is nil");
	case ValueType::BOOL: {
		if (m_table->m_boolMap.count(key->getBool()))
			return m_table->m_boolMap[key->getBool()];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		else
			break;
	}
	case ValueType::NUMBER:
		if (m_table->m_numMap.count(key->getNumber()))
			return m_table->m_numMap[key->getNumber()];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		else
			break;
	case ValueType::STRING:
		if (m_table->m_stringMap.count(key->getString()))
			return m_table->m_stringMap[key->getString()];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		else
			break;
	case ValueType::FUNCTION:
	case ValueType::TABLE:
		if (m_table->m_refMap.count(key))
			return m_table->m_refMap[key];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		break;
	}
	if (m_table->m_parentScope != nullptr) {
		return m_table->m_parentScope->castTable()->get(key);
	}
	else {
		return std::make_shared<Value>();
	}
}

std::shared_ptr<Value> Table::get(std::string name)
{
	return m_table->m_stringMap[name];
}

std::shared_ptr<Value> Table::create(std::string name, std::shared_ptr<Value> value)
{
	if (name == "")
		throw std::runtime_error("Cant define Variable without name");
	m_table->m_stringMap[name] = value;
	return m_table->m_stringMap[name];
}

std::shared_ptr<Value> Table::getParentScope()
{
	return m_table->m_parentScope;
}

std::shared_ptr<Value> Table::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value) {
	switch (key->getType())
	{
	case ValueType::NIL:
		throw std::runtime_error("key is nil");
	case ValueType::BOOL:
		m_table->m_boolMap[key->getBool()] = value;
		return value;
	case ValueType::NUMBER:
		m_table->m_numMap[key->getNumber()] = value;
		return value;
	case ValueType::STRING:
		m_table->m_stringMap[key->getString()] = value;
		return value;
	case ValueType::FUNCTION:
	case ValueType::TABLE:
		m_table->m_refMap[key] = value;
		return value;
	case ValueType::MULTI:
		throw std::runtime_error("Cant insert MultiValue into Table");
	}
	return nullptr;
}