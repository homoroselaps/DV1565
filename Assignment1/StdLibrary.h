#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "StringValue.h"

class StdLibrary
{
public:

	StdLibrary()
	{
	}

	virtual ~StdLibrary()
	{
	}

	static std::shared_ptr<Value> print() {
		Func f = [](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> args) {
			for (auto arg : args) {
				std::cout << arg->to_string();
			}
			std::cout << std::endl;
			return std::make_shared<Value>();
		};
		auto fun = std::make_shared<Value>();
		auto _fun = reinterpret_cast<Function*>(fun.get())->Create(std::make_shared<Value>(), -1, f);
		return fun;
	}

	static void load(std::shared_ptr<Value> environment) {
		environment->castTable()->set(std::make_shared<StringValue>("print"), print());
	}
};
