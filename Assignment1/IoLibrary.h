#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "StringValue.h"

class IoLibrary
{
public:

	IoLibrary()
	{
	}

	virtual ~IoLibrary()
	{
	}

	static std::shared_ptr<Value> write() {
		Func f = [](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> args) {
			for (auto arg : args) {
				std::cout << arg->to_string();
			}
			return std::make_shared<Value>();
		};
		auto fun = std::make_shared<Value>();
		auto _fun = reinterpret_cast<Function*>(fun.get())->Create(1, f);
		return fun;
	}

	static void load(std::shared_ptr<Value> environment) {
		auto io = std::make_shared<Value>();
		auto _io = reinterpret_cast<Table*>(io.get())->Create();
		_io->set(std::make_shared<StringValue>("write"), write());
		environment->castTable()->set(std::make_shared<StringValue>("io"), io);
	}
};

