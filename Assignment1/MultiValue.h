#pragma once

#include "Value.h"
#include <vector>

class MultiValue : public Value
{
	
public:

	MultiValue * Create(std::vector<std::shared_ptr<Value>> &values);

	virtual ~MultiValue() { }

	void assignMulti(std::shared_ptr<Value> other);

	void assignSingle(std::shared_ptr<Value> other);
	
	std::vector<std::shared_ptr<Value>> getValues();

	const std::shared_ptr<Value> getFirst();
};
