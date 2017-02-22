// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

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


// First part of user declarations.

#line 37 "binary.tab.c" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "binary.tab.h"

// User implementation prologue.

#line 51 "binary.tab.c" // lalr1.cc:412
// Unqualified %code blocks.
#line 49 "binary.y" // lalr1.cc:413

	#define YY_DECL yy::parser::symbol_type yylex()
	YY_DECL;
	#define spc std::static_pointer_cast
	#define dpc std::dynamic_pointer_cast

	std::shared_ptr<Node> root;

	void debug(std::string text) {
		std::cout << text << std::endl;
	}

#line 66 "binary.tab.c" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 133 "binary.tab.c" // lalr1.cc:479

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        value.move< BoolComparatorType > (that.value);
        break;

      case 34: // NUMBER
        value.move< double > (that.value);
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
        value.move< std::shared_ptr<Node> > (that.value);
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        value.copy< BoolComparatorType > (that.value);
        break;

      case 34: // NUMBER
        value.copy< double > (that.value);
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
        value.copy< std::shared_ptr<Node> > (that.value);
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 21: // OR
      case 22: // AND
      case 23: // COMP
        yylhs.value.build< BoolComparatorType > ();
        break;

      case 34: // NUMBER
        yylhs.value.build< double > ();
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
        yylhs.value.build< std::shared_ptr<Node> > ();
        break;

      case 16: // ANY
      case 35: // STRING
      case 36: // NAME
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 95 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
						root = yylhs.value.as< std::shared_ptr<Node> > ();
 					}
#line 596 "binary.tab.c" // lalr1.cc:859
    break;

  case 3:
#line 99 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<Chunk>(yystack_[2].value.as< std::shared_ptr<Node> > ());
						node->addStatement(dpc<Statement>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
						root = yylhs.value.as< std::shared_ptr<Node> > ();
					}
#line 607 "binary.tab.c" // lalr1.cc:859
    break;

  case 4:
#line 107 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<Chunk>();
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 616 "binary.tab.c" // lalr1.cc:859
    break;

  case 5:
#line 111 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<Chunk>(yystack_[2].value.as< std::shared_ptr<Node> > ());
						node->addStatement(dpc<Statement>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 626 "binary.tab.c" // lalr1.cc:859
    break;

  case 6:
#line 118 "binary.y" // lalr1.cc:859
    { }
#line 632 "binary.tab.c" // lalr1.cc:859
    break;

  case 7:
#line 119 "binary.y" // lalr1.cc:859
    { }
#line 638 "binary.tab.c" // lalr1.cc:859
    break;

  case 8:
#line 122 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ReturnStat>(dpc<ExprList>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
 					}
#line 647 "binary.tab.c" // lalr1.cc:859
    break;

  case 9:
#line 126 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ReturnStat>();
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 656 "binary.tab.c" // lalr1.cc:859
    break;

  case 10:
#line 130 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<BreakStat>();
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 665 "binary.tab.c" // lalr1.cc:859
    break;

  case 11:
#line 136 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > (); }
#line 671 "binary.tab.c" // lalr1.cc:859
    break;

  case 12:
#line 139 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<Assignment>(dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()), dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 680 "binary.tab.c" // lalr1.cc:859
    break;

  case 13:
#line 143 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = yystack_[1].value.as< std::shared_ptr<Node> > ();
					}
#line 688 "binary.tab.c" // lalr1.cc:859
    break;

  case 14:
#line 146 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<WhileLoop>(dpc<Expr>(yystack_[3].value.as< std::shared_ptr<Node> > ()), dpc<Statement>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 697 "binary.tab.c" // lalr1.cc:859
    break;

  case 15:
#line 150 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<RepeatLoop>(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()), dpc<Statement>(yystack_[2].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 706 "binary.tab.c" // lalr1.cc:859
    break;

  case 16:
