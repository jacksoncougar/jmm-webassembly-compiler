#ifndef LEXER_H
#define LEXER_H

#ifndef YY_DECL

#define YY_DECL            \
    yy::Parser::token_type yy::Lexer::lex( \
        yy::Parser::semantic_type *yylval);
#endif

#include "tokens.h"
#include "parser.hpp"

#ifndef yyFlexLexerOnce
// apparently this fixes a specific problem with flex++
#include "FlexLexer.h"
#endif

namespace yy
{
class Lexer : public yyFlexLexer
{
public:
    /**
     * Returns the attributes associated with the token returned by a previous 
     * call to yylex()
     */
    TokenAttributes attributes()
    {
        return {lineno(), std::string(YYText(), YYLeng())};
    }

    virtual yy::Parser::token_type lex(
        yy::Parser::semantic_type *yylval);
};
} // namespace yy

#endif