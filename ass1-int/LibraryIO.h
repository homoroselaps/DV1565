#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "StringValue.h"
#include "Utils.h"

class LibraryIO
{
	LibraryIO() { }

	virtual ~LibraryIO() { }
public:
	static std::shared_ptr<Value> read() {
		Func f = [](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> args) {
			auto firstArg = args.front();
			switch (firstArg->getType())
			{
			case NUMBER: {
				throw std::runtime_error("IO write: flag not supported");
			}
			case STRING: {
				if (firstArg->getString() == "*number") {
					double number;
					std::cin >> number;
					return std::make_shared<Value>(number);
				}
				else if (firstArg->getString() == "*line") {
					std::string input_line;
					while (std::cin) {
						std::getline(std::cin, input_line);
					};
					return std::make_shared<Value>(input_line);
				}
				else {
					throw std::runtime_error("IO write: flag not supported");
				}
			}
			default:
				throw std::runtime_error("IO write: argument type not supported");
			}
			return std::make_shared<Value>();
		};
		auto fun = std::make_shared<Value>();
		auto _fun = reinterpret_cast<Function*>(fun.get())->Create(1, f);
		return fun;
	}

	static std::shared_ptr<Value> write() {
		Func f = [](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> args) {
			for (auto arg : args) {
				std::string str = arg->to_string();
				Utils::replace(str,"\\n","\n");
				Utils::replace(str,"\\t","\t");
				std::cout << str;
			}
			return std::make_shared<Value>();
		};
		auto fun = std::make_shared<Value>();
		auto _fun = reinterpret_cast<Function*>(fun.get())->Create(-1, f);
		return fun;
	}

	static void load(std::shared_ptr<Value> environment) {
		auto io = std::make_shared<Value>();
		auto _io = reinterpret_cast<Table*>(io.get())->Create();
		_io->set(std::make_shared<StringValue>("write"), write());
		_io->set(std::make_shared<StringValue>("read"), read());
		environment->castTable()->set(std::make_shared<StringValue>("io"), io);
	}
};