#line 154 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<Selection>();
						auto ifStat = std::make_shared<IfStatement>(dpc<Expr>(yystack_[4].value.as< std::shared_ptr<Node> > ()),dpc<Statement>(yystack_[2].value.as< std::shared_ptr<Node> > ()));
						node->addElseIfStat(ifStat);
						for (auto child : dpc<NodeList>(yystack_[1].value.as< std::shared_ptr<Node> > ())->getChildren()){
							node->addElseIfStat(dpc<IfStatement>(child));
						}
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 720 "binary.tab.c" // lalr1.cc:859
    break;

  case 17:
#line 163 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<Selection>();
						auto ifStat = std::make_shared<IfStatement>(dpc<Expr>(yystack_[6].value.as< std::shared_ptr<Node> > ()),dpc<Statement>(yystack_[4].value.as< std::shared_ptr<Node> > ()));
						node->addElseIfStat(ifStat);
						for (auto child : dpc<NodeList>(yystack_[3].value.as< std::shared_ptr<Node> > ())->getChildren()){
							node->addElseIfStat(dpc<IfStatement>(child));
						}
						node->setElseStat(dpc<Statement>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 735 "binary.tab.c" // lalr1.cc:859
    break;

  case 18:
#line 173 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ForLoop>(yystack_[7].value.as< std::string > (),
							dpc<Expr>(yystack_[5].value.as< std::shared_ptr<Node> > ()),
							dpc<Expr>(yystack_[3].value.as< std::shared_ptr<Node> > ()),
							dpc<Expr>(std::make_shared<NumLiteral>(1)),
							dpc<Statement>(yystack_[1].value.as< std::shared_ptr<Node> > ())
							);
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 749 "binary.tab.c" // lalr1.cc:859
    break;

  case 19:
#line 182 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ForLoop>(yystack_[9].value.as< std::string > (),
							dpc<Expr>(yystack_[7].value.as< std::shared_ptr<Node> > ()),
							dpc<Expr>(yystack_[5].value.as< std::shared_ptr<Node> > ()),
							dpc<Expr>(yystack_[3].value.as< std::shared_ptr<Node> > ()),
							dpc<Statement>(yystack_[1].value.as< std::shared_ptr<Node> > ())
							);
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 763 "binary.tab.c" // lalr1.cc:859
    break;

  case 20:
#line 191 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<Node>("forlist", "");
					}
#line 771 "binary.tab.c" // lalr1.cc:859
    break;

  case 21:
#line 194 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<GlobalFunctionDef>(
							dpc<NameList>(yystack_[1].value.as< std::shared_ptr<Node> > ()),
							dpc<FunctionBody>(yystack_[0].value.as< std::shared_ptr<Node> > ())
							);
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 783 "binary.tab.c" // lalr1.cc:859
    break;

  case 22:
#line 201 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<LocalFunctionDef>(
							yystack_[1].value.as< std::string > (),
							dpc<FunctionBody>(yystack_[0].value.as< std::shared_ptr<Node> > ())
							);
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 795 "binary.tab.c" // lalr1.cc:859
    break;

  case 23:
#line 208 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<LocalDef>(dpc<NameList>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 804 "binary.tab.c" // lalr1.cc:859
    break;

  case 24:
#line 212 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<LocalAssignment>(dpc<NameList>(yystack_[2].value.as< std::shared_ptr<Node> > ()), dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 813 "binary.tab.c" // lalr1.cc:859
    break;

  case 25:
#line 218 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<NodeList>();
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 822 "binary.tab.c" // lalr1.cc:859
    break;

  case 26:
