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

#endif //TOKEN_H