
%{
/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */
#include <stdio.h>
#include <string>
#include <fstream>

#include "tokens.h"

int yylineno = 1;
int warningno = 0;

%}

%option noyywrap
 // enable built in line counting (flex)
%option yylineno c++ 

%x STRING
%x ESCAPE

LineTerminator          (\r\n|\n|\r)
Separator               [(){};,]
terminal                [[:space:]{Separator}]
Identifier              [_[:alpha:]][_[:alnum:]]*
Whitespace              ([ \t\f]|{LineTerminator})

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


%%
 // Keywords go at the top
"int" { return T_TYPE_INT; }
"boolean" { return T_TYPE_BOOLEAN; }

"if" { return T_KEYWORD_IF; }
"else" { return T_KEYWORD_ELSE; }
"while" { return T_KEYWORD_WHILE; }
"break" { return T_KEYWORD_BREAK; }
"return" { return T_KEYWORD_RETURN; }
"void" { return T_KEYWORD_VOID; }

["]  { BEGIN (STRING); yymore(); }
<STRING>{StringCharacter}*  { yymore(); }

 /* strings cannot span across lines */
<STRING>{LineTerminator}  { 
    error("String literal missing closing quotation at or near line ", 
    yylineno);
    return 0; 
}

 /* catch the case when we reach the end-of-file without closing a string */
<STRING><<EOF>> { 
    error("String literal missing closing quotation at or near line ", 
    yylineno);
    return 0; 
}
<STRING>["] { BEGIN (INITIAL); return T_LITERAL_STRING; }
<STRING>\\. { BEGIN (ESCAPE); yyless(1); /* ignore opening quotation */ }

 /* scan until the end-of-string to see if there are more unknown escapes, then 
  * die */
<ESCAPE>\\. {  error("unknown escape sequence in string: '", yytext, "' at line ", yylineno); }
<ESCAPE>["] { return 0; }
<ESCAPE>.   /* do nothing */


"+" { return T_OP_PLUS; }
"-" { return T_OP_MINUS; }
"*" { return T_OP_MULTIPLY; }
"/" { return T_OP_DIVIDE; }
"%" { return T_OP_MODULO; }
"=" { return T_OP_ASSIGNMENT; }
"!" { return T_OP_NOT; }
"<" { return T_OP_LT; }
">" { return T_OP_GT; }
">=" { return T_OP_GE; }
"<=" { return T_OP_LE; }
"==" { return T_OP_EQ; }
"!=" { return T_OP_NE; }
"&&" { return T_OP_AND; }
"||" { return T_OP_OR; }

"("     { return T_PARENTHESIS_OPEN; }
")"     { return T_PARENTHESIS_CLOSE; }
"{"     { return T_BRACE_OPEN; }
"}"     { return T_BRACE_CLOSE; }
";"     { return T_SEMICOLON; }
","     { return T_COMMA; }

[/][/].*             /* do nothing */
{BooleanLiteral}    { return T_LITERAL_BOOLEAN; }
{OctalLikeNumeral}  { warning("treating octal-like number as decimal numeral."); return T_LITERAL_DECIMAL;}
{DecimalNumeral}    { return T_LITERAL_DECIMAL; }
{Identifier}        { return T_ID; }
{Whitespace}        /* do nothing */

 /* catch-all here at the bottom; count up to 10 warnings then error and stop. */
.                   { 
                        if(warningno++ < 10)  {
                            warning("ignoring unknown token '", yytext,"' at line ", yylineno);
                        }
                        else { 
                            error("too many warnings at or near line ", yylineno); return 0;
                        }  
                    }

<<EOF>> { return 0; }
%%

