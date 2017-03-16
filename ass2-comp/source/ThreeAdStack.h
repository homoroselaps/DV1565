#pragma once
#include <string>
#include <memory>
#include "ThreeAd.h"
#include "Utils.h"

struct StackFrame {
	std::vector<std::shared_ptr<Symbol>> symbols {};
};



class ThreeAdStack : public ThreeAd
{
	std::shared_ptr<StackFrame> m_frame;
	bool m_onEnter;
public:
	ThreeAdStack(std::shared_ptr<StackFrame> frame, bool onEnter)
	: m_frame(frame)
	, m_onEnter(onEnter)
	{
	}

	virtual ~ThreeAdStack() { }

	virtual std::string to_string() override {
		if (m_onEnter) return "Enter StackFrame";
		return "Leave StackFrame";
	}

	virtual std::string to_asm() override {
		std::stringstream output;
		int size = 0;
		for (auto sym : m_frame->symbols) {
			size = sym->calculate_offset(size, false);
		}
		if (m_onEnter) {
			output << "\"pushq	%%rbp;\"" << std::endl;
			output << "\"movq	%%rsp, %%rbp;\"" << std::endl;
			output << "\"subq	$" + std::to_string(size) + ", %%rsp;\"" << std::endl;
		}
		else {
			output << "\"addq	$" + std::to_string(size) + ", %%rsp;\"" << std::endl;
			output << "\"popq	%%rbp;\"" << std::endl;
		}
		return output.str();
	}
};

