// A Bison parser, made by GNU Bison 3.0.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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
// //                    "%code top" blocks.
#line 23 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:399

        
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "lexer.h"
#include "declarations.hpp"
#include "driver.h"
#undef yylex
#define yylex driver.lexer->lex


#line 47 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:399


// First part of user declarations.
#line 1 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:406
        
int yydebug = 1;

#line 55 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 69 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:414


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 155 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:481

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    value = that.value;
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
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
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  Parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
    #line 42 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:737
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 509 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:737

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
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
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 131 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << *(yystack_[0].value.a); }
#line 620 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 10:
#line 143 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("globaldeclaration", {(yystack_[0].value.a)}); }
#line 626 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 11:
#line 144 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a)->add((yystack_[0].value.a)); }
#line 632 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 15:
#line 153 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("variabledeclaration", {(yystack_[2].value.a), (yystack_[1].value.a)}); }
#line 638 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 17:
#line 160 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("function_decl", {(yystack_[1].value.a), (yystack_[0].value.a)}); }
#line 644 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 18:
#line 164 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("function_header", {(yystack_[1].value.a), (yystack_[0].value.a)}); }
#line 650 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 19:
#line 167 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("function_header", {(yystack_[1].value.a), (yystack_[0].value.a)}); }
#line 656 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 20:
#line 170 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("functiondeclarator", {(yystack_[3].value.a), (yystack_[1].value.a)}); }
#line 662 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 21:
#line 171 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("functiondeclarator", {(yystack_[2].value.a)}); }
#line 668 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 22:
#line 174 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("formalparameterlist", {(yystack_[0].value.a)}); }
#line 674 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 23:
#line 175 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a)->add((yystack_[0].value.a)); }
#line 680 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 24:
#line 178 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("formalparameter", {(yystack_[1].value.a), (yystack_[0].value.a)}); }
#line 686 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 25:
#line 182 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("mainfunctiondeclaration", {(yystack_[1].value.a), (yystack_[0].value.a)}); }
#line 692 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 26:
#line 185 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = (yystack_[2].value.a); }
#line 698 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 27:
#line 188 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("block", {(yystack_[1].value.a)}); }
#line 704 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 28:
#line 189 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("block"); }
#line 710 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 29:
#line 193 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("blockstatements", {(yystack_[0].value.a)}); }
#line 716 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 30:
#line 194 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a)->add((yystack_[0].value.a)); }
#line 722 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 34:
#line 202 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("nullstatement"); }
#line 728 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 35:
#line 203 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = (yystack_[1].value.a); }
#line 734 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 37:
#line 205 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("return", {(yystack_[1].value.a)}); }
#line 740 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 39:
#line 207 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("if", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 746 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 40:
#line 208 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("ifelse", {(yystack_[4].value.a),(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 752 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 41:
#line 209 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("while", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 758 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 42:
#line 212 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("statementexpression", {(yystack_[0].value.a)}); }
#line 764 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 43:
#line 213 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("retstatementexpressionurn", {(yystack_[0].value.a)}); }
#line 770 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 45:
#line 217 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = (yystack_[1].value.a); }
#line 776 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 47:
#line 221 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("argumentlist", {(yystack_[0].value.a)}); }
#line 782 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 48:
#line 222 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a)->add((yystack_[0].value.a)); }
#line 788 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 49:
#line 225 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("functioninvocation", {(yystack_[3].value.a),(yystack_[1].value.a)}); }
#line 794 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 50:
#line 226 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("functioninvocation", {(yystack_[2].value.a)}); }
#line 800 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 53:
#line 233 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("-", {(yystack_[0].value.a)}); }
#line 806 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 54:
#line 234 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("!", {(yystack_[0].value.a)}); }
#line 812 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 57:
#line 239 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("*", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 818 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 58:
#line 240 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("/", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 824 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 59:
#line 241 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("%", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 830 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 61:
#line 245 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("+", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 836 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 62:
#line 246 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("-", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 842 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 64:
#line 250 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("<", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 848 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 65:
#line 251 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode(">", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 854 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 66:
#line 252 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("<=", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 860 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 67:
#line 253 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode(">=", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 866 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 69:
#line 257 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("==", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 872 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 70:
#line 258 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("!=", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 878 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 72:
#line 262 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("&&", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 884 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 74:
#line 266 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("||", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 890 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 77:
#line 273 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { (yylhs.value.a) = new ASTNode("=", {(yystack_[2].value.a),(yystack_[0].value.a)}); }
#line 896 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;


