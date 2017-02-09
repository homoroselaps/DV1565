#include "stdafx.h"
#include "Value.h"
#include "BoolValue.h"
#include "NumValue.h"
#include "StringValue.h"
#include "MultiValue.h"

void Value::assign(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	if (left->getType() == ValueType::MULTI) {
		auto l = std::dynamic_pointer_cast<MultiValue>(left);
		if (right->getType() == ValueType::MULTI) {
			auto r = std::dynamic_pointer_cast<MultiValue>(right);
			l->assignMulti(r);
		}
		else
		{
			l->assignSingle(right);
		}
	}
	// left Value is a single Value
	switch (right->m_type)
	{
	case NIL:
		left.reset();
		left = std::make_shared<Value>();
		break;
	case BOOL:
		left.reset();
		left = std::make_shared<BoolValue>(right->getBool());
		break;
	case NUMBER:
		left.reset();
		left = std::make_shared<NumValue>(right->getNumber());
		break;
	case STRING:
		left.reset();
		left = std::make_shared<StringValue>(right->getString());
		break;
	case FUNCTION:
	case TABLE:
		left = right;
		break;
	case MULTI:
		auto r = std::dynamic_pointer_cast<MultiValue>(left);
		left.reset();
		left = r->getFirst();
	}
}