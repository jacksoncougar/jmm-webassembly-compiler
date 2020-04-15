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

  void generate_code(ASTNodeBase *node) {
    switch (node->type) {

      // mmm token soup...

    case ASTNodeType::none:
      break;
    case ASTNodeType::start:
      destination << "(module\n";
      break;
    case ASTNodeType::literal:
      break;
    case ASTNodeType::type:
      break;
    case ASTNodeType::globaldeclarations:
      break;
    case ASTNodeType::globaldeclaration:
      break;
    case ASTNodeType::variabledeclaration:
      break;
    case ASTNodeType::identifier:
      break;
    case ASTNodeType::functiondeclaration:
      break;
    case ASTNodeType::functionheader:
      break;
    case ASTNodeType::functiondeclarator:
      break;
    case ASTNodeType::formalparameterlist:
      break;
    case ASTNodeType::formalparameter:
      break;
    case ASTNodeType::mainfunctiondeclaration:
      break;
    case ASTNodeType::mainfunctiondeclarator:
      break;
    case ASTNodeType::block:
      break;
    case ASTNodeType::blockstatements:
      break;
    case ASTNodeType::blockstatement:
      break;
    case ASTNodeType::infixoperator:
      break;
    case ASTNodeType::statement:
      break;
    case ASTNodeType::ifstatement:
      break;
    case ASTNodeType::whilestatement:
      break;
    case ASTNodeType::returnstatement:
      break;
    case ASTNodeType::breakstatement:
      break;
    case ASTNodeType::statementexpression:
      break;
    case ASTNodeType::primary:
      break;
    case ASTNodeType::argumentlist:
      break;
    case ASTNodeType::functioninvocation:
      break;
    case ASTNodeType::postfixexpression:
      break;
    case ASTNodeType::unaryexpression:
      break;
    case ASTNodeType::multiplicativeexpression:
      break;
    case ASTNodeType::additiveexpression:
      break;
    case ASTNodeType::relationalexpression:
      break;
    case ASTNodeType::equalityexpression:
      break;
    case ASTNodeType::conditionalandexpression:
      break;
    case ASTNodeType::conditionalorexpression:
      break;
    case ASTNodeType::assignmentexpression:
      break;
    case ASTNodeType::assignment:
      break;
    case ASTNodeType::expression:
      break;
    }
  }

  void generate_webasm_code(ASTNodeBase *root) {
    generate_line_comment("begins auto generated .wasm code");
    // todo generate code...
    // foreach node in the ast: print code...

    // todo import global decls for halt, getchar, and printc...
    // todo start with parameters
    post_order_apply(*root, [&](ASTNodeBase &node) { generate_code(&node); });

    generate_line_comment("finished auto generated .wasm code");
  }
};

#endif // SCANNER_CODE_GENERATOR_H
