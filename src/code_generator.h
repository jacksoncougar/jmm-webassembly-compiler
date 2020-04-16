//
// Created by Jackson Cougar Wiebe on 4/14/2020.
//

#ifndef SCANNER_CODE_GENERATOR_H
#define SCANNER_CODE_GENERATOR_H

#include "ast.hpp"
#include "template.hpp"
#include <ostream>
#include <string>
#include <utility>

using namespace std::literals::string_literals;

struct CodeGenerator
{
  struct Wrapper
  {
    Wrapper(std::ostream &out, CodeGenerator &parent)
        : out(out), parent(parent) {}

    std::ostream &out;
    CodeGenerator &parent;

    template<class T>
    Wrapper &operator<<(T &&x)
    {
      out << std::forward<T>(x);
      parent.is_newline = false;
      return *this;
    }
  };

  Wrapper destination;
  int current_indentation_level = 0;
  bool is_newline = true;

  struct Indent
  {
    CodeGenerator &parent;

    Indent(CodeGenerator &parent) : parent(parent) {}

    friend std::ostream &operator<<(std::ostream &out, const Indent &i)
    {
      if (i.parent.is_newline)
      {
        out << std::string(i.parent.current_indentation_level * 2, ' ');
      }
      return out;
    }
  };// stream manipulation


  void open_scope()
  {
    destination << Indent(*this) << "(";
    current_indentation_level++;
  }

  void close_scope()
  {
    current_indentation_level--;
    destination << Indent(*this) << ")";
  }

  public:
  CodeGenerator(std::ostream &destination) : destination(destination, *this) {}

  // todo lines should be abstracted from generation here...

  void generate_comment_line(const char *comment)
  {
    destination << Indent(*this) << ";;" << comment;
    newline();
  }
  void generate_comment_line(std::string comment)
  {
    destination << Indent(*this) << ";;" << comment;
    newline();
  }
  void generate_comment(std::string comment)
  {
    destination << Indent(*this) << ";;" << comment;
  }
  void generate_code_line(const char *code)
  {
    destination << Indent(*this) << code;
    newline();
  }
  void generate_code_line(std::string code)
  {
    destination << Indent(*this) << code;
    newline();
  }
  void generate_code_line(std::string template_string,
                          std::initializer_list<std::string> args)
  {
    destination << Indent(*this) << Template(std::move(template_string), args);
    newline();
  }
  void generate_code(const char *code) { destination << Indent(*this) << code; }
  void generate_code(std::string code) { destination << Indent(*this) << code; }
  void generate_code(std::string template_string,
                     std::initializer_list<std::string> args)
  {
    destination << Indent(*this) << Template(std::move(template_string), args);
  }

  /**
   * Cleans up any lingering indentation.
   * @param node
   */
  void post_process(ASTNodeBase *node)
  {
    switch (node->type)
    {
      case ASTNodeType::start:
        close_scope();
        newline();
        break;
      case ASTNodeType::functiondeclaration:
        close_scope();
        newline();
        break;
      case ASTNodeType::formalparameter:
        break;
      case ASTNodeType::variabledeclaration:
        break;
      case ASTNodeType::mainfunctiondeclaration:
        close_scope();
        newline();
        break;
      case ASTNodeType::ifstatement:
        close_scope();
        newline();
        break;
    }
  }

  void newline()
  {
    destination << '\n';
    is_newline = true;
  }

  std::string asm_identifier()
  {
    static int identifier = 0;
    return "$" + std::to_string(identifier++);
  }

  bool generate_locals(ASTNodeBase &node)
  {
    switch (node.type)
    {
      case ASTNodeType::formalparameter:
      {
        open_scope();
        auto id = asm_identifier();
        node.get_attribute<SymbolTableEntry *>("symbol")
                ->data["asm_identifier"] = id;
        generate_code("param {$C0} {i32}", {id, asm_type_of(node)});
        close_scope();
        generate_comment_line(node.get_attribute<std::string>("name").c_str());
      }
      break;
      case ASTNodeType::variabledeclaration:
      {
        open_scope();
        auto id = asm_identifier();
        node.get_attribute<SymbolTableEntry *>("symbol")
                ->data["asm_identifier"] = id;
        generate_code("local {$C0} {i32}", {id, asm_type_of(node)});
        close_scope();
        generate_comment_line(node.get_attribute<std::string>("name").c_str());
      }
    }
    return true;
  }

