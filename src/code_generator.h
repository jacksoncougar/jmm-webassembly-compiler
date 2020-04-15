//
// Created by Jackson Cougar Wiebe on 4/14/2020.
//

#ifndef SCANNER_CODE_GENERATOR_H
#define SCANNER_CODE_GENERATOR_H

#include "ast.hpp"
#include <ostream>

class CodeGenerator {
  std::ostream &destination;

public:
  CodeGenerator(std::ostream &destination) : destination(destination) {}

  void generate_line_comment(const char *comment) {
    destination << ";;" << comment << '\n';
  }

  void generate_webasm_code(ASTNodeBase *root) {
    generate_line_comment("begins auto generated .wasm code");
    // todo generate code...
    generate_line_comment("finished auto generated .wasm code");
  }
};

#endif // SCANNER_CODE_GENERATOR_H
