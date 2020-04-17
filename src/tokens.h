/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#ifndef TOKENS_H
#define TOKENS_H

#include <iostream>
#include <map>


const std::string note_label = "Note: ";
const std::string warning_label = "Warning: ";
const std::string error_label = "Error: ";

#ifdef TAKE_NOTES
template<typename... Args>
void note(Args... args)
{
  std::cerr << note_label;
  (std::cerr << ... << args);// c++ fold
  std::cerr << '\n';
}
#else
template<typename... Args>
void note(Args... args)
{
}
#endif

template<typename... Args>
void warning(Args... args)
{
  std::cerr << warning_label;
  (std::cerr << ... << args);// c++ fold
  std::cerr << '\n';
}

template<typename... Args>
void error(Args... args)
{
  std::cerr << error_label;
    (std::cerr << ... << args); // c++ fold
    std::cerr << '\n';
}

struct TokenAttributes {
    int lineno;
    std::string lexeme;
};

std::ostream &operator<<(std::ostream &out, const TokenAttributes &attributes);

#endif //TOKEN_H