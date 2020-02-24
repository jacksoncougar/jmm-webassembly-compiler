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


// First part of user declarations.
#line 13 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:406

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "lexer.h"
#include "declarations.h"
#include "driver.h"

#undef yylex
#define yylex driver.lexer->lex




#line 51 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 65 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:414


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
#line 132 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:481

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

  Parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
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
  {
    value = other.value;
  }

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
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
    : super_type (that.state)
  {
    value = that.value;
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
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
        << ' ' << yytname_[yytype] << " (";
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

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


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
            yyla.type = yytranslate_ (yylex (&yyla.value));
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


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 11:
#line 97 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 573 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 14:
#line 103 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclaration\n"; }
#line 579 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 15:
#line 107 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "variabledeclaration\n"; }
#line 585 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 16:
#line 111 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "identifier\n"; }
#line 591 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 17:
#line 115 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "functiondeclaration\n"; }
#line 597 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 19:
#line 120 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 603 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 21:
#line 125 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 609 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 23:
#line 130 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 615 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 24:
#line 134 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 621 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 25:
#line 138 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 627 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 26:
#line 142 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 633 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 28:
#line 147 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 639 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 30:
#line 152 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 645 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 32:
#line 157 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 651 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 41:
#line 169 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 657 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 43:
#line 174 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 663 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 46:
#line 180 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 669 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 48:
#line 185 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 675 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 50:
#line 190 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 681 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 52:
#line 195 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 687 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 55:
#line 201 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 693 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 59:
#line 208 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 699 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 62:
#line 214 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 705 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 67:
#line 222 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 711 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 70:
#line 228 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 717 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 72:
#line 233 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 723 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 74:
#line 238 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 729 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 76:
#line 243 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 735 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 77:
#line 247 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 741 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;

  case 78:
#line 251 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:856
    { std::cout << "globaldeclarations\n"; }
#line 747 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
    break;


#line 751 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:856
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
    error (yyexc.what ());
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


  const signed char Parser::yypact_ninf_ = -59;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
     128,   -59,   -59,   -59,     8,    18,     8,   128,   -59,   -59,
       6,   -59,    15,   -59,    15,    45,   -59,   -59,    46,   -59,
     -59,    75,    98,   -59,   -59,     7,   -59,   -59,    50,    79,
      36,    83,   -59,   -59,     8,   -59,    -5,   -59,   115,   -59,
     -59,    84,   -59,   -59,   -59,     8,    -3,   -59,    60,    60,
     -59,   -59,   -59,   -59,    60,   -59,    60,    60,   -59,    -5,
     -59,   -59,   -59,   -59,    49,   -24,   -27,    22,   111,   122,
     -59,   -59,    92,   -59,   102,    55,    60,   -59,   -59,   -59,
     -59,   -59,    64,   103,   104,   113,   112,   -59,   -59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,   -59,   -59,    29,   -59,   -59,   -59,    14,    14,
     -59,   -59,   -59,   -59,    49,    49,   -24,   -24,   -24,   -24,
     -27,   -27,    22,   111,   -59,    60,   139,   -59,   -59,    14,
     -59
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,    16,     8,     9,     0,     0,     0,     3,    10,    12,
       0,    13,     0,    14,     0,     0,    19,     1,     0,    18,
      11,     0,     0,    17,    25,     0,    15,    26,     0,     0,
       0,     0,    28,    34,     0,    31,     0,    33,     0,    29,
      32,     0,    43,    42,    21,     0,     0,    22,     0,     0,
       4,     5,     6,     7,     0,    38,     0,     0,    44,    52,
      51,    46,    55,    56,    60,    63,    68,    71,    73,    75,
      78,    76,     0,    36,     0,     0,     0,    27,    30,    35,
      24,    20,     0,     0,     0,     0,    52,    53,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    50,     0,    47,    77,    23,     0,     0,
      45,    57,    58,    59,    62,    61,    67,    66,    64,    65,
      69,    70,    72,    74,    49,     0,    39,    41,    48,     0,
      40
  };

  const short int
  Parser::yypgoto_[] =
  {
     -59,   -59,   -59,   -12,   -59,   147,   -10,     0,   -59,   -59,
     149,   -59,    77,   -59,   -59,   137,   -59,   123,   -58,   -59,
     -59,   -59,   -19,   -59,    30,   -15,    51,     4,    62,    59,
     -59,    87,   -17,   -40
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     5,    58,     6,     7,     8,     9,    86,    11,    12,
      16,    46,    47,    13,    14,    37,    38,    39,    40,    41,
      60,   104,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72
  };

  const unsigned char
  Parser::yytable_[] =
  {
      10,    94,    95,    42,    15,    43,    18,    10,    83,    84,
      34,     1,    35,    45,    85,     2,     3,     1,    17,    42,
      92,    43,    36,    96,    97,    93,    34,    28,    35,    29,
      59,    30,    31,    75,    74,   105,    81,    82,    36,     1,
      50,    51,    52,    53,    21,    80,    44,    76,    59,    59,
     126,   127,    98,    99,    59,    22,    22,    33,     1,    50,
      51,    52,    53,     1,    50,    51,    52,    53,   124,   125,
      45,   130,     2,     3,    54,    59,    59,   114,   115,    55,
      56,    57,    26,    25,    25,   128,    87,    88,    48,    42,
      42,    43,    43,    54,   103,    89,    90,    91,    54,    56,
      57,     1,   120,   121,    56,    57,     2,     3,    36,    36,
      42,    28,    43,    29,    27,    30,    31,    49,     1,   111,
     112,   113,   100,     2,     3,    59,    73,    79,    28,    36,
      29,     1,    30,    31,   101,   102,     2,     3,    26,    22,
      32,    33,   108,   109,     4,   116,   117,   118,   119,    23,
      75,    24,   110,   129,    20,    19,    22,    77,    33,   107,
     123,    78,   122,   106
  };

  const unsigned char
  Parser::yycheck_[] =
  {
       0,    28,    29,    22,     4,    22,     6,     7,    48,    49,
      22,     3,    22,    25,    54,     8,     9,     3,     0,    38,
      44,    38,    22,    50,    51,    49,    38,    13,    38,    15,
      30,    17,    18,    38,    34,    75,    39,    40,    38,     3,
       4,     5,     6,     7,    38,    45,    39,    52,    48,    49,
     108,   109,    30,    31,    54,    41,    41,    43,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    39,    40,
      82,   129,     8,     9,    38,    75,    76,    92,    93,    43,
      44,    45,    36,    38,    38,   125,    56,    57,    38,   108,
     109,   108,   109,    38,    39,    46,    47,    48,    38,    44,
      45,     3,    98,    99,    44,    45,     8,     9,   108,   109,
     129,    13,   129,    15,    39,    17,    18,    38,     3,    89,
      90,    91,    11,     8,     9,   125,    43,    43,    13,   129,
      15,     3,    17,    18,    12,    43,     8,     9,    36,    41,
      42,    43,    39,    39,    16,    94,    95,    96,    97,    12,
      38,    14,    39,    14,     7,     6,    41,    42,    43,    82,
     101,    38,   100,    76
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     8,     9,    16,    54,    56,    57,    58,    59,
      60,    61,    62,    66,    67,    60,    63,     0,    60,    63,
      58,    38,    41,    68,    68,    38,    36,    39,    13,    15,
      17,    18,    42,    43,    56,    59,    60,    68,    69,    70,
      71,    72,    75,    85,    39,    56,    64,    65,    38,    38,
       4,     5,     6,     7,    38,    43,    44,    45,    55,    60,
      73,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    43,    60,    38,    52,    42,    70,    43,
      60,    39,    40,    86,    86,    86,    60,    77,    77,    46,
      47,    48,    44,    49,    28,    29,    50,    51,    30,    31,
      11,    12,    43,    39,    74,    86,    84,    65,    39,    39,
      39,    77,    77,    77,    78,    78,    79,    79,    79,    79,
      80,    80,    81,    82,    39,    40,    71,    71,    86,    14,
      71
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    53,    54,    54,    55,    55,    55,    55,    56,    56,
      57,    57,    58,    58,    58,    59,    60,    61,    62,    62,
      63,    63,    64,    64,    65,    66,    67,    68,    68,    69,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    73,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      79,    79,    79,    80,    80,    80,    80,    80,    81,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    86
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
  "FALSE", "BOOLEAN", "INT", "DECIMAL", "AND", "OR", "IF", "ELSE", "WHILE",
  "VOID", "RETURN", "BREAK", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MODULO", "ASSIGNMENT", "NOT", "LT", "GT", "GE", "LE", "EQ", "NE",
  "PARENTHESIS_OPEN", "PARENTHESIS_CLOSE", "BRACE_OPEN", "BRACE_CLOSE",
  "SEMICOLON", "COMMA", "'('", "')'", "','", "'{'", "'}'", "';'", "'-'",
  "'!'", "'*'", "'/'", "'%'", "'+'", "'<'", "'>'", "'='", "$accept",
  "start", "literal", "type", "globaldeclarations", "globaldeclaration",
  "variabledeclaration", "identifier", "functiondeclaration",
  "functionheader", "functiondeclarator", "formalparameterlist",
  "formalparameter", "mainfunctiondeclaration", "mainfunctiondeclarator",
  "block", "blockstatements", "blockstatement", "statement",
  "statementexpression", "primary", "argumentlist", "functioninvocation",
  "postfixexpression", "unaryexpression", "multiplicativeexpression",
  "additiveexpression", "relationalexpression", "equalityexpression",
  "conditionalandexpression", "conditionalorexpression",
  "assignmentexpression", "assignment", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    82,    82,    83,    86,    87,    88,    89,    91,    92,
      95,    96,   100,   101,   102,   106,   110,   114,   118,   119,
     123,   124,   128,   129,   133,   137,   141,   145,   146,   150,
     151,   155,   156,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   172,   173,   177,   178,   179,   183,   184,   188,
     189,   193,   194,   198,   199,   200,   204,   205,   206,   207,
     211,   212,   213,   217,   218,   219,   220,   221,   225,   226,
     227,   231,   232,   236,   237,   241,   242,   246,   250
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
       2,     2,     2,    45,     2,     2,     2,    48,     2,     2,
      38,    39,    46,    49,    40,    44,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      50,    52,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      35,    36,    37
    };
    const unsigned user_token_number_max_ = 292;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1271 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.cpp" // lalr1.cc:1163
#line 254 "/home/ugc/jackson.wiebe1/cpsc411/ms1/src/parser.ypp" // lalr1.cc:1164


void yy::Parser::error(const std::string& m)
{
        std::cerr << m << "\n";
        // okay
}