#line 222 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<NodeList>(yystack_[4].value.as< std::shared_ptr<Node> > ());
						auto ifStat = std::make_shared<IfStatement>(dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Statement>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						node->addChild(ifStat);
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 833 "binary.tab.c" // lalr1.cc:859
    break;

  case 27:
#line 230 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ExprList>();
						node->addExpression(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 843 "binary.tab.c" // lalr1.cc:859
    break;

  case 28:
#line 235 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<ExprList>(yystack_[2].value.as< std::shared_ptr<Node> > ());
						node->addExpression(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 853 "binary.tab.c" // lalr1.cc:859
    break;

  case 29:
#line 242 "binary.y" // lalr1.cc:859
    {
							auto node = std::make_shared<NameList>();
							node->addString(yystack_[1].value.as< std::string > ());
							for (auto name : dpc<NameList>(yystack_[0].value.as< std::shared_ptr<Node> > ())->getStrings()) {
								node->addString(name);
							}
							yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 866 "binary.tab.c" // lalr1.cc:859
    break;

  case 30:
#line 250 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<NameList>();
						node->addString(yystack_[3].value.as< std::string > ());
						for (auto name : dpc<NameList>(yystack_[2].value.as< std::shared_ptr<Node> > ())->getStrings()) {
							node->addString(name);
						}
						node->setSpecial(yystack_[0].value.as< std::string > ());
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 880 "binary.tab.c" // lalr1.cc:859
    break;

  case 31:
#line 261 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<NameList>();
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 889 "binary.tab.c" // lalr1.cc:859
    break;

  case 32:
#line 265 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<NameList>(yystack_[2].value.as< std::shared_ptr<Node> > ());
						node->addString(yystack_[0].value.as< std::string > ());
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 899 "binary.tab.c" // lalr1.cc:859
    break;

  case 33:
#line 272 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<VarName>(yystack_[0].value.as< std::string > ());
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 908 "binary.tab.c" // lalr1.cc:859
    break;

  case 34:
#line 276 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<VarIndex>(spc<Expr>(yystack_[3].value.as< std::shared_ptr<Node> > ()),spc<Expr>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 917 "binary.tab.c" // lalr1.cc:859
    break;

  case 35:
#line 280 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<VarIndex>(spc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),spc<Expr>(std::make_shared<StringLiteral>(yystack_[0].value.as< std::string > ())));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 926 "binary.tab.c" // lalr1.cc:859
    break;

  case 36:
#line 286 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<NameList>();
						node->addString(yystack_[0].value.as< std::string > ());
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 936 "binary.tab.c" // lalr1.cc:859
    break;

  case 37:
#line 291 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<NameList>(yystack_[2].value.as< std::shared_ptr<Node> > ());
						node->addString(yystack_[0].value.as< std::string > ());
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 946 "binary.tab.c" // lalr1.cc:859
    break;

  case 38:
#line 298 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ExprList>();
						node->addExpression(spc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 956 "binary.tab.c" // lalr1.cc:859
    break;

  case 39:
#line 303 "binary.y" // lalr1.cc:859
    {
						auto node = dpc<ExprList>(yystack_[2].value.as< std::shared_ptr<Node> > ());
						node->addExpression(spc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 966 "binary.tab.c" // lalr1.cc:859
    break;

  case 40:
#line 310 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NilLiteral>(); }
#line 972 "binary.tab.c" // lalr1.cc:859
    break;

  case 41:
#line 311 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<BoolLiteral>(false); }
#line 978 "binary.tab.c" // lalr1.cc:859
    break;

  case 42:
#line 312 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<BoolLiteral>(true); }
#line 984 "binary.tab.c" // lalr1.cc:859
    break;

  case 43:
#line 313 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumLiteral>(yystack_[0].value.as< double > ()); }
#line 990 "binary.tab.c" // lalr1.cc:859
    break;

  case 44:
#line 314 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<StringLiteral>(yystack_[0].value.as< std::string > ()); }
#line 996 "binary.tab.c" // lalr1.cc:859
    break;

  case 45:
#line 315 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<StringLiteral>("..."); }
#line 1002 "binary.tab.c" // lalr1.cc:859
    break;

  case 46:
#line 316 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > (); }
#line 1008 "binary.tab.c" // lalr1.cc:859
    break;

  case 47:
#line 317 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > (); }
#line 1014 "binary.tab.c" // lalr1.cc:859
    break;

  case 48:
#line 318 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > (); }
#line 1020 "binary.tab.c" // lalr1.cc:859
    break;

  case 49:
#line 319 "binary.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > (); }
#line 1026 "binary.tab.c" // lalr1.cc:859
    break;

  case 50:
#line 320 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::MINUS,spc<Expr>(std::make_shared<NumLiteral>(0)),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
					}
#line 1034 "binary.tab.c" // lalr1.cc:859
    break;

  case 51:
#line 323 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<NotOperator>(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 1043 "binary.tab.c" // lalr1.cc:859
    break;

  case 52:
#line 327 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<LengthOperator>(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 1052 "binary.tab.c" // lalr1.cc:859
    break;

  case 53:
#line 333 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
					}
#line 1060 "binary.tab.c" // lalr1.cc:859
    break;

  case 54:
#line 336 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
					}
#line 1068 "binary.tab.c" // lalr1.cc:859
    break;

  case 55:
#line 339 "binary.y" // lalr1.cc:859
    {
						yylhs.value.as< std::shared_ptr<Node> > () = yystack_[1].value.as< std::shared_ptr<Node> > ();
					}
#line 1076 "binary.tab.c" // lalr1.cc:859
    break;

  case 56:
#line 344 "binary.y" // lalr1.cc:859
    {
						auto node = std::make_shared<ExprStatement>(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
						yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
					}
#line 1085 "binary.tab.c" // lalr1.cc:859
    break;

  case 57:
#line 350 "binary.y" // lalr1.cc:859
    {
										auto node = std::make_shared<FunctionCall>(dpc<Expr>(yystack_[1].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
										yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
									}
#line 1094 "binary.tab.c" // lalr1.cc:859
    break;

  case 58:
#line 354 "binary.y" // lalr1.cc:859
    {
										auto node = std::make_shared<FunctionCall>(dpc<Expr>(yystack_[3].value.as< std::shared_ptr<Node> > ()), yystack_[1].value.as< std::string > (), dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
										yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
									}
#line 1103 "binary.tab.c" // lalr1.cc:859
    break;

  case 59:
#line 360 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<ExprList>();
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1112 "binary.tab.c" // lalr1.cc:859
    break;

  case 60:
#line 364 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = yystack_[1].value.as< std::shared_ptr<Node> > ();
				}
#line 1120 "binary.tab.c" // lalr1.cc:859
    break;

  case 61:
#line 367 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
				}
#line 1128 "binary.tab.c" // lalr1.cc:859
    break;

  case 62:
#line 370 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<StringLiteral>(yystack_[0].value.as< std::string > ());
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1137 "binary.tab.c" // lalr1.cc:859
    break;

  case 63:
#line 376 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
				}
#line 1145 "binary.tab.c" // lalr1.cc:859
    break;

  case 64:
#line 381 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<FunctionBody>(std::make_shared<NameList>(),dpc<Chunk>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1154 "binary.tab.c" // lalr1.cc:859
    break;

  case 65:
#line 385 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<FunctionBody>(dpc<NameList>(yystack_[3].value.as< std::shared_ptr<Node> > ()),dpc<Chunk>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1163 "binary.tab.c" // lalr1.cc:859
    break;

  case 66:
#line 391 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
				}
#line 1171 "binary.tab.c" // lalr1.cc:859
    break;

  case 67:
#line 394 "binary.y" // lalr1.cc:859
    {
					auto node = dpc<NameList>(yystack_[2].value.as< std::shared_ptr<Node> > ());
					node->addString("...");
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1181 "binary.tab.c" // lalr1.cc:859
    break;

  case 68:
#line 399 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<NameList>();
					node->addString("...");
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1191 "binary.tab.c" // lalr1.cc:859
    break;

  case 69:
#line 406 "binary.y" // lalr1.cc:859
    {
										auto node = std::make_shared<TableConstructor>();
										yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
									}
#line 1200 "binary.tab.c" // lalr1.cc:859
    break;

  case 70:
#line 410 "binary.y" // lalr1.cc:859
    {
										auto node = std::make_shared<TableConstructor>(dpc<FieldList>(yystack_[1].value.as< std::shared_ptr<Node> > ()));
										yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
									}
#line 1209 "binary.tab.c" // lalr1.cc:859
    break;

  case 71:
#line 416 "binary.y" // lalr1.cc:859
    {
										yylhs.value.as< std::shared_ptr<Node> > () = yystack_[0].value.as< std::shared_ptr<Node> > ();
									}
#line 1217 "binary.tab.c" // lalr1.cc:859
    break;

  case 72:
#line 419 "binary.y" // lalr1.cc:859
    {
										yylhs.value.as< std::shared_ptr<Node> > () = yystack_[1].value.as< std::shared_ptr<Node> > ();
									}
#line 1225 "binary.tab.c" // lalr1.cc:859
    break;

  case 73:
#line 424 "binary.y" // lalr1.cc:859
    {
										auto node = std::make_shared<FieldList>();
										node->addField(dpc<Field>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
										yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
 									}
#line 1235 "binary.tab.c" // lalr1.cc:859
    break;

  case 74:
#line 429 "binary.y" // lalr1.cc:859
    {
										auto node = dpc<FieldList>(yystack_[2].value.as< std::shared_ptr<Node> > ());
										node->addField(dpc<Field>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
										yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
									}
#line 1245 "binary.tab.c" // lalr1.cc:859
    break;

  case 75:
#line 436 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<FieldIndex>(dpc<Expr>(yystack_[3].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1254 "binary.tab.c" // lalr1.cc:859
    break;

  case 76:
#line 440 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<FieldIndex>(std::make_shared<StringLiteral>(yystack_[2].value.as< std::string > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1263 "binary.tab.c" // lalr1.cc:859
    break;

  case 77:
#line 444 "binary.y" // lalr1.cc:859
    {
					auto node = std::make_shared<FieldCount>(dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
					yylhs.value.as< std::shared_ptr<Node> > () = spc<Node>(node);
				}
#line 1272 "binary.tab.c" // lalr1.cc:859
    break;

  case 78:
#line 450 "binary.y" // lalr1.cc:859
    { }
#line 1278 "binary.tab.c" // lalr1.cc:859
    break;

  case 79:
#line 451 "binary.y" // lalr1.cc:859
    { }
#line 1284 "binary.tab.c" // lalr1.cc:859
    break;

  case 80:
#line 454 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::PLUS,dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1292 "binary.tab.c" // lalr1.cc:859
    break;

  case 81:
#line 457 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::MINUS,dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1300 "binary.tab.c" // lalr1.cc:859
    break;

  case 82:
#line 460 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::MUL,dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1308 "binary.tab.c" // lalr1.cc:859
    break;

  case 83:
#line 463 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::DIV,dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1316 "binary.tab.c" // lalr1.cc:859
    break;

  case 84:
#line 466 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::POW,dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1324 "binary.tab.c" // lalr1.cc:859
    break;

  case 85:
#line 469 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<NumOperator>(NumOperatorType::MOD,dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1332 "binary.tab.c" // lalr1.cc:859
    break;

  case 86:
#line 472 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<StringOperator>(dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1340 "binary.tab.c" // lalr1.cc:859
    break;

  case 87:
#line 475 "binary.y" // lalr1.cc:859
    {
					 yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<BoolComparator>(yystack_[1].value.as< BoolComparatorType > (),dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				 }
#line 1348 "binary.tab.c" // lalr1.cc:859
    break;

  case 88:
#line 478 "binary.y" // lalr1.cc:859
    {
					yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<BoolComparator>(yystack_[1].value.as< BoolComparatorType > (),dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				}
#line 1356 "binary.tab.c" // lalr1.cc:859
    break;

  case 89:
#line 481 "binary.y" // lalr1.cc:859
    {
					 yylhs.value.as< std::shared_ptr<Node> > () = std::make_shared<BoolComparator>(yystack_[1].value.as< BoolComparatorType > (),dpc<Expr>(yystack_[2].value.as< std::shared_ptr<Node> > ()),dpc<Expr>(yystack_[0].value.as< std::shared_ptr<Node> > ()));
				 }
#line 1364 "binary.tab.c" // lalr1.cc:859
    break;


#line 1368 "binary.tab.c" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -49;

  const signed char parser::yytable_ninf_ = -55;

  const short int
  parser::yypact_[] =
  {
     -49,    16,    26,   -49,   202,     3,   -49,   -49,   -49,   202,
      15,   202,   -49,    13,   202,    -4,    -4,   -15,     5,    94,
     238,   202,   202,   202,   -49,   -49,   -49,   -49,   -49,     9,
     -49,    85,   -49,   241,    94,   -49,   -49,   -49,   -49,    24,
       8,   -49,    57,    61,   314,   -49,    38,    10,    49,   335,
     -49,     9,   231,   -49,   -49,   -49,   202,    19,   -49,    56,
      73,   202,   162,   -49,   -49,    80,    80,    77,    21,   -49,
      92,   202,   -49,   335,    64,   -28,   -49,   -49,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
      79,   -49,   202,   -49,     9,   202,   202,   -11,   -49,   -49,
      49,    11,   -23,   -49,   278,   -49,   -25,   -49,   -49,    81,
      74,   202,   288,   -49,   -49,   -49,   182,   -49,   303,   354,
      70,    70,    77,    77,    58,    58,    80,    80,   324,     1,
     -49,   335,   124,   -49,    49,   335,    97,   104,   -49,   -49,
     -49,   137,    31,   -49,   335,   126,   -49,   121,   202,   -49,
     -49,   -49,   -49,   -49,   -49,   140,   202,   202,   -49,   -49,
     148,   141,   -49,   335,   268,   142,   -49,   202,   -49,   -49,
     -49,   143,   346,   -49,   -49,   -49,   145,   -49
  };

  const unsigned char
  parser::yydefact_[] =
  {
       4,     0,     2,     1,     0,     0,     4,     4,    10,     0,
       0,     9,    33,     0,     0,     6,     6,     0,    53,     0,
      56,     0,     0,     0,    40,    41,    42,    43,    44,     0,
      45,     0,    53,     0,    47,    54,    46,    48,    49,    36,
       0,    11,     0,     0,     0,    36,     0,    23,     8,    38,
      31,     0,     0,     7,     3,     5,     0,     0,    62,     0,
       0,     0,     0,    57,    61,    52,    51,    50,     0,    63,
      33,     0,    69,    77,     0,    71,    73,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     4,     0,     0,     0,    29,    21,    55,
      12,    53,     0,    35,     0,    59,     0,    68,     4,    66,
       0,     0,     0,    70,    79,    78,    72,    25,    89,    88,
      87,    86,    80,    81,    82,    85,    83,    84,     0,     0,
      37,    15,     0,    22,    24,    39,     0,     0,    58,    34,
      60,     0,     0,     4,    76,     0,    74,     0,     0,     4,
      14,    30,    32,    64,    67,     0,     0,     0,     4,    16,
       0,     0,    65,    75,     0,     0,     4,     0,    20,     4,
      17,     0,     0,    26,    18,     4,     0,    19
  };

  const short int
  parser::yypgoto_[] =
  {
     -49,   155,   -49,   144,   -49,    -7,   -49,   -49,   -49,   -49,
     -49,     2,    -8,   -47,    -3,     6,   154,    59,   -49,   -48,
     -49,   -12,   -49,   -49,    42,   -49,   -49
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,    41,     2,    54,    15,    42,    16,   147,    17,    51,
      97,    32,    40,    48,    49,    34,    35,    63,    36,    69,
     110,    37,    74,    75,    76,   116,    38
  };

  const short int
  parser::yytable_[] =
  {
      43,    33,    47,    98,    18,    56,    44,    64,    19,   100,
     149,    52,    58,   114,   115,   106,     3,    96,    65,    66,
      67,    89,    64,   140,    62,   -27,    31,    57,    73,     4,
      95,   -28,   136,   137,     5,     6,     7,    53,     8,    39,
       9,    10,   129,    96,    88,    11,   133,   -27,   134,    50,
      90,    45,    90,   -28,    46,    12,    68,    45,   104,   101,
     109,   107,    12,    19,    91,    13,    14,   130,   112,   108,
     117,   154,    92,    14,    94,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   132,    86,    87,   131,
      64,    96,   102,   135,    81,    82,    83,    84,    85,    86,
      87,   141,    21,    22,    84,    85,    86,    87,   144,   103,
      87,    23,   111,    73,   113,   130,    24,    25,    26,    27,
      28,    70,   143,   142,    29,    30,   157,   158,   159,    58,
      71,   150,    14,   151,    31,    72,   155,    59,    60,    61,
     152,    62,   161,    31,   153,   160,   156,   162,   168,   170,
     174,   165,   177,   163,   164,     1,    20,   166,   146,   171,
      55,   138,   173,     0,   172,     0,     0,     0,   176,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,     0,
     167,     0,     0,    24,    25,    26,    27,    28,    12,    21,
      22,    29,    30,     0,     0,     0,     0,     0,    23,    14,
     105,    31,     0,    24,    25,    26,    27,    28,    70,    21,
      22,    29,    30,     0,     0,     0,     0,    71,    23,    14,
       0,    31,     0,    24,    25,    26,    27,    28,    12,     0,
       0,    29,    30,     0,     0,    77,     0,     0,     0,    14,
       0,    31,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   169,   -54,     0,     0,     0,     0,     0,    99,
       0,   -54,   -54,   -54,     0,   -54,     0,   -54,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,     0,
       0,     0,     0,    93,   139,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   145,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,   175,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   148,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    80,    81,    82,
      83,    84,    85,    86,    87
  };

  const short int
  parser::yycheck_[] =
  {
       7,     4,    10,    51,     2,    20,     9,    19,     2,    56,
       9,    14,    35,    41,    42,    62,     0,    42,    21,    22,
      23,    13,    34,    48,    47,    20,    49,    42,    31,     3,
      20,    20,    43,    44,     8,     9,    10,    41,    12,    36,
      14,    15,    89,    42,    20,    19,    94,    42,    95,    36,
      42,    36,    42,    42,    39,    36,    47,    36,    61,    57,
      68,    40,    36,    57,     7,    39,    47,    36,    71,    48,
      77,    40,    11,    47,    36,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    93,    29,    30,    92,
     102,    42,    36,    96,    24,    25,    26,    27,    28,    29,
      30,   108,    17,    18,    27,    28,    29,    30,   111,    36,
      30,    26,    20,   116,    50,    36,    31,    32,    33,    34,
      35,    36,    48,    42,    39,    40,     5,     6,     7,    35,
      45,     7,    47,    36,    49,    50,   143,    43,    44,    45,
      36,    47,   149,    49,     7,   148,    20,     7,     7,     7,
       7,   158,     7,   156,   157,     0,     2,     9,   116,   166,
      16,   102,   169,    -1,   167,    -1,    -1,    -1,   175,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      42,    -1,    -1,    31,    32,    33,    34,    35,    36,    17,
      18,    39,    40,    -1,    -1,    -1,    -1,    -1,    26,    47,
      48,    49,    -1,    31,    32,    33,    34,    35,    36,    17,
      18,    39,    40,    -1,    -1,    -1,    -1,    45,    26,    47,
      -1,    49,    -1,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    40,    -1,    -1,     4,    -1,    -1,    -1,    47,
      -1,    49,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     4,    35,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    43,    44,    45,    -1,    47,    -1,    49,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,     9,    46,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    46,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     9,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    42,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    23,    24,    25,
      26,    27,    28,    29,    30
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    52,    53,     0,     3,     8,     9,    10,    12,    14,
      15,    19,    36,    39,    47,    55,    57,    59,    62,    66,
      67,    17,    18,    26,    31,    32,    33,    34,    35,    39,
      40,    49,    62,    65,    66,    67,    69,    72,    77,    36,
      63,    52,    56,    56,    65,    36,    39,    63,    64,    65,
      36,    60,    65,    41,    54,    54,    20,    42,    35,    43,
      44,    45,    47,    68,    72,    65,    65,    65,    47,    70,
      36,    45,    50,    65,    73,    74,    75,     4,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    20,    13,
      42,     7,    11,     9,    36,    20,    42,    61,    70,    48,
      64,    62,    36,    36,    65,    48,    64,    40,    48,    63,
      71,    20,    65,    50,    41,    42,    76,    56,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    64,
      36,    65,    56,    70,    64,    65,    43,    44,    68,    46,
      48,    56,    42,    48,    65,    46,    75,    58,    42,     9,
       7,    36,    36,     7,    40,    56,    20,     5,     6,     7,
      65,    56,     7,    65,    65,    56,     9,    42,     7,     4,
       7,    56,    65,    56,     7,     9,    56,     7
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    57,    67,    67,    68,
      68,    68,    68,    69,    70,    70,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     0,     3,     0,     1,     2,     1,
       1,     1,     3,     3,     5,     4,     6,     8,     9,    11,
       7,     3,     4,     2,     4,     0,     5,     1,     3,     2,
       4,     0,     3,     1,     4,     3,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     1,     1,     3,     1,     2,     4,     2,
       3,     1,     1,     2,     4,     5,     1,     3,     1,     2,
       3,     1,     2,     1,     3,     5,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "IF", "THEN", "ELSEIF",
  "ELSE", "END", "FOR", "DO", "REPEAT", "UNTIL", "BREAK", "IN", "WHILE",
  "LOCAL", "ANY", "LENGTH", "NOT", "RETURN", "'='", "OR", "AND", "COMP",
  "CONCAT", "'+'", "'-'", "'*'", "'%'", "'/'", "'^'", "NIL", "FALSE",
  "TRUE", "NUMBER", "STRING", "NAME", "NL", "BLK", "FUNCTION", "DDDOT",
  "';'", "','", "':'", "'.'", "'['", "']'", "'('", "')'", "'{'", "'}'",
  "$accept", "chunk", "__stat", "_semi", "laststat", "block", "stat",
  "__elseif", "varlist", "funcname", "__dotname", "var", "namelist",
  "explist", "exp", "prefixexp", "functioncall", "args", "function",
  "funcbody", "parlist", "tableconstructor", "fieldlist",
  "__fieldsepfield", "field", "fieldsep", "binopexp", YY_NULLPTR
  };


  const unsigned short int
  parser::yyrline_[] =
  {
       0,    95,    95,    99,   107,   111,   118,   119,   122,   126,
     130,   136,   139,   143,   146,   150,   154,   163,   173,   182,
     191,   194,   201,   208,   212,   218,   222,   230,   235,   242,
     250,   261,   265,   272,   276,   280,   286,   291,   298,   303,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   323,   327,   333,   336,   339,   344,   350,   354,   360,
     364,   367,   370,   376,   381,   385,   391,   394,   399,   406,
     410,   416,   419,   424,   429,   436,   440,   444,   450,   451,
     454,   457,   460,   463,   466,   469,   472,   475,   478,   481
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1801 "binary.tab.c" // lalr1.cc:1167
#line 485 "binary.y" // lalr1.cc:1168

