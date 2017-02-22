// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

/**
 ** \file binary.tab.h
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_BINARY_TAB_H_INCLUDED
# define YY_YY_BINARY_TAB_H_INCLUDED
// //                    "%code requires" blocks.
#line 5 "binary.y" // lalr1.cc:377

	#define YYDEBUG 1
	#include "Assignment.h"
	#include "BoolLiteral.h"
	#include "BreakStat.h"
	#include "Chunk.h"
	#include "BoolComparator.h"
	#include "Expr.h"
	#include "ExprList.h"
	#include "ExprStatement.h"
	#include "FieldCount.h"
	#include "FieldIndex.h"
	#include "FieldList.h"
	#include "FunctionCall.h"
	#include "FunctionBody.h"
	#include "ForLoop.h"
	#include "GlobalFunctionDef.h"
	#include "IfStatement.h"
	#include "NilLiteral.h"
	#include "Node.hpp"
	#include "NodeList.h"
	#include "NameList.h"
	#include "NumLiteral.h"
	#include "NumOperator.h"
	#include "NotOperator.h"
	#include "LengthOperator.h"
	#include "LocalAssignment.h"
	#include "LocalDef.h"
	#include "LocalFunctionDef.h"
	#include "ReturnStat.h"
	#include "RepeatLoop.h"
	#include "Selection.h"
	#include "Statement.h"
	#include "StringLiteral.h"
	#include "StringOperator.h"
	#include "TableConstructor.h"
	#include "VarName.h"
	#include "VarIndex.h"
	#include "WhileLoop.h"

	#include <string>
	#include <memory>

#line 88 "binary.tab.h" // lalr1.cc:377


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"


#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif


namespace yy {
#line 165 "binary.tab.h" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {}

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;
  };


  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // OR
      // AND
      // COMP
      char dummy1[sizeof(BoolComparatorType)];

      // NUMBER
      char dummy2[sizeof(double)];

      // chunk
      // __stat
      // _semi
      // laststat
      // block
      // stat
      // __elseif
      // varlist
      // funcname
      // __dotname
      // var
      // namelist
      // explist
      // exp
      // prefixexp
      // functioncall
      // args
      // function
      // funcbody
      // parlist
      // tableconstructor
      // fieldlist
      // __fieldsepfield
      // field
      // fieldsep
      // binopexp
      char dummy3[sizeof(std::shared_ptr<Node>)];

      // ANY
      // STRING
      // NAME
      char dummy4[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m);
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        EOOF = 0,
        IF = 258,
        THEN = 259,
        ELSEIF = 260,
        ELSE = 261,
        END = 262,
        FOR = 263,
        DO = 264,
        REPEAT = 265,
        UNTIL = 266,
        BREAK = 267,
        IN = 268,
        WHILE = 269,
        LOCAL = 270,
        ANY = 271,
        LENGTH = 272,
        NOT = 273,
        RETURN = 274,
        OR = 275,
        AND = 276,
        COMP = 277,
        CONCAT = 278,
        NIL = 279,
        FALSE = 280,
        TRUE = 281,
        NUMBER = 282,
        STRING = 283,
        NAME = 284,
        NL = 285,
        BLK = 286,
        FUNCTION = 287,
        DDDOT = 288
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t);

  basic_symbol (typename Base::kind_type t, const BoolComparatorType v);

  basic_symbol (typename Base::kind_type t, const double v);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Node> v);

  basic_symbol (typename Base::kind_type t, const std::string v);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_EOOF ();

    static inline
    symbol_type
    make_IF ();

    static inline
    symbol_type
    make_THEN ();

    static inline
    symbol_type
    make_ELSEIF ();

    static inline
    symbol_type
    make_ELSE ();

    static inline
    symbol_type
    make_END ();

    static inline
    symbol_type
    make_FOR ();

    static inline
    symbol_type
    make_DO ();

    static inline
    symbol_type
    make_REPEAT ();

    static inline
    symbol_type
    make_UNTIL ();

    static inline
    symbol_type
    make_BREAK ();

    static inline
    symbol_type
    make_IN ();

    static inline
    symbol_type
    make_WHILE ();

    static inline
    symbol_type
    make_LOCAL ();

    static inline
    symbol_type
    make_ANY (const std::string& v);

    static inline
    symbol_type
    make_LENGTH ();

    static inline
    symbol_type
    make_NOT ();

    static inline
    symbol_type
    make_RETURN ();

    static inline
    symbol_type
    make_OR (const BoolComparatorType& v);

    static inline
    symbol_type
    make_AND (const BoolComparatorType& v);

    static inline
    symbol_type
    make_COMP (const BoolComparatorType& v);

    static inline
    symbol_type
    make_CONCAT ();

    static inline
    symbol_type
    make_NIL ();

    static inline
    symbol_type
    make_FALSE ();

    static inline
    symbol_type
    make_TRUE ();

    static inline
    symbol_type
    make_NUMBER (const double& v);

    static inline
    symbol_type
    make_STRING (const std::string& v);

    static inline
    symbol_type
    make_NAME (const std::string& v);

    static inline
    symbol_type
    make_NL ();

    static inline
    symbol_type
    make_BLK ();

    static inline
    symbol_type
    make_FUNCTION ();

    static inline
    symbol_type
    make_DDDOT ();


    /// Build a parser object.
    parser ();
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 384,     ///< Last index in yytable_.
      yynnts_ = 27,  ///< Number of nonterminal symbols.
      yyfinal_ = 3, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 51  ///< Number of tokens.
    };


  };

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    28,     2,     2,
      47,    48,    27,    25,    42,    26,    44,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    41,
       2,    20,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    21,    22,    23,    24,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40
    };
    const unsigned int user_token_number_max_ = 288;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
      switch (other.type_get ())
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        value.copy< BoolComparatorType > (other.value);
        break;

      case 34: // NUMBER
        value.copy< double > (other.value);
        break;

      case 52: // chunk
      case 53: // __stat
      case 54: // _semi
      case 55: // laststat
      case 56: // block
      case 57: // stat
      case 58: // __elseif
      case 59: // varlist
      case 60: // funcname
      case 61: // __dotname
      case 62: // var
      case 63: // namelist
      case 64: // explist
      case 65: // exp
      case 66: // prefixexp
      case 67: // functioncall
      case 68: // args
      case 69: // function
      case 70: // funcbody
      case 71: // parlist
      case 72: // tableconstructor
      case 73: // fieldlist
      case 74: // __fieldsepfield
      case 75: // field
      case 76: // fieldsep
      case 77: // binopexp
        value.copy< std::shared_ptr<Node> > (other.value);
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value ()
  {
    (void) v;
      switch (this->type_get ())
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        value.copy< BoolComparatorType > (v);
        break;

      case 34: // NUMBER
        value.copy< double > (v);
        break;

      case 52: // chunk
      case 53: // __stat
      case 54: // _semi
      case 55: // laststat
      case 56: // block
      case 57: // stat
      case 58: // __elseif
      case 59: // varlist
      case 60: // funcname
      case 61: // __dotname
      case 62: // var
      case 63: // namelist
      case 64: // explist
      case 65: // exp
      case 66: // prefixexp
      case 67: // functioncall
      case 68: // args
      case 69: // function
      case 70: // funcbody
      case 71: // parlist
      case 72: // tableconstructor
      case 73: // fieldlist
      case 74: // __fieldsepfield
      case 75: // field
      case 76: // fieldsep
      case 77: // binopexp
        value.copy< std::shared_ptr<Node> > (v);
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BoolComparatorType v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const double v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Node> v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v)
    : Base (t)
    , value (v)
  {}


  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        value.template destroy< BoolComparatorType > ();
        break;

      case 34: // NUMBER
        value.template destroy< double > ();
        break;

      case 52: // chunk
      case 53: // __stat
      case 54: // _semi
      case 55: // laststat
      case 56: // block
      case 57: // stat
      case 58: // __elseif
      case 59: // varlist
      case 60: // funcname
      case 61: // __dotname
      case 62: // var
      case 63: // namelist
      case 64: // explist
      case 65: // exp
      case 66: // prefixexp
      case 67: // functioncall
      case 68: // args
      case 69: // function
      case 70: // funcbody
      case 71: // parlist
      case 72: // tableconstructor
      case 73: // fieldlist
      case 74: // __fieldsepfield
      case 75: // field
      case 76: // fieldsep
      case 77: // binopexp
        value.template destroy< std::shared_ptr<Node> > ();
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        value.move< BoolComparatorType > (s.value);
        break;

      case 34: // NUMBER
        value.move< double > (s.value);
        break;

      case 52: // chunk
      case 53: // __stat
      case 54: // _semi
      case 55: // laststat
      case 56: // block
      case 57: // stat
      case 58: // __elseif
      case 59: // varlist
      case 60: // funcname
      case 61: // __dotname
      case 62: // var
      case 63: // namelist
      case 64: // explist
      case 65: // exp
      case 66: // prefixexp
      case 67: // functioncall
      case 68: // args
      case 69: // function
      case 70: // funcbody
      case 71: // parlist
      case 72: // tableconstructor
      case 73: // fieldlist
      case 74: // __fieldsepfield
      case 75: // field
      case 76: // fieldsep
      case 77: // binopexp
        value.move< std::shared_ptr<Node> > (s.value);
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }

  inline
  parser::token_type
  parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      61,   275,   276,   277,   278,    43,    45,    42,    37,    47,
      94,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,    59,    44,    58,    46,    91,    93,    40,    41,   123,
     125
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  parser::symbol_type
  parser::make_EOOF ()
  {
    return symbol_type (token::EOOF);
  }

  parser::symbol_type
  parser::make_IF ()
  {
    return symbol_type (token::IF);
  }

  parser::symbol_type
  parser::make_THEN ()
  {
    return symbol_type (token::THEN);
  }

  parser::symbol_type
  parser::make_ELSEIF ()
  {
    return symbol_type (token::ELSEIF);
  }

  parser::symbol_type
  parser::make_ELSE ()
  {
    return symbol_type (token::ELSE);
  }

  parser::symbol_type
  parser::make_END ()
  {
    return symbol_type (token::END);
  }

  parser::symbol_type
  parser::make_FOR ()
  {
    return symbol_type (token::FOR);
  }

  parser::symbol_type
  parser::make_DO ()
  {
    return symbol_type (token::DO);
  }

  parser::symbol_type
  parser::make_REPEAT ()
  {
    return symbol_type (token::REPEAT);
  }

  parser::symbol_type
  parser::make_UNTIL ()
  {
    return symbol_type (token::UNTIL);
  }

  parser::symbol_type
  parser::make_BREAK ()
  {
    return symbol_type (token::BREAK);
  }

  parser::symbol_type
  parser::make_IN ()
  {
    return symbol_type (token::IN);
  }

  parser::symbol_type
  parser::make_WHILE ()
  {
    return symbol_type (token::WHILE);
  }

  parser::symbol_type
  parser::make_LOCAL ()
  {
    return symbol_type (token::LOCAL);
  }

  parser::symbol_type
  parser::make_ANY (const std::string& v)
  {
    return symbol_type (token::ANY, v);
  }

  parser::symbol_type
  parser::make_LENGTH ()
  {
    return symbol_type (token::LENGTH);
  }

  parser::symbol_type
  parser::make_NOT ()
  {
    return symbol_type (token::NOT);
  }

  parser::symbol_type
  parser::make_RETURN ()
  {
    return symbol_type (token::RETURN);
  }

  parser::symbol_type
  parser::make_OR (const BoolComparatorType& v)
  {
    return symbol_type (token::OR, v);
  }

  parser::symbol_type
  parser::make_AND (const BoolComparatorType& v)
  {
    return symbol_type (token::AND, v);
  }

  parser::symbol_type
  parser::make_COMP (const BoolComparatorType& v)
  {
    return symbol_type (token::COMP, v);
  }

  parser::symbol_type
  parser::make_CONCAT ()
  {
    return symbol_type (token::CONCAT);
  }

  parser::symbol_type
  parser::make_NIL ()
  {
    return symbol_type (token::NIL);
  }

  parser::symbol_type
  parser::make_FALSE ()
  {
    return symbol_type (token::FALSE);
  }

  parser::symbol_type
  parser::make_TRUE ()
  {
    return symbol_type (token::TRUE);
  }

  parser::symbol_type
  parser::make_NUMBER (const double& v)
  {
    return symbol_type (token::NUMBER, v);
  }

  parser::symbol_type
  parser::make_STRING (const std::string& v)
  {
    return symbol_type (token::STRING, v);
  }

  parser::symbol_type
  parser::make_NAME (const std::string& v)
  {
    return symbol_type (token::NAME, v);
  }

  parser::symbol_type
  parser::make_NL ()
  {
    return symbol_type (token::NL);
  }

  parser::symbol_type
  parser::make_BLK ()
  {
    return symbol_type (token::BLK);
  }

  parser::symbol_type
  parser::make_FUNCTION ()
  {
    return symbol_type (token::FUNCTION);
  }

  parser::symbol_type
  parser::make_DDDOT ()
  {
    return symbol_type (token::DDDOT);
  }



} // yy
#line 1463 "binary.tab.h" // lalr1.cc:377




#endif // !YY_YY_BINARY_TAB_H_INCLUDED
