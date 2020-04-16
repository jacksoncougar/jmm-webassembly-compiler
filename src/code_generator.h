//
// Created by Jackson Cougar Wiebe on 4/14/2020.
//

#ifndef SCANNER_CODE_GENERATOR_H
#define SCANNER_CODE_GENERATOR_H

#include "ast.hpp"
#include "driver.h"
#include "semantic_checker.h"
#include "template.hpp"
#include <ostream>
#include <sstream>
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
      auto start_position = out.tellp();
      out << std::forward<T>(x);
      auto end_position = out.tellp();
      parent.is_newline = false;
      parent.current_column_position += end_position - start_position;
      return *this;
    }
  };

  Wrapper destination;
  int current_indentation_level = 0;
  bool is_newline = true;
  bool runtime_library = false;
  int current_column_position = 0;
  int current_data_offset = 0;

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

  enum FormatOptions
  {
    none = 0,
    endline = 1,
    align
  };

  void close_scope(FormatOptions options = none)
  {
    current_indentation_level--;
    destination << Indent(*this) << ")";
    if (options & endline) newline();
  }

  public:
  CodeGenerator(std::ostream &destination) : destination(destination, *this) {}


  void generate_comment(std::string_view format,
                        std::initializer_list<std::string_view> args = {},
                        FormatOptions options = (FormatOptions)(FormatOptions::endline | FormatOptions::align))
  {
    destination << Indent(*this) << ((options & align) ? std::string(std::max(0, 40 - current_column_position), ' ') : "")
                << ";;" << Template(format, args);
    if (options & endline) newline();
  }

  void generate_code(std::string_view format,
                     std::initializer_list<std::string_view> args = {},
                     FormatOptions options = FormatOptions::none)
  {
    destination << Indent(*this) << Template(format, args);
    if (options & endline) newline();
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

  std::string asm_label()
  {
    static int label = 0;
    return "$L" + std::to_string(label++);
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
        generate_comment(node.get_attribute<std::string>("name").c_str());
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
        generate_comment(node.get_attribute<std::string>("name").c_str());
      }
    }
    return true;
  }

  void generate_runtime_system()
  {
    if (runtime_library) return;
    static auto prints_asm_source = R"(
(func $prints (; 1 ;) (param $0 i32) (param $1 i32)
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (get_local $1)
     (i32.const 1)
    )
   )
   (loop $label$1
     (call $putchar
      (i32.load8_s
       (get_local $0)
      )
    )
    (set_local $0
     (i32.add
      (get_local $0)
      (i32.const 1)
     )
    )
    (br_if $label$1
     (tee_local $1
      (i32.add
       (get_local $1)
       (i32.const -1)
      )
     )
    )
   )
  )
 ))";

    static auto printi_source = R"(void printi(int i) {
  int remainder;
  int quotient;

  remainder = 0;
  quotient = i;

  while(quotient > 0) {
      remainder = quotient % 10;
      quotient = quotient / 10;
      putchar(48 + remainder);
  }
})";

    static auto printb_source = R"(void printb(int b) {
  if(b) prints("true");
  else prints("false");
})";

    generate_code(prints_asm_source, {}, endline);

    runtime_library = true;
    auto compile = [&](std::string jmm_source_code) -> std::string {
      yy::Driver driver;
      driver.streamname = "runtime_library";
      std::stringstream ss(jmm_source_code);
      driver.parse_stream(ss);

      SemanticChecker sc;
      sc.runtime_library = true;
      sc.process(driver.root.get());

      std::stringstream out;
      generate_strings(*driver.root);
      generate_webasm_code(driver.root->children()[0]->children()[0].get());

      return out.str();
    };

    generate_code(compile(printi_source), {}, endline);
    generate_code(compile(printb_source), {}, endline);
    runtime_library = false;
  }

  bool generate_code(ASTNodeBase *node)
  {
    switch (node->type)
    {
      case ASTNodeType::start:
      {
        open_scope();
        generate_code("module", {}, endline);

        generate_externs();
        generate_code("(memory 0)", {}, endline);
        generate_runtime_system();
        generate_strings(*node);
      }
      break;

      case ASTNodeType::functiondeclaration:
      {

        auto id = node->get_attribute<SymbolTableEntry *>("symbol")->identifier;

        open_scope();
        generate_code("func ${id}", {id}, endline);

        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_locals(n); });
      }
      break;
      case ASTNodeType::formalparameter:
        return false;// don't descend into children.
        break;
      case ASTNodeType::variabledeclaration:
        return false;// don't descend into children.
        break;
      case ASTNodeType::mainfunctiondeclaration:
      {
        generate_code("(start $main)", {}, endline);
        open_scope();
        generate_code("func $main", {}, endline);

        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_locals(n); });
      }
      break;
      case ASTNodeType::functioninvocation:
        generate_expression_code(node->children()[1].get());
        generate_code("call ${function}",
                      {node->get_attribute<SymbolTableEntry *>("symbol")->identifier}, endline);
        return false;// don't descend into children;
      case ASTNodeType::infixoperator:
      {
        // lhs = result of rhs...
        auto lhs = node->children()[0].get();
        auto rhs = node->children()[1].get();
        generate_expression_code(rhs);

        // assign that result to the lhs identifier...
        generate_code("local.set {lhs}",
                      {lhs->get_attribute<SymbolTableEntry *>("symbol")
                               ->data.at("asm_identifier")},
                      endline);


        return false;// don't descend into children.
      }
      case ASTNodeType::ifstatement:
      {
        generate_comment("if condition");
        generate_expression_code(node->children()[0].get());
        open_scope();
        generate_code("if", {}, endline);

        open_scope();
        generate_code("then", {}, endline);

        pre_post_order_apply(
                *node->children()[1],
                [&](ASTNodeBase &node) { return generate_code(&node); },
                [&](ASTNodeBase &node) { post_process(&node); });
        close_scope(endline);

        if (node->children().size() >= 3)// if-else node
        {
          open_scope();
          generate_code("else", {}, endline);

          pre_post_order_apply(
                  *node->children()[2],
                  [&](ASTNodeBase &node) { return generate_code(&node); },
                  [&](ASTNodeBase &node) { post_process(&node); });
          close_scope(endline);
        }
        close_scope(endline);
        return false;// don't descend into children.
      }
      case ASTNodeType::whilestatement:
      {
        auto exit_label = asm_label();
        auto continue_label = asm_label();

        open_scope();
        generate_code("block {label}", {exit_label}, endline);

        open_scope();
        generate_code("loop {label}", {continue_label}, endline);

        generate_comment("loop condition", {}, endline);
        generate_expression_code(node->children()[0].get());
        generate_comment("loop test", {}, endline);
        generate_code("br_if {label}", {exit_label}, endline);
        generate_comment("loop body", {}, endline);
        generate_webasm_code(node->children()[1].get());
        generate_code("br {label}", {continue_label}, endline);

        close_scope(endline);
        close_scope(endline);
        return false;// don't descend into children.
      }
      default:
        // do some sanity checking while debugging...
        warning("Unhandled case '" + node->name + "' in '" + __FUNCTION__ + "'");
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

  struct StringTableEntry
  {
    int offset;
    int length;
  };
  std::map<std::string, StringTableEntry> string_table;

  std::string trim(std::string string)
  {
    // remove quotations marks.
    return string.substr(1, string.size() - 2);
  }

  void generate_prints()
  {
    //    // get the size of the string to print
    //    // walk through the string data and call putchar on each element on the string
    //    open_scope();
    //    generate_code("func $prints", {}, endline);
    //    generate_code("(param $address)", {}, endline);
    //    generate_code("(param $size)", {}, endline);
    //    generate_code("(local $iteration)", {}, endline);
    //    generate_code("local.get $size", {}, endline);// load the string size onto stack
    //    open_scope();
    //    generate_code("loop", {}, endline);// load the string size onto stack
    //    open_scope();
    //
    //    close_scope();
    //    generate_code("end", {}, endline);// load the string size onto stack
    //    close_scope();
    //    close_scope();
    //
  }

  void generate_externs()
  {
    generate_code(R"((import "host" "exit" (func $halt)))", {}, endline);
    generate_code(R"((import "host" "getchar" (func $getchar (result i32))))", {}, endline);
    generate_code(R"((import "host" "putchar" (func $putchar (param i32))))", {}, endline);
  }

  void generate_strings(ASTNodeBase &node)
  {
    auto insert_string_table_entry = [&](const std::string &string_literal) {
      auto [_, string_not_previously_defined] = string_table.emplace(
              string_literal,
              StringTableEntry{current_data_offset, (int) string_literal.size()});

      if (string_not_previously_defined)
      {
        generate_code("(data 0 (i32.const {offset}) \"{data}\")",
                      {std::to_string(current_data_offset), string_literal}, endline);
        current_data_offset += string_literal.size();
      }
    };

    insert_string_table_entry("true");
    insert_string_table_entry("false");

    pre_order_apply(node, [&](ASTNodeBase &node) {
      if (node.name == "string")
      {
        const std::string &string_literal = trim(node.get_attribute<std::string>("value"));
        insert_string_table_entry(string_literal);
      }
    });
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
                generate_comment("begin negation", {}, endline);
              }
              return true; },
            [&, function_name = std::string(__FUNCTION__)](
                    ASTNodeBase &expression) {
              if (expression.name == "int")// integer constant
              {
                generate_code("{op} {value}",
                              {"i32.const ", expression.get_attribute<std::string>("value")}, endline);
              }
              else if (expression.name == "true" || expression.name == "false")// integer constant
              {
                auto value = expression.get_attribute<std::string>("value") == "true"
                                     ? "1"
                                     : "0";
                generate_code("{op} {value}",
                              {"i32.const", value});
                generate_comment("boolean " + expression.name, {}, endline);
              }
              else if (expression.name == "int")// integer constant
              {
                generate_code("{op} {value}",
                              {"i32.const", expression.get_attribute<std::string>("value")}, endline);
              }
              else if (expression.name == "string")// integer constant
              {
                auto [offset, length] = string_table.at(trim(expression.get_attribute<std::string>("value")));
                generate_code("{op} {value}",
                              {"i32.const", std::to_string(offset)}, endline);
                generate_code("{op} {value}",
                              {"i32.const", std::to_string(length)}, endline);
              }
              else if (expression.name == "id")// integer constant
              {
                generate_code("{op} {value}",
                              {"local.get", get_identifier_of(expression)}, endline);
              }
              else if (expression.name == "!")// integer constant
              {
                // take the current value on the stack and invert it
                generate_code("{op}", {"i32.sub"});
                generate_comment("end negation");
              }
              else if (asm_math_operations.count(expression.name))// maths
              {
                auto type_of_result =
                        asm_type_name.at(expression.get_attribute<std::string>("type"));
                generate_code("{type}.{op}", {type_of_result, asm_math_operations[expression.name]}, endline);

                // result is now on the stack.,
              }
              else if (asm_conditional_operations.count(expression.name))// maths
              {
                auto type_of_result =
                        asm_type_name.at(expression.get_attribute<std::string>("type"));
                generate_code("{type}.{op}", {type_of_result, asm_conditional_operations[expression.name]}, endline);

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

    generate_comment("begins auto generated .wasm code", {}, endline);
    // todo generate code...
    // foreach node in the ast: print code...

    // todo import global decls for halt, getchar, and printc...
    // todo start with parameters
    pre_post_order_apply(
            *root,

            [&](ASTNodeBase &node) { return generate_code(&node); },

            [&](ASTNodeBase &node) { post_process(&node); });
    generate_prints();
    generate_comment("finished auto generated .wasm code", {}, endline);
  }
};

#endif// SCANNER_CODE_GENERATOR_H
