//
// Created by Jackson Cougar Wiebe on 4/14/2020.
//

#include "semantic_checker.h"
#include "driver.h"
#include "scope_stack.hpp"
#include "template.hpp"
#include "tokens.h"
#include <fstream>
#include <string>
#include <vector>

void SemanticChecker::process(ASTNodeBase *root)
{
  scopes.open_new_scope();
  std::vector<std::string> type_stack;

  auto putchar_ste = SymbolTableEntry{
          "putchar", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "void putchar (int)",
                  "void",
                  1,
                  {"int"},
                  yy::location()}};
  auto getchar_ste = SymbolTableEntry{
          "getchar", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "int getchar ()",
                  "int",
                  0,
                  {},
                  yy::location()}};
  auto exit_ste = SymbolTableEntry{
          "exit", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "void exit ()",
                  "void",
                  0,
                  {},
                  yy::location()}};

  auto printi_ste = SymbolTableEntry{
          "printi", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "void printi (int)",
                  "void",
                  1,
                  {"int"},
                  yy::location()}};
  auto printc_ste = SymbolTableEntry{
          "printc", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "void printc (int)",
                  "void",
                  1,
                  {"int"},
                  yy::location()}};
  auto printb_ste = SymbolTableEntry{
          "printb", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "void printb (int)",
                  "void",
                  1,
                  {"int"},
                  yy::location()}};
  auto prints_ste = SymbolTableEntry{
          "prints", "", "function",
          yy::location(),
          new FunctionSymbolTableEntry{
                  "void prints (string)",
                  "void",
                  1,
                  {"string"},
                  yy::location()}};

  scopes.define(Identifier{"putchar"}, putchar_ste);
  scopes.define(Identifier{"getchar"}, getchar_ste);
  scopes.define(Identifier{"exit"}, exit_ste);

  scopes.define(Identifier{"printi"}, printi_ste);
  scopes.define(Identifier{"printc"}, printc_ste);
  scopes.define(Identifier{"printb"}, printb_ste);
  scopes.define(Identifier{"prints"}, prints_ste);

  scopes.open_new_scope();

  bool has_main_declaration = false;

  // pass 0: process global decls
  pre_post_order_apply(
          *root,
          [](auto &node) {
            if (node.type == ASTNodeType::globaldeclarations)
            {
              for (auto &child : node.children())
              {
                child->set_attribute("global", true);
              }
            }
            return true;
          },
          [&](auto &node) {
            if (!node.has_attribute("global"))
              return;// only process globals
            if (node.type == ASTNodeType::variabledeclaration)
            {
              node.set_attribute("processed", true);
              auto type = node[0].name;
              auto id = node[1].template get_attribute<std::string>("value");

              auto entry = SymbolTableEntry{
                      id, "", type,
                      node.template get_attribute<yy::location>("location"), nullptr};
              node.set_attribute(
                      "symbol",
                      scopes.define({id, node[1].template get_attribute<yy::location>(
                                                 "location")},
                                    std::move(entry)));
            }
            if (node.type == ASTNodeType::mainfunctiondeclaration)
            {
              has_main_declaration = true;
              node.set_attribute("processed", true);
              auto id = node[0][0].template get_attribute<std::string>("value");

              if (node[0].children().size() > 1)
              {
                error(node.template get_attribute<yy::location>("location"),
                      " main declaration cannot have parameters.");
              }

              node.set_attribute(
                      "symbol",
                      scopes.define(
                              {id,
                               node[0][0].template get_attribute<yy::location>("location")},
                              {id, "", "main",
                               node.template get_attribute<yy::location>("location"),
                               nullptr}));
            }
            if (node.type == ASTNodeType::functiondeclaration)
            {
              node.set_attribute("processed", true);
              auto return_type = node[0][0].name;
              auto id = node[0][1][0].template get_attribute<std::string>("value");
              node.set_attribute("name", id);

              std::vector<std::string> params;
              if (node[0][1].children().size() > 1)
              {
                for (auto &p : node[0][1][1].children())
                {
                  params.emplace_back((*p)[0].name);
                }
              }

              auto function_symbol = new FunctionSymbolTableEntry(
                      Template{"{rtype} {id} ({args})"} << return_type << id << params,
                      return_type, (int) params.size(),
                      std::vector<std::string>(params.begin(), params.end()),
                      node.template get_attribute<yy::location>("location"));

              auto entry = SymbolTableEntry(
                      id, "", "function",
                      node.template get_attribute<yy::location>("location"),
                      function_symbol);

              node.set_attribute(
                      "symbol",
                      scopes.define(
                              {id, node[0][1][0].template get_attribute<yy::location>(
                                           "location")},
                              std::move(entry)));
            }
          });

  if (!has_main_declaration && !runtime_library)
  {
    error(root->template get_attribute<yy::location>("location"),
          " No main declaration.");
  }

  typedef std::string type;
  typedef std::string operator_t;

  std::map<std::tuple<operator_t, type>, type> unary_operand_types = {
          {{"!", "boolean"}, "boolean"},
          {{"-", "int"}, "int"},
  };

  std::map<std::tuple<operator_t, type, type>, type> binary_operand_types = {
          {{"=", "int", "int"}, "int"},
          {{"=", "boolean", "boolean"}, "boolean"},
          {{"+", "int", "int"}, "int"},
          {{"-", "int", "int"}, "int"},
          {{"*", "int", "int"}, "int"},
          {{"/", "int", "int"}, "int"},
          {{"%", "int", "int"}, "int"},

          {{"<", "int", "int"}, "boolean"},
          {{"<=", "int", "int"}, "boolean"},
          {{">", "int", "int"}, "boolean"},
          {{">=", "int", "int"}, "boolean"},

          {{"==", "int", "int"}, "boolean"},
          {{"!=", "int", "int"}, "boolean"},
          {{"==", "boolean", "boolean"}, "boolean"},
          {{"!=", "boolean", "boolean"}, "boolean"},

          {{"&&", "boolean", "boolean"}, "boolean"},
          {{"||", "boolean", "boolean"}, "boolean"},
  };

  // pass 1: process all other decls
  int scope_depth = 0;
  pre_post_order_apply(
          *root,
          [&](auto &node) {
            if (node.type == ASTNodeType::functiondeclaration)
            {
              scopes.open_new_scope();
              node[0].set_attribute("function-scope", true);
              node[1].set_attribute("function-scope", true);
              scope_depth++;
            }

            if (node.type == ASTNodeType::block)
            {
              scope_depth++;
            }

            if (!node.has_attribute("function-scope") &&
                node.type == ASTNodeType::block)
            {
              scopes.open_new_scope();
            }

            if (node.type == ASTNodeType::variabledeclaration)
            {
              node.set_attribute("type", node[0].name);
              node.set_attribute("name", node[1].template get_attribute<std::string>("value"));
              return false;// don't go deeper
            }

            if (node.type == ASTNodeType::formalparameter)
            {
              node.set_attribute("name", node[1].template get_attribute<std::string>("value"));
              return false;// don't go deeper
            }

            return true;
          },
          [&](auto &node) {
            if (node.type == ASTNodeType::functiondeclaration)
            {
              scopes.close_top_scope();
              scope_depth--;
            }

            if (node.type == ASTNodeType::block)
            {
              scope_depth--;
            }

            if (!node.has_attribute("function-scope") &&
                node.type == ASTNodeType::block)
            {
              scopes.close_top_scope();
            }

            if (node.has_attribute("processed"))
              return;

            if (node.type == ASTNodeType::variabledeclaration)
            {
              node[1].set_attribute("processed", true);
              auto type = node[0].name;
              auto id = node[1].template get_attribute<std::string>("value");

              node.set_attribute(
                      "symbol",
                      scopes.define(
                              {id,
                               node[1].template get_attribute<yy::location>("location")},
                              {id, "", type,
                               node.template get_attribute<yy::location>("location"),
                               nullptr}));
              if (scope_depth != 1 && scope_depth != 2)// todo why
              {
                error(node.template get_attribute<yy::location>("location"),
                      " local declarations must appear in outermost scope.");
              }
            }
            if (node.type == ASTNodeType::functiondeclaration)
            {
              auto rtype = node[0][0].name;
              auto id = node[0][1][0].template get_attribute<std::string>("value");

              std::vector<std::string> params;
              if (node[0][1].children().size() > 1)
              {
                for (auto &p : node[0][1][1].children())
                {
                  params.emplace_back((*p)[0].name);
                }
              }
              auto param_list = std::accumulate(
                      params.begin(), params.end(), std::string(),
                      [](const std::string &a, const std::string &b) -> std::string {
                        return a + (a.length() > 0 ? "," : "") + b;
                      });
              auto entry = SymbolTableEntry{
                      id, "", "function",
                      node.template get_attribute<yy::location>("location"),
                      new FunctionSymbolTableEntry(FunctionSymbolTableEntry{
                              Template{"{rtype} {id} ({args})"} << rtype << id
                                                                << param_list,
                              rtype,
                              (int) params.size(),
                              {params.begin(), params.end()},
                              node.template get_attribute<yy::location>("location")})};
              node.set_attribute(
                      "symbol",
                      scopes.define(
                              {id, node[0][1][0].template get_attribute<yy::location>(
                                           "location")},
                              std::move(entry)));
            }

            if (node.type == ASTNodeType::formalparameter)
            {
              node[1].set_attribute("processed", true);
              auto type = node[0].name;
              node.set_attribute("type", type);
              auto id = node[1].template get_attribute<std::string>("value");

              node.set_attribute(
                      "symbol",
                      scopes.define(
                              {id,
                               node[1].template get_attribute<yy::location>("location")},
                              {id, "", type,
                               node.template get_attribute<yy::location>("location"),
                               nullptr}));
            }
            if (node.type == ASTNodeType::functioninvocation)
            {
              if (node.children().size() > 1)
              {
                node[1].set_attribute("processed", true);
              }
              auto id = node[0].template get_attribute<std::string>("value");
              auto symbol = node.set_attribute(
                      "symbol",
                      scopes.lookup({id, node[0].template get_attribute<yy::location>(
                                                 "location")}));
              if (!symbol->function)
              {
                error(node.template get_attribute<yy::location>("location"),
                      " Identifier '", id, "' does not name a callable function.");
              }
              else
              {
                node.set_attribute("type", symbol->function->return_type);
              }
            }

            if (node.type == ASTNodeType::identifier)
            {
              auto symbol = node.set_attribute(
                      "symbol",
                      scopes.lookup(
                              {node.template get_attribute<std::string>("value"),
                               node.template get_attribute<yy::location>("location")}));

              if (symbol)
              {
                node.set_attribute("type", symbol->type);
              }
              else
              {
                node.set_attribute("type", "<error-type>"s);
              }
            }
            // types down here...

            if (node.type == ASTNodeType::unaryexpression)
            {
              // std::cout << node.template
              // get_attribute<yy::location>("location") << std::endl;
              auto operand = node[0].template get_attribute<std::string>("type");
              auto op = node.name;
              auto result_type = unary_operand_types.find({op, operand});
              if (result_type == unary_operand_types.end())
              {
                error(node.template get_attribute<yy::location>("location"),
                      " Type mismatch in operator '", op, "'");
                node.set_attribute("type", "<error-type>"s);
              }
              else
              {
                node.set_attribute("type", result_type->second);
              }
            }

            if (node.type == ASTNodeType::infixoperator)
            {
              // std::cout << node.template
              // get_attribute<yy::location>("location") << std::endl;
              auto right = node[0].template get_attribute<std::string>("type");
              auto left = node[1].template get_attribute<std::string>("type");
              auto op = node.name;
              auto result_type = binary_operand_types.find({op, left, right});
              if (result_type == binary_operand_types.end())
              {
                error(node.template get_attribute<yy::location>("location"),
                      " Type mismatch in operator '", op, "'");
                node.set_attribute("type", "<error-type>"s);
              }
              else
              {
                node.set_attribute("type", result_type->second);
              }
            }
          });
  scopes.close_top_scope();

  // pass 2: type checking
  pre_post_order_apply(
          *root, [](const auto &node) { return true; },
          [](auto &node) {
            if (node.type == ASTNodeType::ifstatement)
            {
              if (node[0].template get_attribute<std::string>("type") !=
                  "boolean")
              {
                error(node[0].template get_attribute<yy::location>("location"),
                      " if statement must have boolean type expression.");
              }
            }
            if (node.type == ASTNodeType::whilestatement)
            {
              if (node[0].template get_attribute<std::string>("type") !=
                  "boolean")
              {
                error(node[0].template get_attribute<yy::location>("location"),
                      " while statement must have boolean type expression.");
              }
            }
            if (node.type == ASTNodeType::functioninvocation)
            {
              // check return type
              // check number of arguments & types
              auto *symbol =
                      node[0].template get_attribute<SymbolTableEntry *>("symbol");

              std::vector<std::string> params;
              if (node.children().size() > 1)
              {
                for (auto &p : node[1].children())
                {
                  params.emplace_back(
                          p->template get_attribute<std::string>("type"));
                }
              }

              if (!(symbol->function))
                return;// hmmm

              if ((size_t) symbol->function->number_of_args !=
                  (size_t) params.size())
              {
                error(node.template get_attribute<yy::location>("location"),
                      " wrong number of arguments: expected '",
                      symbol->function->number_of_args, "' but received '",
                      params.size(), "'.");
              }
              if (symbol->function->arg_types != params)
              {
                auto it1 = params.begin();
                auto it2 = symbol->function->arg_types.begin();
                while (it1 != params.end() &&
                       it2 != symbol->function->arg_types.end())
                {
                  if (*it1 != *it2)
                  {
                    error(node.template get_attribute<yy::location>("location"),
                          " incorrect argument type: expected '", *it2,
                          "' but was '", *it1, "'");
                  }
                  it1++;
                  it2++;
                }
                while (it1 != params.end())
                {
                  error(node.template get_attribute<yy::location>("location"),
                        " extra argument type: '", *it1, "'");
                  it1++;
                }
                while (it2 != symbol->function->arg_types.end())
                {
                  error(node.template get_attribute<yy::location>("location"),
                        " missing argument type: '", *it2, "'");
                  it2++;
                }
              }
            }
          });

  // pass 3: general catch-all pass
  int inside_while_scope = 0;
  type return_type;
  bool require_return = false;
  bool has_return = false;
  pre_post_order_apply(
          *root,
          [&inside_while_scope, &require_return, &has_return,
           &return_type](const auto &node) {
            if (node.type == ASTNodeType::whilestatement)
            {
              inside_while_scope++;
            }
            if (node.type == ASTNodeType::functiondeclaration)
            {
              auto symbol =
                      node.template get_attribute<SymbolTableEntry *>("symbol");
              return_type = symbol->function->return_type;
              require_return = return_type != "void";
              has_return = false;
            }
            return true;
          },
          [&inside_while_scope, &require_return, &has_return,
           &return_type](auto &node) {
            if (node.type == ASTNodeType::functiondeclaration)
            {
              if (require_return && !has_return)
              {
                error(node.template get_attribute<yy::location>("location"),
                      " function requires return statement.");
              }
            }
            if (node.type == ASTNodeType::breakstatement)
            {
              if (inside_while_scope <= 0)
              {
                error(node.template get_attribute<yy::location>("location"),
                      " break statement must be inside of a while loop.");
              }
            }
            if (node.type == ASTNodeType::whilestatement)
            {
              inside_while_scope--;
            }

            if (node.type == ASTNodeType::returnstatement)
            {
              has_return = true;
              auto has_value = !node.children().empty();
              if (!has_value)
              {
                if (return_type != "void")
                {
                  error(node.template get_attribute<yy::location>("location"),
                        " expected return type.");
                }
              }
              else
              {
                auto return_statement_type =
                        node[0].template get_attribute<std::string>("type");
                if (return_type != return_statement_type)
                {
                  error(node.template get_attribute<yy::location>("location"),
                        " mismatched return type.");
                }
              }
            }
          });
}
