#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Symbol.h"
#include "Utils.h"
#include "SymbolTable.h"
#include "ImidiateSymbol.h"
#include "ThreeAd.h"

class ThreeAdSymbol: public ThreeAd
{
public:
	std::shared_ptr<Symbol> result, left, right;
	Operator op;

	ThreeAdSymbol(Operator op, std::shared_ptr<Symbol> result, std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right)
	: op(op)
	, result(result)
	, left(left)
	, right(right)
	{ }

	static std::shared_ptr<ThreeAdSymbol> create3Ad(Operator op, std::shared_ptr<Symbol> result, std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right) {
		return std::make_shared<ThreeAdSymbol>(op, result, left, right);
	}

	static std::shared_ptr<ThreeAdSymbol> create2Ad(Operator op, std::shared_ptr<Symbol> result, std::shared_ptr<Symbol> sgl) {
		return std::make_shared<ThreeAdSymbol>(op, result, sgl, sgl);
	}

	static std::shared_ptr<ThreeAdSymbol> create1Ad(Operator op, std::shared_ptr<Symbol> sgl) {
		return std::make_shared<ThreeAdSymbol>(op, nullptr, sgl, sgl);
	}

	virtual ~ThreeAdSymbol() { }

	virtual std::string to_string() override {
		std::string out = "";
		if (result)
			out = result->to_string() + " <- ";
		if (left)
			out = out + left->to_string() + " " + Utils::to_string(op);
		if (right)
			out = out + " " + right->to_string();
		return out;
	}

	virtual std::string to_asm() override {
		std::stringstream output;
		switch (op)
		{
		case Operator::ADD:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
			output << "\" addq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::SUB:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
			output << "\" subq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::MUL:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
			output << "\" imulq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::DIV:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
			output << "\"cltd;\"" << std::endl;
			output << "\" idivq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::MOD:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
			output << "\"cltd;\"" << std::endl;
			output << "\" idivq %%rbx, %%rax ;\"" << std::endl;
			output << "\" movq %%rdx, %%rax ;\"" << std::endl;
			break;
		case Operator::MOV:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
			break;
		case Operator::CALL: {
			auto REGS = std::vector<std::string>{ "%%rdi","%%rsi", "%%rdx", "%%rcx" };
			
			std::vector<std::shared_ptr<Symbol>> args;
			if (std::dynamic_pointer_cast<SymbolTable>(right)) {
				auto symTable = std::dynamic_pointer_cast<SymbolTable>(right);
				args = symTable->getSymbols();
			}
			else {
				args = std::vector<std::shared_ptr<Symbol>>{ right, std::make_shared<ImidiateSymbol>() };
			}	
			
			int index = 0;
			for (auto arg : args) {
				auto typeArg = std::make_shared<ImidiateSymbol>(Utils::to_underlying(arg->type));
				output << "\" movq " << typeArg->to_asm() << ", " << REGS.at(index) << " ;\"" << std::endl;
				index++;
				output << "\" movq " << arg->to_asm() << ", " << REGS.at(index) << " ;\"" << std::endl;
				index++;
			}
			output << "\" call " << left->to_asm(op) << " ;\"" << std::endl;
			break;
		}
		case Operator::EQUAL:
		case Operator::NEQUAL:
		case Operator::LESS:
		case Operator::LEQUAL:
		case Operator::GREATER:
		case Operator::GEQUAL:
		case Operator::AND:
		case Operator::OR:
			output << boolComparator();
			break;
		case Operator::TEST:
			output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
			output << "\" test %%rax, %%rax ;\"" << std::endl;
			break;
		default:
			break;
		}
		// Write back result if there is one
		if (result)
			output << "\" movq %%rax, " << result->to_asm() << " ;\"" << std::endl;
		return output.str();
	}
	std::string boolComparator() {
		std::stringstream output;
		output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
		output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
		std::string inst = "";
		switch (op)
		{
		case Operator::EQUAL:
		case Operator::NEQUAL:
		case Operator::LESS:
		case Operator::LEQUAL:
		case Operator::GREATER:
		case Operator::GEQUAL:
			inst = "cmpq";
			break;
		case Operator::AND:
			inst = "andq";
			break;
		case Operator::OR:
			inst = "orq";
			break;
		default:
			break;
		}

		output << "\" movq $1, %%rcx;\"" << std::endl;
		output << "\" " << inst << " %%rbx, %%rax;\"" << std::endl;

		std::string jmpTrue = "";
		switch (op)
		{
		case Operator::EQUAL:
			jmpTrue = "je";
			break;
		case Operator::NEQUAL:
			jmpTrue = "jne";
			break;
		case Operator::LESS:
			jmpTrue = "jl";
			break;
		case Operator::LEQUAL:
			jmpTrue = "jle";
			break;
		case Operator::GREATER:
			jmpTrue = "jg";
			break;
		case Operator::GEQUAL:
			jmpTrue = "jge";
			break;
		case Operator::AND:
			jmpTrue = "jne";
			break;
		case Operator::OR:
			jmpTrue = "jne";
			break;
		default:
			break;
		}
		auto trueLabel = NameGenerator::get().nextName(".jmp");
		output << "\" " << jmpTrue << " " << trueLabel << ";\"" << std::endl;
		output << "\" movq $0, %%rcx;\"" << std::endl;
		output << "\" " << trueLabel << ":\"" << std::endl;
		output << "\" movq %%rcx, %%rax;\"" << std::endl;
		return output.str();
	}
};

