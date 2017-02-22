#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "StringValue.h"
#include "Utils.h"

class LibraryStd
{
public:

	LibraryStd()
	{
	}

	virtual ~LibraryStd()
	{
	}

	static std::shared_ptr<Value> print() {
		Func f = [](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> args) {
			for (auto arg : args) {
				auto str = arg->to_string();
				Utils::replace(str,"\\n","\n");
				Utils::replace(str,"\\t","\t");
				std::cout << str;
			}
			std::cout << std::endl;
			return std::make_shared<Value>();
		};
		auto fun = std::make_shared<Value>();
		auto _fun = reinterpret_cast<Function*>(fun.get())->Create(-1, f);
		return fun;
	}

	static void load(std::shared_ptr<Value> environment) {
		environment->castTable()->create("print", print());
	}
};
