#pragma once

#include "Value.h"
#include <vector>

class MultiValue : public Value
{
	
public:

	MultiValue * Create(std::vector<std::shared_ptr<Value>> &values);

	virtual ~MultiValue() { }

	void assignMultiValue(std::shared_ptr<Value> other);

	std::shared_ptr<Value> copy();
	
	std::vector<std::shared_ptr<Value>> getValues();

	const std::shared_ptr<Value> getFirst();
};
