#pragma once

enum class ValueType
{
	NIL,
	BOOL,
	NUMBER,
	STRING,
	FUNCTION,
	TABLE,
	MULTI,
};

enum class Operator {
	NONE,
	ADD,
	SUB,
	MUL,
	DIV,
	MOV,
	CALL,
};

enum class NumOperatorType {
  PLUS,
  MINUS,
  MUL,
  DIV,
  POW,
  MOD,
};

enum class BoolComparatorType {
  EQUAL,
  NEQUAL,
  LESS,
  LEQUAL,
  GREATER,
  GEQUAL,
  AND,
  OR,
};

namespace Utils {

		template <typename E>
		constexpr auto to_underlying(E e) noexcept
		{
			return static_cast<std::underlying_type_t<E>>(e);
		}

		static bool replace(std::string& str, const std::string& from, const std::string& to) {
			size_t start_pos = str.find(from);
			if (start_pos == std::string::npos)
				return false;
			str.replace(start_pos, from.length(), to);
			return true;
		}

		static std::string to_string(BoolComparatorType type) {
			switch (type) {
			case BoolComparatorType::EQUAL:
				return "Equal";
			case BoolComparatorType::NEQUAL:
				return "NotEqual";
			case BoolComparatorType::LESS:
				return "Less";
			case BoolComparatorType::LEQUAL:
				return "LessEqual";
			case BoolComparatorType::GREATER:
				return "Greater";
			case BoolComparatorType::GEQUAL:
				return "GreaterEqual";
			case BoolComparatorType::AND:
				return "And";
			case BoolComparatorType::OR:
				return "Or";
			default:
				return "std::to_string(type)";
			}
		}

		static std::string to_string(NumOperatorType type) {
			switch (type) {
			case NumOperatorType::PLUS:
				return "Plus";
			case NumOperatorType::MINUS:
				return "Minus";
			case NumOperatorType::MUL:
				return "Multiplication";
			case NumOperatorType::DIV:
				return "Divsion";
			case NumOperatorType::POW:
				return "Power";
			case NumOperatorType::MOD:
				return "Modulo";
			default:
				return "std::to_string(type)";
			}
		}

		static std::string to_string(Operator op) {
			switch (op)
			{
			case Operator::ADD:
				return "ADD";
			case Operator::SUB:
				return "SUB";
			case Operator::MUL:
				return "MUL";
			case Operator::DIV:
				return "DIV";
			case Operator::MOV:
				return "MOV";
			case Operator::CALL:
				return "CALL";
			default:
				break;
			};
			return "";
		}

		static std::string to_string(ValueType type) {
			switch (type)
			{
			case ValueType::NIL:
				return "NIL";
			case ValueType::BOOL:
				return "BOOL";
			case ValueType::NUMBER:
				return "NUMBER";
			case ValueType::STRING:
				return "STRING";
			case ValueType::FUNCTION:
				return "FUNCTION";
			case ValueType::TABLE:
				return "TABLE";
			case ValueType::MULTI:
				return "MULTI";
			default:
				return "std::to_string(type)";
			}
		}
}
