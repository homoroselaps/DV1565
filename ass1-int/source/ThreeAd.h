#pragma once
#include <string>
#include "source/Symbol.h"
#include "source/Utils.h"

class ThreeAd
{
public:
	std::shared_ptr<Symbol> result, left, right;
	Operator op;

	ThreeAd(Operator op, std::shared_ptr<Symbol> result, std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right)
	: op(op)
	, result(result)
	, left(left)
	, right(right)
	{
	}

	ThreeAd(Operator op, std::shared_ptr<Symbol> result, std::shared_ptr<Symbol> sgl): ThreeAd(op, result, sgl, sgl) { }

	virtual ~ThreeAd()
	{
	}

	std::string to_string() {
		return result->to_string() + " <- " + left->to_string() + " " + Utils::to_string(op) + " " + right->to_string();
	}

	std::string to_asm() {
		std::stringstream output;
		output << "\" movq " << left->to_asm() << ", %%rax ;\"" << std::endl;
		output << "\" movq " << right->to_asm() << ", %%rbx ;\"" << std::endl;
		switch (op)
		{
		case Operator::ADD:
			output << "\" addq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::SUB:
			output << "\" subq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::MUL:
			output << "\" mulq %%rbx, %%rax ;\"" << std::endl;
			break;
		case Operator::DIV:
			break;
		case Operator::MOV:
			//Nothing to do here
			break;
		default:
			break;
		}
		output << "\" movq %%rax, " << result->to_asm() << " ;\"" << std::endl;
		return output.str();
	}
};

