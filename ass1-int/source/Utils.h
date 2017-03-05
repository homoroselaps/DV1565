#pragma once

enum NumOperatorType {
  PLUS,
  MINUS,
  MUL,
  DIV,
  POW,
  MOD,
};

enum BoolComparatorType {
  EQUAL,
  NEQUAL,
  LESS,
  LEQUAL,
  GREATER,
  GEQUAL,
  AND,
  OR,
};

class Utils
{
  Utils()
	{
	}

	virtual ~Utils()
	{
	}
public:

	static bool replace(std::string& str, const std::string& from, const std::string& to) {
      size_t start_pos = str.find(from);
      if(start_pos == std::string::npos)
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
};
