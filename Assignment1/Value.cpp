#include "Value.h"
#include "BoolValue.h"
#include "NumValue.h"
#include "StringValue.h"
#include "MultiValue.h"

void Value::assign(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	if (left->getType() == ValueType::MULTI) {
		auto _left = left->castMultiValue();
		if (right->getType() == ValueType::MULTI) {
			_left->assignMulti(right);
		}
		else
		{
			_left->assignSingle(right);
		}
	}
	// left Value is a single Value
	switch (right->m_type)
	{
	case NIL:
	case BOOL:
	case NUMBER:
	case STRING:
		left.swap(std::make_shared<Value>(*right));
		break;
	case FUNCTION:
	case TABLE:
		left = right;
		break;
	case MULTI:
		auto _right = right->castMultiValue();
		left.reset();
		left = _right->getFirst();
	}
}

Function * Value::castFunction()
{
	assert(m_type == ValueType::FUNCTION);
	return reinterpret_cast<Function*>(this);
}

Table * Value::castTable()
{
	assert(m_type == ValueType::TABLE);
	return reinterpret_cast<Table*>(this);
}

MultiValue * Value::castMultiValue()
{
	assert(m_type == ValueType::MULTI);
	return reinterpret_cast<MultiValue*>(this);
}
