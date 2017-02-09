#pragma once

#include "Value.h"
#include <vector>

class MultiValue : public Value
{
	std::vector<std::shared_ptr<Value>> m_values;
public:

	MultiValue(std::vector<std::shared_ptr<Value>> &values);

	MultiValue(std::initializer_list<std::shared_ptr<Value>> values);

	virtual ~MultiValue() { }

	void assignMulti(std::shared_ptr<MultiValue> other);

	void assignSingle(std::shared_ptr<Value> other);
	
	std::vector<std::shared_ptr<Value>> getValues();

	const std::shared_ptr<Value> getFirst();
};
