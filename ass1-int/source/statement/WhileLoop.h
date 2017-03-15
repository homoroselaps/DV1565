#pragma once
#include "../Statement.h"
#include "../Expr.h"
class WhileLoop : public Statement
{
	std::shared_ptr<Expr> m_condition;
	std::shared_ptr<Statement> m_block;

public:

	WhileLoop(std::shared_ptr<Expr> cond, std::shared_ptr<Statement> block) : m_condition{ cond }, m_block{ block }
	{
	}

	~WhileLoop()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		std::shared_ptr<Value> result = nullptr;
		auto env = std::make_shared<Value>();
		auto _env = reinterpret_cast<Table*>(env.get())->Create(environment);
		while (true)
		{
			auto cond = m_condition->evaluate(environment);
			if (!cond->getBool() || control) {
				if (control == ExecControl::BREAK) control = ExecControl::NONE;
				return result;
			}
			result = m_block->execute(env, control);
		}
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_condition));
		children.push_back(std::static_pointer_cast<Node>(m_block));
		return children;
	}
	virtual std::string to_string() override {
		return "WhileLoop(Statement)";
	}

	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		auto startBlock = std::make_shared<Block>();
		auto block = std::make_shared<Block>();
		auto endBlock = std::make_shared<Block>();
		current->tExit = startBlock;
		current->fExit = startBlock;

		startBlock = m_condition->convert(startBlock, env);
		auto testInst = ThreeAdSymbol::create1Ad(Operator::TEST, m_condition->result);
		startBlock->addInstruction(testInst);
		startBlock->tExit = block;
		startBlock->fExit = endBlock;

		block = m_block->convert(block, env);
		block->tExit = startBlock;
		block->fExit = startBlock;
		return endBlock;
	};

};