#line 900 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
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

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -77;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      17,   -77,   -77,   -77,    11,    28,    11,    17,   -77,   -77,
      43,   -77,   -16,   -77,   -16,    46,   -77,   -77,    -4,   -77,
     -77,     3,    38,   -77,   -77,     4,   -77,   -77,    74,    80,
      92,    49,   -77,   -77,    11,   -77,   -13,   -77,    85,   -77,
     -77,    82,   -77,   -77,   -77,    11,     8,   -77,   145,   145,
     -77,   -77,   -77,   -77,   145,   145,   145,   -77,   -77,   -13,
     -77,   -77,   -77,   -77,    53,    32,    36,    40,    98,    99,
     -77,   -77,    89,   -77,    91,   145,   131,   -77,   -77,   -77,
     -77,   -77,    78,   107,   108,   100,   -77,   -77,   109,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   -77,   -77,   -77,    22,   -77,   -77,   111,   111,
     -77,   -77,   -77,   -77,    53,    53,    32,    32,    32,    32,
      36,    36,    40,    98,   -77,   145,   125,   -77,   -77,   111,
     -77
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,    16,     8,     9,     0,     0,     0,     3,    10,    12,
       0,    13,     0,    14,     0,     0,    19,     1,     0,    18,
      11,     0,     0,    17,    25,     0,    15,    26,     0,     0,
       0,     0,    28,    34,     0,    31,     0,    33,     0,    29,
      32,     0,    43,    42,    21,     0,     0,    22,     0,     0,
       4,     5,     6,     7,     0,     0,     0,    38,    44,    52,
      51,    46,    55,    56,    60,    63,    68,    71,    73,    75,
      78,    76,     0,    36,     0,     0,     0,    27,    30,    35,
      24,    20,     0,     0,     0,    52,    53,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    77,    50,     0,    47,    23,     0,     0,
      45,    57,    58,    59,    61,    62,    64,    65,    67,    66,
      69,    70,    72,    74,    49,     0,    39,    41,    48,     0,
      40
  };

  const short int
  Parser::yypgoto_[] =
  {
     -77,   -77,   -77,   -14,   -77,   138,     1,     0,   -77,   -77,
     141,   -77,    72,   -77,   -77,    71,   -77,   115,   -76,   -77,
     -77,   -77,   -19,   -77,   -39,    29,   -15,     2,    57,    58,
     -77,    83,   -17,   -47
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     5,    58,     6,     7,     8,     9,    85,    11,    12,
      16,    46,    47,    13,    14,    37,    38,    39,    40,    41,
      60,   105,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72
  };

  const unsigned char
  Parser::yytable_[] =
  {
      10,    83,    84,    42,    15,    43,    18,    10,    34,    88,
      75,    45,     2,     3,     1,    86,    87,    22,    76,    42,
       1,    43,    36,    35,    34,     2,     3,    25,    17,   106,
      59,    26,   126,   127,    74,    27,    44,     4,    36,    35,
      81,     1,    92,    93,    82,    80,     2,     3,    59,    59,
     111,   112,   113,   130,   124,    28,    59,    29,   125,    30,
      31,    94,    95,    96,    97,    89,    90,    91,    45,    98,
      99,    22,    32,    33,    21,    59,    59,    25,   128,   116,
     117,   118,   119,    23,    73,    24,     2,     3,     1,    42,
      42,    43,    43,     2,     3,     1,    50,    51,    52,    53,
     120,   121,    28,    54,    29,    48,    30,    31,    36,    36,
      42,    49,    43,   100,     1,   101,    55,    79,    22,    77,
      33,   114,   115,    56,   102,    59,    26,    57,    28,    36,
      29,    76,    30,    31,     1,    50,    51,    52,    53,   108,
     109,   110,    54,   129,    22,    20,    33,    19,     1,    50,
      51,    52,    53,    78,   107,    55,    54,   122,   103,   123,
       0,     0,    56,   104,     0,     0,     0,     0,     0,    55,
       0,     0,     0,     0,     0,     0,    56
  };

  const short int
  Parser::yycheck_[] =
  {
       0,    48,    49,    22,     4,    22,     6,     7,    22,    56,
      23,    25,     8,     9,     3,    54,    55,    33,    31,    38,
       3,    38,    22,    22,    38,     8,     9,    31,     0,    76,
      30,    35,   108,   109,    34,    32,    32,    20,    38,    38,
      32,     3,    10,    11,    36,    45,     8,     9,    48,    49,
      89,    90,    91,   129,    32,    17,    56,    19,    36,    21,
      22,    25,    26,    27,    28,    12,    13,    14,    82,    29,
      30,    33,    34,    35,    31,    75,    76,    31,   125,    94,
      95,    96,    97,    12,    35,    14,     8,     9,     3,   108,
     109,   108,   109,     8,     9,     3,     4,     5,     6,     7,
      98,    99,    17,    11,    19,    31,    21,    22,   108,   109,
     129,    31,   129,    15,     3,    16,    24,    35,    33,    34,
      35,    92,    93,    31,    35,   125,    35,    35,    17,   129,
      19,    31,    21,    22,     3,     4,     5,     6,     7,    32,
      32,    32,    11,    18,    33,     7,    35,     6,     3,     4,
       5,     6,     7,    38,    82,    24,    11,   100,    75,   101,
      -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     8,     9,    20,    38,    40,    41,    42,    43,
      44,    45,    46,    50,    51,    44,    47,     0,    44,    47,
      42,    31,    33,    52,    52,    31,    35,    32,    17,    19,
      21,    22,    34,    35,    40,    43,    44,    52,    53,    54,
      55,    56,    59,    69,    32,    40,    48,    49,    31,    31,
       4,     5,     6,     7,    11,    24,    31,    35,    39,    44,
      57,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    35,    44,    23,    31,    34,    54,    35,
      44,    32,    36,    70,    70,    44,    61,    61,    70,    12,
      13,    14,    10,    11,    25,    26,    27,    28,    29,    30,
      15,    16,    35,    68,    32,    58,    70,    49,    32,    32,
      32,    61,    61,    61,    62,    62,    63,    63,    63,    63,
      64,    64,    65,    66,    32,    36,    55,    55,    70,    18,
      55
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    37,    38,    38,    39,    39,    39,    39,    40,    40,
      41,    41,    42,    42,    42,    43,    44,    45,    46,    46,
      47,    47,    48,    48,    49,    50,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    56,    57,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      63,    63,    63,    64,    64,    64,    64,    64,    65,    65,
      65,    66,    66,    67,    67,    68,    68,    69,    70
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     3,     1,     2,     2,     2,
       4,     3,     1,     3,     2,     2,     3,     3,     2,     1,
       2,     1,     1,     1,     1,     2,     2,     3,     2,     5,
       7,     5,     1,     1,     1,     3,     1,     1,     3,     4,
       3,     1,     1,     2,     2,     1,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "END", "error", "$undefined", "ID", "NUMBER", "STRING_LITERAL", "TRUE",
  "FALSE", "BOOLEAN", "INT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MODULO", "AND", "OR", "IF", "ELSE", "WHILE", "VOID", "RETURN", "BREAK",
  "ASSIGNMENT", "NOT", "LT", "GT", "GE", "LE", "EQ", "NE",
  "PARENTHESIS_OPEN", "PARENTHESIS_CLOSE", "BRACE_OPEN", "BRACE_CLOSE",
  "SEMICOLON", "COMMA", "$accept", "start", "literal", "type",
  "globaldeclarations", "globaldeclaration", "variabledeclaration",
  "identifier", "functiondeclaration", "functionheader",
  "functiondeclarator", "formalparameterlist", "formalparameter",
  "mainfunctiondeclaration", "mainfunctiondeclarator", "block",
  "blockstatements", "blockstatement", "statement", "statementexpression",
  "primary", "argumentlist", "functioninvocation", "postfixexpression",
  "unaryexpression", "multiplicativeexpression", "additiveexpression",
  "relationalexpression", "equalityexpression", "conditionalandexpression",
  "conditionalorexpression", "assignmentexpression", "assignment",
  "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   130,   130,   131,   134,   135,   136,   137,   139,   140,
     143,   144,   147,   148,   149,   153,   156,   159,   163,   166,
     170,   171,   174,   175,   178,   181,   185,   188,   189,   192,
     194,   197,   198,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   212,   213,   216,   217,   218,   221,   222,   225,
     226,   229,   230,   233,   234,   235,   238,   239,   240,   241,
     244,   245,   246,   249,   250,   251,   252,   253,   256,   257,
     258,   261,   262,   265,   266,   269,   270,   273,   276
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
    };
    const unsigned user_token_number_max_ = 291;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1425 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:1163
#line 279 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:1164


void yy::Parser::error(const location_type& l, const std::string& m)
{
        driver.error(l, m);
}
