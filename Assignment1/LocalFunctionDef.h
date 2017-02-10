
#include "Statement.h"
#include "NameList.h"
#include "FunctionBody.h"
class LocalFunctionDef : public Statement
{
	std::string m_name;
	std::shared_ptr<FunctionBody> m_funcBody;

public:

	LocalFunctionDef(std::string name, std::shared_ptr<FunctionBody> funcBody)
		: m_name{ name }
		, m_funcBody{ funcBody }
	{
	}

	virtual ~LocalFunctionDef()
	{
	}

	virtual std::shared_ptr<Value> execute(std::shared_ptr<Value> environment, ExecControl &control) {
		std::string funcName = m_name;
		auto func = m_funcBody->evaluate(environment);
		environment->castTable()->create(funcName, func);
		return nullptr;
	}

	virtual std::vector<std::shared_ptr<Node>> getChildren() override {
		auto children = std::vector<std::shared_ptr<Node>>{};
		children.push_back(std::static_pointer_cast<Node>(m_funcBody));
		return children;
	}
	virtual std::string to_string() override {
		return "LocalFunctionDefinition(Statement): " + m_name;
	}
};
