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
	{
	}

	ThreeAdSymbol(Operator op, std::shared_ptr<Symbol> result, std::shared_ptr<Symbol> sgl): ThreeAdSymbol(op, result, sgl, sgl) { }

	virtual ~ThreeAdSymbol() { }

	virtual std::string to_string() override {
		return result->to_string() + " <- " + left->to_string() + " " + Utils::to_string(op) + " " + right->to_string();
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
			output << "\" mulq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::DIV:
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
				args = std::vector<std::shared_ptr<Symbol>>{ right };
			}	
			
			int index = 0;
			for (auto arg : args) {
				auto typeArg = std::make_shared<ImidiateSymbol>(Utils::to_underlying(arg->type));
				output << "\" movq " << typeArg->to_asm() << ", " << REGS.at(index) << " ;\"" << std::endl;
				index++;
				output << "\" movq " << arg->to_asm() << ", " << REGS.at(index) << " ;\"" << std::endl;
				index++;
			}
			output << "\" call " << left->to_asm() << " ;\"" << std::endl;
			break;
		}
		default:
			break;
		}
		// Write back result
		output << "\" movq %%rax, " << result->to_asm() << " ;\"" << std::endl;
		return output.str();
	}
};

