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
#include <regex>
#include <sstream>
#include <string>
#include <utility>

using namespace std::literals::string_literals;

struct CodeGenerator// lambda soup; bring crackers.
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

  std::map<std::string, std::string> asm_types = {
          {"int", "i32"},
          {"boolean", "i32"}};

  std::map<std::string, std::string> asm_math_operations = {
          {"+", "add"},
          {"-", "sub"},
          {"*", "mul"},
          {"/", "div_s"},
          {"%", "rem_s"}};

  std::map<std::string, std::string> asm_conditional_operations = {
          {"&&", "and"},
          {"||", "or"},
          {"<", "lt_s"},
          {"<=", "le_s"},
          {">", "gt_s"},
          {">=", "ge_s"},
          {"==", "eq"},
          {"!=", "ne"},
  };

  struct StringTableEntry
  {
    int offset;
    int length;
  };
  std::map<std::string, StringTableEntry> string_table;

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

  std::string asm_type_of(ASTNodeBase &node)
  {
    return asm_types.at(node.get_attribute<std::string>("type"));
  }

  std::string get_identifier_of(ASTNodeBase &node)
  {
    return node.get_attribute<SymbolTableEntry *>("symbol")
            ->data["asm_identifier"];
  }

  bool is_global_id(ASTNodeBase &node)
  {
    return node.get_attribute<SymbolTableEntry *>("symbol")
                   ->data.count("global") > 0;
  }

  std::string trim(std::string string)
  {
    static std::regex bell("\\\\b");
    static std::regex formfeed("\\\\f");
    // remove quotations marks.
    auto value = string.substr(1, string.size() - 2);
    value = std::regex_replace(value, bell, "0x07"s);
    value = std::regex_replace(value, formfeed, "0x0C"s);
    return value;
  }

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

  enum FormatOptions
  {
    none = 0,
    endline = 1,
    align
  };

  void open_scope()
  {
    destination << Indent(*this) << "(";
    current_indentation_level++;
  }

  void close_scope(FormatOptions options = none)
  {
    current_indentation_level--;
    destination << Indent(*this) << ")";
    if (options & endline) newline();
  }

  void newline()
  {
    destination << '\n';
    is_newline = true;
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
    destination.out.flush();
  }

  void generate_code(std::string_view format,
                     std::initializer_list<std::string_view> args = {},
                     FormatOptions options = FormatOptions::none)
  {
    destination << Indent(*this) << Template(format, args);
    if (options & endline) newline();
    destination.out.flush();
  }

  bool generate_params(ASTNodeBase &node)
  {
    switch (node.type)
    {
      case ASTNodeType::returnstatement:
      {
        auto has_return_type = node.children().size() > 0;
        if (has_return_type)
        {
          generate_code("(result {type})", {asm_type_of(*node.children()[0])}, endline);
        }
      }
      break;
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
    }
    return true;
  }

  bool generate_locals(ASTNodeBase &node)
  {
    switch (node.type)
    {
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
    constexpr auto prints_asm_source = R"(
  ;;
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
    constexpr auto printi_source = R"(void printi(int i) {
  int digit;
  int divisor;
  int remainder;
  int lz;
  boolean negative;

  negative = false;


  lz = 0;
  divisor = 1000000000;
  remainder = i;
  digit = 0;

  if(remainder < 0) {
      putchar(45); // '-'
      negative = true;
  }

  // eat up leading zeros

  while(lz == 0 && divisor > 0) {
    lz = remainder / divisor;

    remainder = remainder % divisor;
    divisor = divisor / 10;
  }

  digit = lz;
  while(divisor > 0) {
    if(negative){
      putchar(48 + (0 - digit));
    }
    else {
      putchar(48 + digit);
    }
    digit = remainder / divisor;

    remainder = remainder % divisor;
    divisor = divisor / 10;
  }    if(negative){
      putchar(48 + (0 - digit));
    }
    else {
      putchar(48 + digit);
    }
})";
    constexpr auto printc_source = R"(void printc(int c) {
  putchar(c);
})";
    constexpr auto printb_source = R"(void printb(boolean b) {
  if(b) prints("true");
  else prints("false");
})";

    generate_code(prints_asm_source, {}, endline);

    runtime_library = true;// switch into runtime generation mode...
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
    generate_code(compile(printc_source), {}, endline);
    runtime_library = false;// switch back to normal mode...
  }

  void generate_globals(ASTNodeBase &node)
  {
    for (auto &&global : node.children())
      switch (global->type)
      {
        case ASTNodeType::variabledeclaration:
          auto id = asm_identifier();
          {
            global->get_attribute<SymbolTableEntry *>("symbol")
                    ->data["asm_identifier"] = id;
            global->get_attribute<SymbolTableEntry *>("symbol")
                    ->data["global"] = "true";

            generate_code("(global {id} (mut {type}) ({type}.const 0))",
                          {id,
                           asm_types.at(global->get_attribute<std::string>("type")),
                           asm_types.at(global->get_attribute<std::string>("type"))},
                          endline);
          }
          break;
      }
  }

  bool generate_code(ASTNodeBase *node)
  {
    switch (node->type)
    {
      case ASTNodeType::start:
      {
        open_scope();
        generate_code("module", {}, endline);

        generate_comment("externs/imports", {}, endline);
        generate_externs();
        generate_comment("data", {}, endline);
        generate_strings(*node);
        generate_globals(*node->children()[0]);
        generate_comment("program", {}, endline);
        generate_webasm_code(node->children()[0].get());
        generate_comment("runtime system", {}, endline);
        generate_runtime_system();
        generate_code("(memory 1)", {}, endline);


        return false;// don't descend into children.
      }
      break;

      case ASTNodeType::returnstatement:
      {
        auto has_return_type = node->children().size() > 0;
        if (has_return_type)
        {
          generate_expression_code(node->children()[0].get());
        }
        return false;// don't descend into children.
      };
      break;

      case ASTNodeType::functiondeclaration:
      {

        auto id = node->get_attribute<SymbolTableEntry *>("symbol")->identifier;

        open_scope();
        generate_code("func ${id}", {id}, endline);

        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_params(n); });
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

        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_params(n); });
        pre_order_apply(*node, [&](ASTNodeBase &n) { generate_locals(n); });
      }
      break;
      case ASTNodeType::functioninvocation:
        generate_function_call(*node);
        return false;// don't descend into children;
      case ASTNodeType::infixoperator:
      {
        // lhs = result of rhs...
        auto lhs = node->children()[0].get();
        auto rhs = node->children()[1].get();

        generate_expression_code(rhs);

        // assign that result to the lhs identifier...
        // if lhs is a rvalue
        if (lhs->type == ASTNodeType::identifier)
        {
          generate_code("{op} {lhs}",
                        {is_global_id(*lhs) ? "global.set" : "local.set",
                         lhs->get_attribute<SymbolTableEntry *>("symbol")
                                 ->data.at("asm_identifier")},
                        endline);
        }
        else if (lhs->type == ASTNodeType::functioninvocation)
        {
          // can we assume that the value is on the stack?
        }
        else
        {
          note("Unhandled case '" + node->name + "' in '" +
               __FUNCTION__ + "':" + std::to_string(__LINE__));
        }


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
        generate_code("i32.eqz", {}, endline);
        generate_code("br_if {label}", {exit_label}, endline);
        generate_comment("loop body", {}, endline);
        generate_webasm_code(node->children()[1].get());
        generate_code("br {label}", {continue_label}, endline);

        close_scope(endline);
        close_scope(endline);
        return false;// don't descend into children.
      }
      default:
        note("Unhandled case '" + node->name + "' in '" +
             __FUNCTION__ + "':" + std::to_string(__LINE__));
    }

    return true;// descend into children.
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

  void generate_function_call(ASTNodeBase &functioninvocation)
  {
    auto has_arguments = functioninvocation.get_attribute<SymbolTableEntry *>("symbol")->function->number_of_args > 0;
    if (has_arguments)
    {
      generate_expression_code(functioninvocation.children()[1].get());
    }
    generate_code("call ${function}",
                  {functioninvocation.get_attribute<SymbolTableEntry *>("symbol")->identifier}, endline);
  }


  void generate_expression_code(ASTNodeBase *expression)
  {
    // walk the expression tree from the bottom up building up asm
    // instructions
    pre_post_order_apply(
            *expression, [&, function_name = std::string(__FUNCTION__)](ASTNodeBase &expression) {
             switch (expression.type)
             {
               case ASTNodeType::functioninvocation:
                 generate_function_call(expression);
                 return false;// don't descend into children.

               case ASTNodeType::unaryexpression:
               {
                 if (expression.name == "-")// integer constant
                 {
                   generate_comment("unaryexpression negation", {}, endline);
                   generate_code("{op} {value}", {"i32.const", "0"}, endline);
                 }
                 else if (expression.name == "!")// integer constant
                 {
                   generate_comment("boolean negation", {}, endline);
                 }
                 else
                 {
                   note("Unhandled case '" + expression.name + "' in '" +
                        function_name + "':" + std::to_string(__LINE__));
                 }
               }
               break;
               default:
                 // do no harm.
                 break;
             }
             return true; },
            [&, function_name = std::string(__FUNCTION__)](
                    ASTNodeBase &expression) {
              switch (expression.type)
              {
                case ASTNodeType::functioninvocation:
                  // ignore
                  break;

                case ASTNodeType::unaryexpression:
                  if (expression.name == "-")
                  {
                    generate_code("{op}", {"i32.sub"}, endline);
                    generate_comment("end negation", {}, endline);
                  }
                  else if (expression.name == "!")// integer constant
                  {
                    // take the current value on the stack and invert it
                    generate_code("{op} {value}", {"i32.const", "1"}, endline);
                    generate_code("{op}", {"i32.add"}, endline);
                    generate_code("{op} {value}", {"i32.const", "2"}, endline);
                    generate_code("{op}", {"i32.rem_u"}, endline);
                    generate_comment("end negation", {}, endline);
                  }
                  else
                  {
                    note("Unhandled case '" + expression.name + "' in '" +
                         function_name + "':" + std::to_string(__LINE__));
                  }
                  break;

                case ASTNodeType::infixoperator:

                  if (asm_math_operations.count(expression.name))// maths
                  {
                    auto type_of_result =
                            asm_types.at(expression.get_attribute<std::string>("type"));
                    generate_code("{type}.{op}", {type_of_result, asm_math_operations[expression.name]}, endline);

                    // result is now on the stack.,
                  }
                  else if (asm_conditional_operations.count(expression.name))// maths
                  {
                    auto type_of_result =
                            asm_types.at(expression.get_attribute<std::string>("type"));
                    generate_code("{type}.{op}", {type_of_result, asm_conditional_operations[expression.name]}, endline);

                    // result is now on the stack.,
                  }
                  else
                  {
                    note("Unhandled case '" + expression.name + "' in '" +
                         function_name + "':" + std::to_string(__LINE__));
                  }
                  break;

                case ASTNodeType::literal:
                  if (expression.name == "int")// integer constant
                  {
                    generate_code("{op} {value}",
                                  {"i32.const ", expression.get_attribute<std::string>("value")}, endline);
                  }
                  else if (expression.name == "string")// integer constant
                  {
                    auto [offset, length] = string_table.at(trim(expression.get_attribute<std::string>("value")));
                    generate_code("{op} {value}",
                                  {"i32.const", std::to_string(offset)}, endline);
                    generate_code("{op} {value}",
                                  {"i32.const", std::to_string(length)}, endline);
                  }
                  if (expression.name == "true" || expression.name == "false")// integer constant
                  {
                    auto value = expression.get_attribute<std::string>("value") == "true"
                                         ? "1"
                                         : "0";
                    generate_code("{op} {value}",
                                  {"i32.const", value});
                    generate_comment("boolean " + expression.name, {}, endline);
                  }
                  else
                  {
                    note("Unhandled case '" + expression.name + "' in '" +
                         function_name + "':" + std::to_string(__LINE__));
                  }
                  break;
                case ASTNodeType::identifier:
                {
                  if (expression.name == "id")// integer constant
                  {
                    generate_code("{op} {value}",
                                  {is_global_id(expression) ? "global.get" : "local.get",
                                   get_identifier_of(expression)},
                                  endline);
                  }
                  else
                  {
                    note("Unhandled case '" + expression.name + "' in '" +
                         function_name + "':" + std::to_string(__LINE__));
                  }
                }
                break;
                default:
                {
                  note("Unhandled case '" + expression.name + "' in '" +
                       function_name + "':" + std::to_string(__LINE__));
                }
              }
            });
  }

  void generate_webasm_code(ASTNodeBase *root)
  {

    note(root);

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
