//
// Created by Jackson Cougar Wiebe on 4/14/2020.
//

#ifndef SCANNER_SEMANTIC_CHECKER_H
#define SCANNER_SEMANTIC_CHECKER_H

#include "ast.hpp"

using namespace std::literals::string_literals;

class SemanticChecker {
public:
  void process(ASTNodeBase *root);
};

#endif // SCANNER_SEMANTIC_CHECKER_H
