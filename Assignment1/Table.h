#pragma once

#include "Value.h"
#include <map>
#include <memory>

class Table: Value
{
public:
	std::shared_ptr<Table> m_parentScope = nullptr;

	std::map<bool, std::shared_ptr<Value>> m_boolMap;
	std::map<double, std::shared_ptr<Value>> m_numMap;
	std::map<std::string, std::shared_ptr<Value>> m_stringMap;
	std::map<std::shared_ptr<Value>, std::shared_ptr<Value>> m_refMap;

	Table(): Value(Type::TABLE)
	{
		m_boolMap = std::map<bool, std::shared_ptr<Value>>{};
		m_numMap = std::map<double, std::shared_ptr<Value>>{};
		m_stringMap = std::map<std::string, std::shared_ptr<Value>>{};
		m_refMap = std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>{};
	}
	Table(std::shared_ptr<Table> parentScope): Table()
	{
		m_parentScope = parentScope;
	}

	~Table()
	{
	}

	std::shared_ptr<Value> get(std::shared_ptr<Value> key) {
		switch (key->getType())
		{
		case Type::NIL:
			throw;
		case Type::BOOL: {
			if (m_boolMap.count(key->getBool()))
				return m_boolMap[key->getBool()];
			else
				break;
		}
		case Type::NUMBER:
			if (m_numMap.count(key->getNumber()))
				return m_numMap[key->getNumber()];
			else
				break;
		case Type::STRING:
			if (m_stringMap.count(key->getString()))
				return m_stringMap[key->getString()];
			else
				break;
		case Type::FUNCTION:
		case Type::TABLE:
			if (m_refMap.count(key))
				return m_refMap[key];
			else
				break;
		}
		if (m_parentScope != nullptr) {
			return m_parentScope->get(key);
		}
		else {
			return std::make_shared<Value>();
		}
	}

	void set(std::shared_ptr<Value> key, std::shared_ptr<Value> value) {
		switch (key->getType())
		{
		case Type::NIL:
			throw;
		case Type::BOOL:
			m_boolMap[key->getBool()] = value;
		case Type::NUMBER:
			m_numMap[key->getNumber()] = value;
		case Type::STRING:
			m_stringMap[key->getString()] = value;
		case Type::FUNCTION:
		case Type::TABLE:
			m_refMap[key] = value;
		}
	}
};