  bool generate_code(ASTNodeBase *node)
  {
    switch (node->type)
    {
      case ASTNodeType::start:
      {
        open_scope();
        generate_code_line("module");
      }
      break;

      case ASTNodeType::functiondeclaration:
      {

        auto id = node->get_attribute<SymbolTableEntry *>("symbol")->identifier;

        open_scope();
        generate_code_line("func ${id}", {id});
        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_locals(n); });
      }
      break;
      case ASTNodeType::formalparameter:
        break;
      case ASTNodeType::variabledeclaration:
        break;
      case ASTNodeType::mainfunctiondeclaration:
      {
        open_scope();
        generate_code("start $main");
        close_scope();

        newline();

        open_scope();
        generate_code_line("func $main");
        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_locals(n); });
      }
      //return false;// don't descend into children.
      break;
      case ASTNodeType::functioninvocation:
        generate_expression_code(node->children()[1].get());
        generate_code_line("call ${function}",
                           {node->get_attribute<SymbolTableEntry *>("symbol")->identifier});
        break;
      case ASTNodeType::infixoperator:
      {
        // lhs = result of rhs...
        auto lhs = node->children()[0].get();
        auto rhs = node->children()[1].get();
        generate_expression_code(rhs);

        // assign that result to the lhs identifier...
        generate_code_line("local.set {lhs}",
                           {lhs->get_attribute<SymbolTableEntry *>("symbol")
                                    ->data.at("asm_identifier")});

        return false;// don't descend into children.
      }
      case ASTNodeType::ifstatement:
        generate_comment_line("if condition");
        generate_expression_code(node->children()[0].get());
        open_scope();
        generate_code_line("if");
        open_scope();
        generate_code_line("then");
        pre_post_order_apply(
                *node->children()[1],
                [&](ASTNodeBase &node) { return generate_code(&node); },
                [&](ASTNodeBase &node) { post_process(&node); });
        close_scope();
        newline();
        if (node->children().size() >= 3)// if-else node
        {
          open_scope();
          generate_code_line("else");
          pre_post_order_apply(
                  *node->children()[2],
                  [&](ASTNodeBase &node) { return generate_code(&node); },
                  [&](ASTNodeBase &node) { post_process(&node); });
          close_scope();
          newline();
        }
        return false;// don't descend into children.
      default:
        // do some sanity checking while debugging...
        error("Unhandled case '" + node->name + "' in '" + __FUNCTION__ + "'");
    }

    return true;// descend into children.
  }

  std::map<std::string, std::string> asm_type_name = {
          {"int", "i32"},
          {"boolean", "i32"}};

  std::map<std::string, std::string> asm_math_operations = {
          {"+", "add"},
          {"-", "sub"},
          {"*", "mul"},
          {"/", "div_u"},
          {"%", "rem_u"}};

  std::map<std::string, std::string> asm_conditional_operations = {
          {"&&", "and"},
          {"||", "or"},
          {"<", "lt_u"},
          {"<=", "le_u"},
          {">", "gt_u"},
          {">=", "ge_u"},
          {"==", "eq"},
          {"!=", "ne"},
  };

  std::string asm_type_of(ASTNodeBase &node)
  {
    return asm_type_name.at(node.get_attribute<std::string>("type"));
  }

  std::string get_identifier_of(ASTNodeBase &node)
  {
    return node.get_attribute<SymbolTableEntry *>("symbol")
            ->data["asm_identifier"];
  }

  void generate_expression_code(ASTNodeBase *expression)
  {
    // walk the expression tree from the bottom up building up asm
    // instructions
    pre_post_order_apply(
            *expression, [&, function_name = std::string(__FUNCTION__)](ASTNodeBase &expression) {
              if (expression.name == "!")// integer constant
              {
                // take the current value on the stack and invert it
                generate_code("{op} {value}", {"i32.const", "0"});
                generate_comment_line("begin negation");
              }
              return true; },
            [&, function_name = std::string(__FUNCTION__)](
                    ASTNodeBase &expression) {
              if (expression.name == "int")// integer constant
              {
                generate_code_line("{op} {value}",
                                   {"i32.const ", expression.get_attribute<std::string>("value")});
              }
              else if (expression.name == "true" || expression.name == "false")// integer constant
              {
                auto value = expression.get_attribute<std::string>("value") == "true"
                                     ? "1"
                                     : "0";
                generate_code("{op} {value}",
                              {"i32.const", value});
                generate_comment_line("boolean " + expression.name);
              }
              else if (expression.name == "int")// integer constant
              {
                generate_code_line("{op} {value}",
                                   {"i32.const", expression.get_attribute<std::string>("value")});
              }
              else if (expression.name == "id")// integer constant
              {
                generate_code_line("{op} {value}",
                                   {"local.get", get_identifier_of(expression)});
              }
              else if (expression.name == "!")// integer constant
              {
                // take the current value on the stack and invert it
                generate_code("{op}", {"i32.sub"});
                generate_comment_line("end negation");
              }
              else if (asm_math_operations.count(expression.name))// maths
              {
                auto type_of_result =
                        asm_type_name.at(expression.get_attribute<std::string>("type"));
                generate_code_line("{type}.{op}", {type_of_result, asm_math_operations[expression.name]});
                // result is now on the stack.,
              }
              else if (asm_conditional_operations.count(expression.name))// maths
              {
                auto type_of_result =
                        asm_type_name.at(expression.get_attribute<std::string>("type"));
                generate_code_line("{type}.{op}", {type_of_result, asm_conditional_operations[expression.name]});
                // result is now on the stack.,
              }
              else
              {
                // do some sanity checking while debugging...
                error("Unhandled case '" + expression.name + "' in '" +
                      function_name + "'");
              }
            });
  }

  void generate_webasm_code(ASTNodeBase *root)
  {

    warning(root);

    generate_comment_line("begins auto generated .wasm code");
    // todo generate code...
    // foreach node in the ast: print code...

    // todo import global decls for halt, getchar, and printc...
    // todo start with parameters
    pre_post_order_apply(
            *root,

            [&](ASTNodeBase &node) { return generate_code(&node); },

            [&](ASTNodeBase &node) { post_process(&node); });

    generate_comment_line("finished auto generated .wasm code");
  }
};

#endif// SCANNER_CODE_GENERATOR_H
