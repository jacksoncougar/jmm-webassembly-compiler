/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <numeric>
#include <utility>

#include "scope_stack.hpp"
#include "tokens.h"
#include "driver.h"
#include "template.hpp"

using namespace std::literals::string_literals;

int main(int argc, char **argv) {
    try {
        if (argc < 2) {
            throw "You must pass the pathname of an input file to scan as the first program argument.";
        }
        if (argc > 2) {
            throw "This program must accept exactly one command-line argument: the pathname of an input file.";
        }

        std::ifstream ifs(argv[1]);
        if (!ifs.is_open()) {
            throw "Could not open input file '" + std::string(argv[1]) + "'";
        }

        yy::Driver driver;
        driver.streamname = argv[1]; // for printing errors 
        driver.parse_stream(ifs);

        // semantic checking...
        ScopeStack scopes;
        scopes.open_new_scope();

        std::vector<std::string> type_stack;

        // pass 0: process global decls
        pre_post_order_apply(
                *driver.root,
                [](auto &node) {
                    if (node.type == ASTNodeType::globaldeclarations) {
                        for (auto &child : node.children()) {
                            child->set_attribute("global", true);
                        }
                    }
                    return true;
                },
                [&scopes](auto &node) {
                    if (!node.has_attribute("global")) return; // only process globals
                    if (node.type == ASTNodeType::variabledeclaration) {
                        node.set_attribute("processed", true);
                        auto type = node[0].name;
                        auto id = node[1].template get_attribute<std::string>("value");

                        auto entry = SymbolTableEntry{id, "", type, node.location};
                        node.set_attribute("ste", scopes.define({id, node[1].location}, std::move(entry)));
                    }
                    if (node.type == ASTNodeType::mainfunctiondeclaration) {
                        node.set_attribute("processed", true);
                        auto id = node[0].template get_attribute<std::string>("value");

                        node.set_attribute("ste", scopes.define({id, node[0].location},
                                                                {id, "", "main", node.location, nullptr}));
                    }
                    if (node.type == ASTNodeType::functiondeclaration) {
                        node.set_attribute("processed", true);
                        auto return_type = node[0][0].name;
                        auto id = node[0][1][0].template get_attribute<std::string>("value");

                        std::vector<std::string> params;
                        if (node[0][1].children().size() > 1) {
                            for (auto &p : node[0][1][1].children()) {
                                params.emplace_back((*p)[0].name);
                            }
                        }

                        auto entry = SymbolTableEntry{id, "", "function", node.location,
                                                      std::make_unique<FunctionSymbolTableEntry>(
                                                              FunctionSymbolTableEntry{
                                                                      Template{"{rtype} {id} ({args})"} << return_type
                                                                                                        << id << params,
                                                                      return_type, (int) params.size(),
                                                                      {params.begin(), params.end()},
                                                                      node.location})};
                        node.set_attribute("ste", scopes.define({id, node[0][1][0].location}, std::move(entry)));

                    }
                }
        );

        typedef  std::string type;
        typedef  std::string $operator;

        std::map<std::tuple<$operator, type>, type> unary_operand_types = {
                {{"!", "boolean"}, "boolean"},
                {{"-", "int"}, "int"},
        };

        std::map<std::tuple<$operator, type, type>, type> binary_operand_types = {
                {{"=", "int", "int"}, "int"},
                {{"=", "boolean", "boolean"}, "boolean"},
                {{"+", "int", "int"}, "int"},
                {{"-", "int", "int"}, "int"},
                {{"*", "int", "int"}, "int"},
                {{"/", "int", "int"}, "int"},
                {{"%", "int", "int"}, "int"},

                {{"<", "int", "int"}, "int"},
                {{"<=", "int", "int"}, "int"},
                {{">", "int", "int"}, "int"},
                {{">=", "int", "int"}, "int"},

                {{"==", "int", "int"}, "int"},
                {{"!=", "int", "int"}, "int"},

                {{"&&", "boolean", "boolean"}, "boolean"},
                {{"||", "boolean", "boolean"}, "boolean"},
        };

        // pass 1: process all other decls
        pre_post_order_apply(
                *driver.root,
                [&scopes](const auto &node) {

                    if (node.type == ASTNodeType::functiondeclaration) {
                        scopes.open_new_scope();
                        node[0].set_attribute("function-scope", true);
                        node[1].set_attribute("function-scope", true);
                    }

                    if (!node.has_attribute("function-scope") && node.type == ASTNodeType::block) {
                        scopes.open_new_scope();
                    }

                    if (node.type == ASTNodeType::variabledeclaration) {
                        return false; // don't go deeper
                    }
                    if (node.type == ASTNodeType::formalparameter) {
                        return false; // don't go deeper
                    }

                    return true;
                },
                [&scopes, &binary_operand_types](auto &node) {

                    if (node.type == ASTNodeType::functiondeclaration) {
                        scopes.close_top_scope();
                    }

                    if (!node.has_attribute("function-scope") && node.type == ASTNodeType::block) {
                        scopes.close_top_scope();
                    }

                    if (node.has_attribute("processed")) return;

                    if (node.type == ASTNodeType::variabledeclaration) {
                        node[1].set_attribute("processed", true);
                        auto type = node[0].name;
                        auto id = node[1].template get_attribute<std::string>("value");


                        auto ste = node.set_attribute("ste", scopes.define({id, node[1].location},
                                                                           {id, "", type, node.location, nullptr}));
                    }
                    if (node.type == ASTNodeType::functiondeclaration) {
                        auto rtype = node[0][0].name;
                        auto id = node[0][1][0].template get_attribute<std::string>("value");

                        std::vector<std::string> params;
                        if (node[0][1].children().size() > 1) {
                            for (auto &p : node[0][1][1].children()) {
                                params.emplace_back((*p)[0].name);
                            }
                        }
                        auto param_list = std::accumulate(params.begin(), params.end(), std::string(),
                                                          [](const std::string &a,
                                                             const std::string &b) -> std::string {
                                                              return a + (a.length() > 0 ? "," : "") + b;
                                                          });
                        auto entry = SymbolTableEntry{id, "", "function", node.location,
                                                      std::make_unique<FunctionSymbolTableEntry>(
                                                              FunctionSymbolTableEntry{
                                                                      Template{"{rtype} {id} ({args})"} << rtype << id
                                                                                                        << param_list,
                                                                      rtype, (int) params.size(),
                                                                      {params.begin(), params.end()},
                                                                      node.location})};
                        node.set_attribute("ste", scopes.define({id, node[0][1][0].location}, std::move(entry)));
                    }

                    if (node.type == ASTNodeType::formalparameter) {
                        node[1].set_attribute("processed", true);
                        auto type = node[0].name;
                        auto id = node[1].template get_attribute<std::string>("value");

                        node.set_attribute("ste", scopes.define({id, node[1].location},
                                                                {id, "", type, node.location, nullptr}));
                    }
                    if (node.type == ASTNodeType::functioninvocation) {
                        node[1].set_attribute("processed", true);
                        auto id = node[0].template get_attribute<std::string>("value");
                        auto symbol = node.set_attribute("ste", scopes.lookup({id, node[1].location}));
                        node.set_attribute("type", symbol->function->return_type);
                    }

                    if (node.type == ASTNodeType::identifier) {
                        auto symbol = node.set_attribute("ste",
                                           scopes.lookup(
                                                   {node.template get_attribute<std::string>("value"), node.location}));

                        node.set_attribute("type", symbol->type);
                    }
                    // types down here...

                    if (node.type == ASTNodeType::infixoperator) {
                        auto right = node[0].template get_attribute<std::string>("type");
                        auto left = node[1].template get_attribute<std::string>("type");
                        auto op = node.name;
                        auto result_type = binary_operand_types.find({op, left, right});
                        if(result_type == binary_operand_types.end()) {
                            error(node.template get_attribute<yy::location>("location"), " Type mismatch in operator '", op, "'\n");
                            node.set_attribute("type", "<error-type>"s);
                        }
                        else {
                            node.set_attribute("type", result_type->second);
                        }
                    }

                });

        // pass 2: type checking
        pre_post_order_apply(*driver.root, [&scopes](const auto &node) {
            return true;
        }, [&scopes](auto &node) {
            if (node.type == ASTNodeType::ifstatement) {
                if(node[0].template get_attribute<std::string>("type") != "boolean") {
                    error(node[0].template get_attribute<yy::location>("location"), " if statement must have boolean type.");
                }
            }
            if (node.type == ASTNodeType::functioninvocation) {
                // check return type
                // check number of arguments & types
                SymbolTableEntry *symbol = node[0].template get_attribute<SymbolTableEntry *>("ste");

                std::vector<std::string> params;
                if (node[1].children().size() > 1) {
                    for (auto &p : node[1].children()) {
                        params.emplace_back(p->name);
                    }
                }

                if (symbol->function->number_of_args != params.size()) {
                    error(node.template get_attribute<yy::location>("location"),
                          " wrong number of arguments: expected '", symbol->function->number_of_args,
                          "' but received '", params.size(),
                          "'.");
                }
                if (symbol->function->arg_types != params) {
                    std::equal(params.begin(), params.end(), symbol->function->arg_types.begin(),
                               [&node](auto r, auto e) {
                                   if (e != r) {
                                       error(node.template get_attribute<yy::location>("location"),
                                             " incorrect argument type: expected '", e,
                                             "' but was '", r, "'");
                                   }
                                   return true;
                               });
                }
            }
        });

        std::cout << scopes;
        std::cout << "aAST: \n" << *driver.root << std::endl;
    }
    catch (const char *e) {
        error(e);
        exit(1);
    }
    catch (const std::string &e) {
        error(e);
        exit(1);
    }

    return 0;
}