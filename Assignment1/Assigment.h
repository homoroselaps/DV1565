#pragma once
#include "Statement.h"
class Assigment :
	public Statement
{
	std::shared_ptr<ExprList> m_base;
public:

	Assigment()
	{
	}

	~Assigment()
	{
	}
};

