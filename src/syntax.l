
%{
/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

#include "lexer.h"
#include "tokens.h"
#include "parser.hpp"

using namespace std::string_literals;

int yylineno = 1;
int warningno = 0;

typedef yy::Parser::token token;
typedef yy::Parser::token_type token_type;

#define yyterminate() return token::END
#undef YY_INTERACTIVE

%}
%option nounistd
%option noyywrap
 // enable built in line counting (flex)
%option yylineno c++ 

%x STRING
%x ESCAPE

LineTerminator          (\r\n|\n|\r)
Separator               [(){};,]
terminal                [[:space:]{Separator}]
Identifier              [_[:alpha:]][_[:alnum:]]*

 /* Numbers shouldn't match the Octal in Java so I'm choosing to follow the
  * Java DecimalNumeral exactly--this will match octals as two consecutive 
  * numbers which I will not issue a warning or error for in the scanner.
  */

DecimalNumeral          (0|{NonZeroDigit}{Digits}?|{NonZeroDigit}{Underscores}{Digits})
Digits                  ({Digit}|{Digit}{DigitsAndUnderscores}?{Digit})
Digit                   [0-9]
NonZeroDigit            [1-9]
DigitsAndUnderscores    ([0-9]|[_0-9]+[0-9])  
Underscores             [_]+
NumberLiteral           {DecimalNumeral}

 /* 'like' an octal because I don't care about the digit range of an octal */
OctalLikeNumeral        (0{Digits}|0{Underscores}{Digits}) 

BooleanLiteral          ("true"|"false")
StringLiteral           \"{StringCharacter}*\"

EscapeSequence          (\\b|\\t|\\n|\\f|\\r|\\\"|\\\\|\\')
StringCharacter         ([^\r\n"\\]|{EscapeSequence})

%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}
%%
%{
yylloc->step();
%}
 // Keywords go at the top
"int" { yylval->a = new ASTNode(ASTNodeType::type, yytext); return token::INT; }
"boolean" { yylval->a = new ASTNode(ASTNodeType::type, yytext); return token::BOOLEAN; }

"if" { yylval->a = new ASTNode(ASTNodeType::statement, "if"); return token::IF; }
"else" { yylval->a = new ASTNode(ASTNodeType::statement,"else"); return token::ELSE; }
"while" { yylval->a = new ASTNode(ASTNodeType::statement,"while"); return token::WHILE; }
"break" { yylval->a = new ASTNode(ASTNodeType::statement,"break"); return token::BREAK; }
"return" { yylval->a = new ASTNode(ASTNodeType::statement,"return"); return token::RETURN; }
"void" { yylval->a = new ASTNode(ASTNodeType::statement,"void"); return token::VOID; }

["]  { BEGIN STRING; yymore(); }
<STRING>{StringCharacter}*  { yymore(); }

 /* strings cannot span across lines */
<STRING>{LineTerminator}  { 
    error("String literal missing closing quotation at or near line ", 
    yylineno);
    return token::END;
}

 /* catch the case when we reach the end-of-file without closing a string */
<STRING><<EOF>> { 
    error("String literal missing closing quotation at or near line ", 
    yylineno);
    return token::END;
}
<STRING>["] { BEGIN INITIAL;     
    yylval->a = new ASTNode(
        ASTNodeType::literal,
        "string"
    );

    yylval->a->set_attribute("value", std::string(yytext));
    yylval->a->set_attribute("type", "string"s);
    return token::STRING_LITERAL; }
<STRING>\\. { BEGIN ESCAPE; yyless(1); /* ignore opening quotation */ }

 /* scan until the end-of-string to see if there are more unknown escapes, then 
  * die */
<ESCAPE>\\. {  error("unknown escape sequence in string: '", yytext, "' at line ", yylineno); return token::END; }
<ESCAPE>["] { return token::END; }
<ESCAPE>.   /* do nothing */


"+" { return token::PLUS; }
"-" { return token::MINUS; }
"*" { return token::MULTIPLY; }
"/" { return token::DIVIDE; }
"%" { return token::MODULO; }

"=" { return token::ASSIGNMENT; }

"!" { return token::NOT; }
"<" { return token::LT; }
">" { return token::GT; }
">=" { return token::GE; }
"<=" { return token::LE; }
"==" { return token::EQ; }
"!=" { return token::NE; }
"&&" { return token::AND; }
"||" { return token::OR; }

"("     { return token::PARENTHESIS_OPEN; }
")"     { return token::PARENTHESIS_CLOSE; }
"{"     { return token::BRACE_OPEN; }
"}"     { return token::BRACE_CLOSE; }
";"     { return token::SEMICOLON; }
","     { return token::COMMA; }

[/][/].*             /* do nothing */

true    {  
    yylval->a = new ASTNode(
        ASTNodeType::literal,
        "true"
        );

    yylval->a->set_attribute("value", std::string(yytext));
    yylval->a->set_attribute("type", "boolean"s);
    return token::TRUE; }

false    {  
    yylval->a = new ASTNode(
        ASTNodeType::literal,
        "false"
        );
    yylval->a->set_attribute("value", std::string(yytext));
    yylval->a->set_attribute("type", "boolean"s);
    return token::FALSE; }

{OctalLikeNumeral}  { 
    warning("treating octal-like number as decimal numeral.");
    yylval->a = new ASTNode(
        ASTNodeType::literal,
        "int"
    );
    yylval->a->set_attribute("value", std::string(yytext));
    yylval->a->set_attribute("type", "int"s);
    return token::NUMBER; }

{DecimalNumeral}    { 
    yylval->a = new ASTNode(
        ASTNodeType::literal,
        "int"
    );
    yylval->a->set_attribute("value", std::string(yytext));
    yylval->a->set_attribute("type", "int"s);
    return token::NUMBER; }

{Identifier}        { 
    yylval->a = new ASTNode(
        ASTNodeType::identifier,
        "id"
        );
    yylval->a->set_attribute("value", std::string(yytext));
    return token::ID; }

[ \t\f]+      {
    yylloc->step();
}

{LineTerminator}+ {
    yylloc->lines(yyleng); yylloc->step();
}

 /* catch-all here at the bottom; count up to 10 warnings then error and stop. */
.                   { 
        if(warningno++ < 10)  {
            warning("ignoring unknown token '", (int)*yytext,"' at ", *yylloc);
        }
        else { 
            error("too many warnings at  ", *yylloc); 
            return token::END;
        }  
    }

<<EOF>>             { return token::END; }
%%

#ifdef yylex
#undef yylex
#endif
int yyFlexLexer::yylex() { return 0; }