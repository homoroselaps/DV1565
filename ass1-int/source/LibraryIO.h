#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "Utils.h"
#include "SymbolTable.h"
#include "ThreeAdText.h"

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
			case ValueType::NUMBER: {
				throw std::runtime_error("IO write: flag not supported");
			}
			case ValueType::STRING: {
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
		_io->set(std::make_shared<Value>("write"), write());
		_io->set(std::make_shared<Value>("read"), read());
		environment->castTable()->set(std::make_shared<Value>("io"), io);
	}

	static std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) {
		auto io = std::make_shared<SymbolTable>("io");
		auto read = std::make_shared<Symbol>(ValueType::FUNCTION, "read");
		io->addSymbol(read);
		env->addSymbol(io);
		std::string instrs = R"(
".text;"
".globl	read;"
"read:"
"pushq	%%rbp;"
"movq	%%rsp, %%rbp;"
"subq	$40, %%rsp;"
"movq	%%rdi,  -8(%%rbp);"
"movq	%%rsi, -16(%%rbp);"
"movq	%%rdx, -24(%%rbp);"
"movq	%%rcx, -32(%%rbp);"
"leaq	-40(%%rbp), %%rax;"
"movq	%%rax, %%rsi;"
"movl	$_ZSt3cin, %%edi;"
"push	%%r8;"
"call	_ZNSirsERl;"
"pop	%%r8;"
"movq	-40(%%rbp), %%rax;"
"addq	$40, %%rsp;"
"popq	%%rbp;"
"ret;"	
)";
		current->addInstruction(std::make_shared<ThreeAdText>(instrs));

		auto write = std::make_shared<Symbol>(ValueType::FUNCTION, "write");
		io->addSymbol(write);
		env->addSymbol(io);
		std::string instrsWrite = R"(
".data;"
".writeLC0: .string \"%%d\";"
".writeLC1: .string \"%%s\";"
".text;"
".globl	write;"
"write:"
"pushq	%%rbp;"
"movq	%%rsp, %%rbp;"
"subq	$32, %%rsp;"
"movq	%%rdi,  -8(%%rbp);"
"movq	%%rsi, -16(%%rbp);"
"movq	%%rdx, -24(%%rbp);"
"movq	%%rcx, -32(%%rbp);"
"cmpq	$2, -8(%%rbp);"
"jg		.writeSTR;"
"movq	-16(%%rbp), %%rsi;"
"movq	$.writeLC0, %%rdi;"
"movq	$0, %%rax;"
"push	%%r8;"
"call	printf;"
"pop	%%r8;"
"jmp	.writeSND;"
".writeSTR:"
"cmpq	$3, -8(%%rbp);"
"jne	.writeSND;"
"movq	-16(%%rbp), %%rsi;"
"movq	$.writeLC1, %%rdi;"
"movq	$0, %%rax;"
"push	%%r8;"
"call	printf;"
"pop	%%r8;"
".writeSND:"
"cmpq	$2, -24(%%rbp);"
"jg		.writeSTRSND;"
"movq	-32(%%rbp), %%rsi;"
"movq	$.writeLC0, %%rdi;"
"movq	$0, %%rax;"
"push	%%r8;"
"call	printf;"
"pop	%%r8;"
"jmp	.writeEND;"
".writeSTRSND:"
"cmpq	$3, -24(%%rbp);"
"jne	.writeEND;"
"movq	-32(%%rbp), %%rsi;"
"movq	$.writeLC1, %%rdi;"
"movq	$0, %%rax;"
"push	%%r8;"
"call	printf;"
"pop	%%r8;"
".writeEND:"
"movq	$0, %%rax;"
"addq	$32, %%rsp;"
"popq	%%rbp;"
"ret;"		
)";
		current->addInstruction(std::make_shared<ThreeAdText>(instrsWrite));

		return current;
	}
};
