#pragma once
#include <string>
#include <memory>
#include "ThreeAd.h"
#include "Utils.h"

class ThreeAdText : public ThreeAd
{
	std::string m_inst;
public:
	ThreeAdText(std::string inst)
	: m_inst(inst)
	{
	}

	virtual ~ThreeAdText() { }

	virtual std::string to_string() override {
		return "Precompiled Statements";
	}

	virtual std::string to_asm() override {
		return m_inst;
	}
};

