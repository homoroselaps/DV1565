#pragma once
#include "../Statement.h"
#include "../Expr.h"
#include "../Table.h"
#include "../Value.h"
#include "../expression/NilLiteral.h"
#include "../ThreeAdSymbol.h"

class ReturnStat : public Statement
{
	std::shared_ptr<Expr> m_exprList;
public:

	ReturnStat()
	{
		m_exprList = std::make_shared<NilLiteral>();
	}

	ReturnStat(std::shared_ptr<Expr> exprList)
	{
		m_exprList = exprList;
	}

	virtual ~ReturnStat()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		control = ExecControl::RETURN;
		return m_exprList->evaluate(environment);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		if (m_exprList)
			children.push_back(std::static_pointer_cast<Node>(m_exprList));
		return children;
	}
	virtual std::string to_string() override {
		return "Return(Statement)";
	}
	
	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env, std::shared_ptr<Block> retBlock, std::shared_ptr<Block> breakBlock) {
		assert(retBlock);
		m_exprList->convert(current, env);
		current->addInstruction(ThreeAdSymbol::create1Ad(Operator::RET, m_exprList->result));
		current->tExit = retBlock;
		current->fExit = retBlock;
		return nullptr;
	};
};
