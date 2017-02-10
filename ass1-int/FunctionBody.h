#pragma once
#include "Expr.h"
#include "Chunk.h"
#include "NameList.h"
#include "Function.h"
#include "MultiValue.h"
class FunctionBody : public Expr
{
	std::shared_ptr<Chunk> m_block;
	std::shared_ptr<NameList> m_paraList;
public:

	FunctionBody(std::shared_ptr<NameList> paraList, std::shared_ptr<Chunk> block)
		: m_paraList { paraList }
		, m_block { block }
	{
	}

	virtual ~FunctionBody()
	{
	}

	virtual std::shared_ptr<Value> evaluate(std::shared_ptr<Value> environment) {
		auto paraNames = m_paraList->getStrings();
		auto block = m_block;
		auto env_copy = environment;

		//Define Function Wrapper
		Func f = [paraNames, block, env_copy](std::shared_ptr<Value> context, std::vector<std::shared_ptr<Value>> args) {
			//Create local environment
			auto env = std::make_shared<Value>();
			auto _env = reinterpret_cast<Table*>(env.get())->Create(env_copy);
			_env->create("self", context);
			auto argItr = args.begin();
			bool foundDDDot = false;

			//fill the parameters with the arguments
			for (auto paraItr = paraNames.begin(); paraItr != paraNames.end(); paraItr++) {
				if (*paraItr == "...") {
					foundDDDot = true;
					break;
				}
				_env->create(*paraItr, *argItr);
				argItr++;
			}
			// if foundDDDot copy all remaining parameter into '...' parameter
			if (foundDDDot) {
				std::vector<std::shared_ptr<Value>> values = std::vector<std::shared_ptr<Value>>{};
				for (; argItr != args.end(); argItr++) {
					values.push_back(*argItr);
				}
				auto mv = std::make_shared<Value>();
				auto _mv = reinterpret_cast<MultiValue*>(mv.get())->Create(values);
				_env->create("...", mv);
			}

			ExecControl control = ExecControl::NONE;
			auto result = block->execute(env, control);
			if (control == ExecControl::RETURN)
				return result;
			return std::make_shared<Value>();
		};

		//Count the parameters
		int paraCount = 0;
		for (auto para : paraNames) {
			if (para == "...") {
				paraCount = -1;
				break;
			}
			paraCount++;
		}

		auto fun = std::make_shared<Value>();
		auto _fun = reinterpret_cast<Function*>(fun.get())->Create(paraCount, f);
		return fun;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_block));
		return children;
	}
	virtual std::string to_string() override {
		return "FunctionBody(Expression)";
	}
};
