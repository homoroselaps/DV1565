#pragma once
#include <memory>
#include <iostream>
#include "Function.h"
#include "Table.h"
#include "Utils.h"
#include "ThreeAdText.h"

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

	static std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) {
		auto sym = std::make_shared<Symbol>(ValueType::FUNCTION, "print");
		env->addSymbol(sym);
		std::string instrs = R"(
".data;"
".printLC0: .string \"%%d\";"
".printLC1: .string \"%%s\";"
".text;"
".globl	print;"
"print:"
"pushq	%%rbp;"
"movq	%%rsp, %%rbp;"
"subq	$32, %%rsp;"
"movq	%%rdi,  -8(%%rbp);"
"movq	%%rsi, -16(%%rbp);"
"movq	%%rdx, -24(%%rbp);"
"movq	%%rcx, -32(%%rbp);"
"cmpq	$2, -8(%%rbp);"
"jne	.printSTR;"
"movq	-16(%%rbp), %%rsi;"
"movq	$.printLC0, %%rdi;"
"movq	$0, %%rax;"
"push	%%r8;"
"call	printf;"
"pop	%%r8;"
"jmp	.printEND;"
".printSTR:"
"cmpq	$3, -8(%%rbp);"
"jne	.printEND;"
"movq	-16(%%rbp), %%rsi;"
"movq	$.printLC1, %%rdi;"
"movq	$0, %%rax;"
"push	%%r8;"
"call	printf;"
"pop	%%r8;"
".printEND:"
"movq	$0, %%rax;"
"addq	$32, %%rsp;"
"popq	%%rbp;"
"ret;"	
)";
		current->instrs.push_back(std::make_shared<ThreeAdText>(instrs));
		return current;
	}
};
