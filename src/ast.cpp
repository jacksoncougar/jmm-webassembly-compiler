#include "ast.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const ASTNodeBase &node) {
    return node.print(out);
}

void ASTNodeBase::add(ASTNodeBase *node) {
    m_children.emplace_back(std::unique_ptr<ASTNodeBase>(node));
}

void pre_order_apply(ASTNodeBase &root, const std::function<void(ASTNodeBase &)> &function) {
    function(root);
    for (auto &child : root.children()) {
        pre_order_apply(*child, function);
    }
}

void post_order_apply(ASTNodeBase &root, const std::function<void(ASTNodeBase &)> &function) {
    for (auto &child : root.children()) {
        post_order_apply(*child, function);
    }
    function(root);
}

bool pre_post_order_apply(
        ASTNodeBase &root, const std::function<bool(ASTNodeBase &)> &pre_order_function,
        const std::function<void(ASTNodeBase &)> &post_order_function
) {
  // the traversal can be short-circuited but will always run both the pre and
  // post order function on every visited node.
  auto continue_traversal = pre_order_function(root);
  if (continue_traversal) {
    for (auto &child : root.children()) {
      pre_post_order_apply(*child, pre_order_function, post_order_function);
    }
  }
  post_order_function(root);
  return continue_traversal;
}

std::ostream &ASTNode::print(std::ostream &out) const {

  out << std::string(current_indentation_level, ' ') << "(" << name;
  if (!attributes.empty()) {
    out << " (attributes (";
    auto it = attributes.begin();
    while (it != std::prev(attributes.end())) {
      auto [name, a] = *it++;
      std::visit(
          [&out, name = &name](auto &&a) { out << name << ": " << a << ", "; },
          a);
    }
    if (it != attributes.end()) {
      auto [name, a] = *it;
      std::visit([&out, name = &name](auto &&a) { out << name << ": " << a; },
                 a);
    }
    out << "))";
  }

  out << ")\n";
  current_indentation_level++;

  auto &children = this->children();
  if (!children.empty()) {
    for (auto &n : children) {
      if (n)
        out << *n;
    }
  }
  current_indentation_level--;
  return out;
}