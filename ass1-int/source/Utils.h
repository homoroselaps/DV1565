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

enum class Operator : int {
	NONE,
	ADD,
	SUB,
	MUL,
	DIV,
	MOV,
	CALL,
	TEST,
	EQUAL,
	NEQUAL,
	LESS,
	LEQUAL,
	GREATER,
	GEQUAL,
	AND,
	OR,
};

enum class NumOperatorType : int {
  PLUS,
  MINUS,
  MUL,
  DIV,
  POW,
  MOD,
};

enum class BoolComparatorType : int {
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
			return static_cast<typename std::underlying_type<E>::type>(e);
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
			case Operator::TEST:
				return "TEST";
			case Operator::EQUAL:
				return "EQUAL";
			case Operator::NEQUAL:
				return "NEQUAL";
			case Operator::LESS:
				return "LESS";
			case Operator::LEQUAL:
				return "LEQUAL";
			case Operator::GREATER:
				return "GREATER";
			case Operator::GEQUAL:
				return "GEQUAL";
			case Operator::AND:
				return "AND";
			case Operator::OR:
				return "OR";
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
