#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "StringValue.h"

class Library
{
public:

	Library()
	{
	}

	~Library()
	{
	}

	static void load(std::shared_ptr<Table> environment) {
		Func f = [](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> &args) {
			for (auto arg : args) {
				std::cout << arg->getString();
			}
			std::cout << std::endl;
			return std::make_shared<Value>();
		};
		auto print = std::make_shared<Function>(std::make_shared<Value>(), f);
		environment->set(std::make_shared<StringValue>("print"), std::static_pointer_cast<Value>(print));
	}
};

