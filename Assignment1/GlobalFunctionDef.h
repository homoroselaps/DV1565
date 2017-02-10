
#include "Statement.h"
#include "NameList.h"
#include "FunctionBody.h"
class GlobalFunctionDef : public Statement
{
	std::shared_ptr<NameList> m_nameList;
	std::shared_ptr<FunctionBody> m_funcBody;

public:

	GlobalFunctionDef(std::shared_ptr<NameList> nameList, std::shared_ptr<FunctionBody> funcBody)
		: m_nameList{nameList}
		, m_funcBody{funcBody}
	{
	}

	virtual ~GlobalFunctionDef()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) {
		//go to parent scope
		auto globalEnv = environment;
		while (globalEnv->castTable()->getParentScope()) {
			globalEnv = globalEnv->castTable()->getParentScope();
		}

		std::shared_ptr<Value> var = globalEnv;
		std::string funcName;
		
		if (m_nameList->getStrings().size())
			throw std::runtime_error("No Function Name specified");
		
		auto list = m_nameList->getStrings();
		if (m_nameList->getSpecial() != "")
			list.push_back(m_nameList->getSpecial());

		for (auto name = list.begin(); name != list.end(); name++) {
			if (name == list.end() - 1) {
				// last name is function name
				funcName = *name;
			}
			else {
				//all others from previous var
				var = var->castTable()->get(*name);
			}
		}

		auto func = m_funcBody->evaluate(environment);
		var->castTable()->create(funcName, func);
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_nameList));
		children.push_back(std::static_pointer_cast<Node>(m_funcBody));
		return children;
	}
	virtual std::string to_string() override {
		return "GlobalFunctionDefinition(Statement)";
	}
};
