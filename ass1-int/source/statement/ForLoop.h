#pragma once
#include <string>
#include <memory>
#include "../Statement.h"
#include "../Expr.h"
#include "Chunk.h"
#include "Assignment.h"
#include "WhileLoop.h"
#include "../expression/VarName.h"
#include "../expression/BoolComparator.h"
#include "../expression/NumLiteral.h"

class ForLoop :
	public Statement
{
	std::string m_name;
	std::shared_ptr<Expr> m_start;
	std::shared_ptr<Expr> m_limit;
	std::shared_ptr<Expr> m_step;
	std::shared_ptr<Statement> m_block;
public:

	ForLoop(std::string name, std::shared_ptr<Expr> start, std::shared_ptr<Expr> limit, std::shared_ptr<Expr> step, std::shared_ptr<Statement> block)
		: m_name  { name }
		, m_start { start }
		, m_limit { limit }
		, m_step  { step }
		, m_block { block }
	{ }

	virtual ~ForLoop() { }

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) override {
		double index = m_start->evaluate(environment)->getNumber();
		double step = m_step->evaluate(environment)->getNumber();
		double limit = m_limit->evaluate(environment)->getNumber();
		auto env = std::make_shared<Value>();
		auto _env = reinterpret_cast<Table*>(env.get())->Create(environment);
		std::shared_ptr<Value> var = _env->create(m_name,std::make_shared<Value>());
		while (step > 0 && index <= limit || step <= 0 && index >= limit)
		{
			var->assignNumber(index);
			auto result = m_block->execute(env, control);
			if (control) {
				if (control == ExecControl::BREAK) control = ExecControl::NONE;
				return result;
			}
			index += step;
		}
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_start));
		children.push_back(std::static_pointer_cast<Node>(m_limit));
		children.push_back(std::static_pointer_cast<Node>(m_step));
		children.push_back(std::static_pointer_cast<Node>(m_block));
		return children;
	}

	virtual std::string to_string() override {
		return "ForLoop(Statement) Name:" + m_name;
	}

	virtual std::shared_ptr<Block> convert(std::shared_ptr<Block> current, std::shared_ptr<SymbolTable> env) override {
		auto root = std::make_shared<Chunk>();
		auto ass = std::make_shared<Assignment>(
			std::static_pointer_cast<Expr>(std::make_shared<VarName>(m_name)),
			m_start
			);
		root->addStatement(ass);

		auto ass2 = std::make_shared<Assignment>(
			std::static_pointer_cast<Expr>(std::make_shared<VarName>("forLoopEndVar")),
			m_limit
			);
		root->addStatement(ass2);

		auto whle = std::make_shared<WhileLoop>(
			std::static_pointer_cast<Expr>(std::make_shared<BoolComparator>(
				BoolComparatorType::LEQUAL,
				std::static_pointer_cast<Expr>(std::make_shared<VarName>(m_name)),
				std::static_pointer_cast<Expr>(std::make_shared<VarName>("forLoopEndVar"))
				)),
				m_block
				);
		root->addStatement(whle);
		
		current = root->convert(current, env);
		return current;
	};

};
