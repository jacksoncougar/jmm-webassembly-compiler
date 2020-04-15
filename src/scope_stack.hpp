//
// Created by Jackson Cougar Wiebe on 3/19/2020.
//

#ifndef SCANNER_SCOPESTACK_HPP
#define SCANNER_SCOPESTACK_HPP

#include "tokens.h"

#include <iomanip>
#include <iostream>
#include <location.hh>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

struct Identifier {
  std::string name;
  yy::location location;
};

namespace std {
template <> struct less<Identifier> {
  bool operator()(const Identifier &lhs, const Identifier &rhs) const {

    return lhs.name < rhs.name;
  }
};
} // namespace std

struct FunctionSymbolTableEntry {
  std::string function_prototype;
  std::string return_type;
  int number_of_args;
  std::vector<std::string> arg_types;
  yy::location location;

  FunctionSymbolTableEntry(const std::string &functionPrototype,
                           const std::string &returnType, int numberOfArgs,
                           const std::vector<std::string> &argTypes,
                           const yy::location &location)
      : function_prototype(functionPrototype), return_type(returnType),
        number_of_args(numberOfArgs), arg_types(argTypes), location(location) {}

  friend std::ostream &operator<<(std::ostream &out,
                                  FunctionSymbolTableEntry &entry) {
    return out << entry.function_prototype;
  }
};

struct SymbolTableEntry {
  std::string identifier;
  std::string value;
  std::string type;
  yy::location location;
  FunctionSymbolTableEntry *function;

  SymbolTableEntry(const std::string &identifier, const std::string &value,
                   const std::string &type, const yy::location &location,
                   FunctionSymbolTableEntry *function)
      : identifier(identifier), value(value), type(type), location(location),
        function(function) {}

  friend std::ostream &operator<<(std::ostream &out, SymbolTableEntry &entry) {
    out << std::setw(10) << entry.identifier << std::setw(10) << entry.type
        << std::setw(10) << entry.value;
    if (entry.function) {
      out << *entry.function;
    }
    return out;
  }
};

class ScopeStack {
  std::vector<std::variant<std::unique_ptr<SymbolTableEntry>,
                           std::unique_ptr<FunctionSymbolTableEntry>>>
      entries;
  std::vector<std::map<std::string, std::variant<SymbolTableEntry *,
                                                 FunctionSymbolTableEntry *>>>
      scopes;

public:
  void open_new_scope() {
    // std::cout << "[Scope]\tOpening scope\n";
    scopes.emplace_back(); // push back an empty map
  }

  void close_top_scope() {
    // std::cout << "[Scope]\tClosing scope\n";
    if (!scopes.empty()) {
      scopes.pop_back();
    }
  }

  friend std::ostream &operator<<(std::ostream &out, ScopeStack &stack) {
    if (stack.scopes.empty()) {
      return out << "No scopes defined...";
    }

    int index = 0;
    for (const auto &scope : stack.scopes) {
      out << "Scope " << index++ << ":\n";
      for (auto &[name, value] : scope) {
        std::visit([&out](auto &e) { out << ": " << *e << "\n"; }, value);
      }
    }

    out << "Entries: \n";
    for (auto &&e : stack.entries) {
      std::visit([&out](auto &e) { out << *e << "\n"; }, e);
    }

    return out;
  }

  SymbolTableEntry *define(Identifier anIdentifier, SymbolTableEntry entry) {
    auto unique_ptr = std::make_unique<SymbolTableEntry>(std::move(entry));
    auto ptr = unique_ptr.get();
    entries.emplace_back(std::move(unique_ptr));
    auto [it, emplace] = scopes.back().emplace(
        anIdentifier.name, ptr); // add an empty table entry for this
    if (!emplace) {
      error(anIdentifier.location, " Symbol already defined '",
            anIdentifier.name, "'");
    }
    return ptr;
  }

  SymbolTableEntry *lookup(Identifier anIdentifier) {

    for (auto &scope : scopes) {
      auto it = scope.find(anIdentifier.name);
      if (it != scope.end()) {
        return std::get<SymbolTableEntry *>(it->second);
      }
    }

    error(anIdentifier.location, " identifier '", anIdentifier.name,
          "' not defined");
    return nullptr;
  }
};

#endif // SCANNER_SCOPESTACK_HPP
