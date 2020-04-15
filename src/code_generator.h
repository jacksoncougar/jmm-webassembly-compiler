//
// Created by Jackson Cougar Wiebe on 4/14/2020.
//

#ifndef SCANNER_CODE_GENERATOR_H
#define SCANNER_CODE_GENERATOR_H

#include "ast.hpp"
#include <ostream>

struct CodeGenerator {
  struct Wrapper {
    Wrapper(std::ostream &out, CodeGenerator &parent)
        : out(out), parent(parent) {}

    std::ostream &out;
    CodeGenerator &parent;

    template <class T> Wrapper &operator<<(T &&x) {
      out << std::forward<T>(x);
      parent.is_newline = false;
      return *this;
    }
  };

  Wrapper destination;
  int current_indentation_level = 0;
  bool is_newline = true;

  struct Indent {
    CodeGenerator &parent;

    Indent(CodeGenerator &parent) : parent(parent) {}

    friend std::ostream &operator<<(std::ostream &out, const Indent &i) {
      if (i.parent.is_newline) {
        out << std::string(i.parent.current_indentation_level * 2, ' ');
      }
      return out;
    }
  }; // stream manipulation

  struct Scope {
    CodeGenerator &parent;

    explicit Scope(CodeGenerator &generator) : parent(generator) {
      parent.destination << Indent(parent) << "(";
      parent.current_indentation_level++;
    }

    ~Scope() {
      parent.current_indentation_level--;
      parent.destination << Indent(parent) << ")";
    }
  }; // raii for indentation

  std::map<ASTNodeBase *, std::unique_ptr<Scope>> scopes;

public:
  CodeGenerator(std::ostream &destination) : destination(destination, *this) {}

  void generate_line_comment(const char *comment) {
    destination << Indent(*this) << ";;" << comment;
    newline();
  }

  /**
   * Cleans up any lingering indentation.
   * @param node
   */
  void post_process(ASTNodeBase *node) { scopes.erase(node); }

  void newline() {
    destination << '\n';
    is_newline = true;
  }

  void generate_code(ASTNodeBase *node) {
    switch (node->type) {

      // mmm token soup...

    case ASTNodeType::none:
      break;
    case ASTNodeType::start: {
      scopes.emplace(node, std::make_unique<Scope>(*this));
      destination << "module";
    } break;
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
      newline();
      generate_line_comment(node->get_attribute<std::string>("name").c_str());
      scopes.emplace(node, std::make_unique<Scope>(*this));
      destination << "func L0$";
      break;
    case ASTNodeType::functionheader:
      break;
    case ASTNodeType::functiondeclarator:
      break;
    case ASTNodeType::formalparameterlist:
      break;
    case ASTNodeType::formalparameter:
      newline();
      scopes.emplace(node, std::make_unique<Scope>(*this));
      destination << "param $C0 i32";
      break;
    case ASTNodeType::mainfunctiondeclaration:
      newline();
      scopes.emplace(node, std::make_unique<Scope>(*this));
      if (node->has_attribute("main_decl")) {
        destination << "start $L0";
      }
      break;
    case ASTNodeType::mainfunctiondeclarator:
      break;
    case ASTNodeType::block:
      newline();
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

    destination << *root;

    generate_line_comment("begins auto generated .wasm code");
    // todo generate code...
    // foreach node in the ast: print code...

    // todo import global decls for halt, getchar, and printc...
    // todo start with parameters
    pre_post_order_apply(
        *root,

        [&](ASTNodeBase &node) {
          generate_code(&node);
          return true;
        },

        [&](ASTNodeBase &node) { post_process(&node); });

    generate_line_comment("finished auto generated .wasm code");
  }
};

#endif // SCANNER_CODE_GENERATOR_H
