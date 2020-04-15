/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#ifndef AST_H
#define AST_H

#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "scope_stack.hpp"
#include <location.hh>

static int tab = 0;

std::ostream &operator<<(std::ostream &out, const class ASTNodeBase &node);

enum class ASTNodeType {
  none = 0,
  start,
  literal,
  type,
  globaldeclarations,
  globaldeclaration,
  variabledeclaration,
  identifier,
  functiondeclaration,
  functionheader,
  functiondeclarator,
  formalparameterlist,
  formalparameter,
  mainfunctiondeclaration,
  mainfunctiondeclarator,
  block,
  blockstatements,
  blockstatement,
  infixoperator,
  statement,
  ifstatement,
  whilestatement,
  returnstatement,
  breakstatement,
  statementexpression,
  primary,
  argumentlist,
  functioninvocation,
  postfixexpression,
  unaryexpression,
  multiplicativeexpression,
  additiveexpression,
  relationalexpression,
  equalityexpression,
  conditionalandexpression,
  conditionalorexpression,
  assignmentexpression,
  assignment,
  expression
};

class ASTNodeBase {
protected:
  std::vector<std::unique_ptr<ASTNodeBase>> m_children;
  std::map<std::string,
           std::variant<yy::location, std::string, int, bool,
                        SymbolTableEntry *, FunctionSymbolTableEntry *>>
      attributes;

public:
  std::string name;
  ASTNodeType type = ASTNodeType::none;

  [[nodiscard]] const std::vector<std::unique_ptr<ASTNodeBase>> &
  children() const {
    return m_children;
  }

  // adds the node as a child.
  void add(ASTNodeBase *node);

  [[nodiscard]] bool has_attribute(const std::string &attribute_name) const {
    return attributes.find(attribute_name) != attributes.end();
  }

  template <typename T> T get_attribute(std::string attribute_name) const {
    return std::get<T>(attributes.at(attribute_name));
  }

  template <typename T>
  T &set_attribute(const std::string &attribute_name, T attribute_value) {
    attributes[attribute_name] = attribute_value;
    return std::get<T>(attributes.at(attribute_name));
  }

  ASTNodeBase &operator[](const size_t index) const {
    return *m_children[index];
  }

  // prints this node,its attributes, and its child nodes.
  virtual std::ostream &print(std::ostream &out) const = 0;

  explicit ASTNodeBase(ASTNodeType type, std::string name,
                       std::initializer_list<ASTNodeBase *> children = {})
      : name(std::move(name)), type(type) {
    for (auto child : children) {
      m_children.emplace_back(std::unique_ptr<ASTNodeBase>(child));
    }
  }
};

template <typename T> struct ASTNodeAttribute {
  std::string label;
  T value;

  friend std::ostream &operator<<(std::ostream &out,
                                  const ASTNodeAttribute &node) {
    out << node.label << ": " << node.value;
    return out;
  }
};

class ASTNode : public ASTNodeBase {
public:
  ASTNode(ASTNodeType type, std::string name,
          std::initializer_list<ASTNodeBase *> children = {})
      : ASTNodeBase(type, name, children) {}

  std::ostream &print(std::ostream &out) const override;
};

void pre_order_apply(ASTNodeBase &root,
                     const std::function<void(ASTNodeBase &)> &function);

void post_order_apply(ASTNodeBase &root,
                      const std::function<void(ASTNodeBase &)> &function);

bool pre_post_order_apply(
    ASTNodeBase &root,
    const std::function<bool(ASTNodeBase &)> &pre_order_function,
    const std::function<void(ASTNodeBase &)> &post_order_function);

#endif // AST_H