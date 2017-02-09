
#include "Table.h"

Table * Table::Create()
{
	m_type = ValueType::TABLE;
	m_boolMap = std::map<bool, std::shared_ptr<Value>>{};
	m_numMap = std::map<double, std::shared_ptr<Value>>{};
	m_stringMap = std::map<std::string, std::shared_ptr<Value>>{};
	m_refMap = std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>{};
	return this;
}

Table * Table::Create(std::shared_ptr<Value> parentScope)
{
	m_parentScope = parentScope;
	return Create();
}

std::shared_ptr<Value> Table::get(std::shared_ptr<Value> key) {
	bool creatIfNotFound = m_parentScope ? false : true;

	switch (key->getType())
	{
	case ValueType::NIL:
		throw std::runtime_error("key is nil");
	case ValueType::BOOL: {
		if (m_boolMap.count(key->getBool()))
			return m_boolMap[key->getBool()];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		else
			break;
	}
	case ValueType::NUMBER:
		if (m_numMap.count(key->getNumber()))
			return m_numMap[key->getNumber()];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		else
			break;
	case ValueType::STRING:
		if (m_stringMap.count(key->getString()))
			return m_stringMap[key->getString()];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		else
			break;
	case ValueType::FUNCTION:
	case ValueType::TABLE:
		if (m_refMap.count(key))
			return m_refMap[key];
		else if (creatIfNotFound)
			return set(key, std::make_shared<Value>());
		break;
	}
	if (m_parentScope != nullptr) {
		return m_parentScope->castTable()->get(key);
	}
	else {
		return std::make_shared<Value>();
	}
}

std::shared_ptr<Value> Table::get(std::string name)
{
	return m_stringMap[name];
}

std::shared_ptr<Value> Table::create(std::string name)
{
	m_stringMap[name] = std::make_shared<Value>();
	return m_stringMap[name];
}

std::shared_ptr<Value> Table::createGlobal(std::string name)
{
	if (m_parentScope)
		return m_parentScope->castTable()->createGlobal(name);
	return create(name);
}

std::shared_ptr<Value> Table::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value) {
	switch (key->getType())
	{
	case ValueType::NIL:
		throw std::runtime_error("key is nil");
	case ValueType::BOOL:
		m_boolMap[key->getBool()] = value;
		return value;
	case ValueType::NUMBER:
		m_numMap[key->getNumber()] = value;
		return value;
	case ValueType::STRING:
		m_stringMap[key->getString()] = value;
		return value;
	case ValueType::FUNCTION:
	case ValueType::TABLE:
		m_refMap[key] = value;
		return value;
	}
}