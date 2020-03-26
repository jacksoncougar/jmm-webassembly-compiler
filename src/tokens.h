/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#ifndef TOKENS_H
#define TOKENS_H

#include <map>
#include <iostream>


const std::string warning_label = "Warning: ";
const std::string error_label = "Error: ";

template<typename... Args>
void warning(Args... args) {
    std::cerr << warning_label;
    (std::cerr << ... << args); // c++ fold
    std::cerr << std::endl;
}

template<typename... Args>
void error(Args... args) {
    std::cerr << error_label;
    (std::cerr << ... << args); // c++ fold
    std::cerr << std::endl;
}

struct TokenAttributes {
    int lineno;
    std::string lexeme;
};

std::ostream &operator<<(std::ostream &out, const TokenAttributes &attributes);

#endif //TOKEN_H