#pragma once
#include <map>
#include <string>
#include <memory>
#include "Block.h"
#include <stack>
#include "ThreeAdStack.h"
#include <assert.h>
#include "Symbol.h"
#include "StackSymbol.h"

class StackManager
{
	StackManager(){}
	std::stack<std::shared_ptr<StackFrame>> m_frames;
public:
	static StackManager& get()
	{
		static StackManager instance; // Guaranteed to be destroyed. Instantiated on first use.
		return instance;
	}

	StackManager(StackManager const&) = delete;
	void operator=(StackManager const&) = delete;

	std::shared_ptr<Block> enterFrame(std::shared_ptr<Block> current) {
		auto frame = std::make_shared<StackFrame>();
		m_frames.push(frame);
		current->addInstruction(std::make_shared<ThreeAdStack>(frame, true));
		return current;
	}

	std::shared_ptr<Block> leaveFrame(std::shared_ptr<Block> current) {
		assert(m_frames.size());
		auto frame = m_frames.top();
		m_frames.pop();
		current->addInstruction(std::make_shared<ThreeAdStack>(frame, false));
		return current;
	}

	void addSymbol(std::shared_ptr<Symbol> sym) {
		assert(m_frames.size());
		auto frame = m_frames.top();
		frame->symbols.push_back(sym);
	}

	std::shared_ptr<StackSymbol> createSymbol(ValueType type, std::string name) {
		assert(m_frames.size());
		auto sym = std::make_shared<StackSymbol>(type, name);
		auto frame = m_frames.top();
		frame->symbols.push_back(sym);
	}
};

