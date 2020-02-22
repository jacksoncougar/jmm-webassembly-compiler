/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#ifndef TOKENS_H
#define TOKENS_H

#include <map>
#include <iostream>
#include <unistd.h>

// Detect device output mode and colourize labels if writing to a terminal
const bool colourize = isatty(1) && isatty(2);

const std::string warning_label = colourize ? "\x1B[01;31mWarning\x1B[0m: " : "Warning: ";
const std::string error_label = colourize ? "\x1B[01;31mError\x1B[0m: " : "Error: ";

template <typename... Args>
void warning(Args... args)
{
    std::cerr << warning_label;
    (std::cerr << ... << args); // c++ fold
    std::cerr << std::endl;
}

template <typename... Args>
void error(Args... args)
{
    std::cerr << error_label;
    (std::cerr << ... << args); // c++ fold
    std::cerr << std::endl;
}

struct TokenAttributes
{
    int lineno;
    std::string lexeme;
};

std::ostream &operator<<(std::ostream &out, const TokenAttributes &attributes);

enum Token
{
    T_TYPE_INT = 1,
    T_TYPE_BOOLEAN,
    T_ID,
    T_LITERAL_STRING,
    T_LITERAL_BOOLEAN,
    T_LITERAL_DECIMAL,
    T_KEYWORD_TRUE,
    T_KEYWORD_FALSE,
    T_KEYWORD_BOOLEAN,
    T_KEYWORD_INT,
    T_KEYWORD_VOID,
    T_KEYWORD_IF,
    T_KEYWORD_ELSE,
    T_KEYWORD_WHILE,
    T_KEYWORD_BREAK,
    T_KEYWORD_RETURN,
    T_OP_PLUS,
    T_OP_MINUS,
    T_OP_MULTIPLY,
    T_OP_DIVIDE,
    T_OP_MODULO,
    T_OP_ASSIGNMENT,
    T_OP_GT,
    T_OP_LT,
    T_OP_LE,
    T_OP_GE,
    T_OP_EQ,
    T_OP_NE,
    T_OP_NOT,
    T_OP_AND,
    T_OP_OR,
    T_PARENTHESIS_OPEN,
    T_PARENTHESIS_CLOSE,
    T_BRACE_OPEN,
    T_BRACE_CLOSE,
    T_SEMICOLON,
    T_COMMA,
    T_UNKNOWN_TOKEN
};

std::string tokenToString(int token);

#endif //TOKEN_H