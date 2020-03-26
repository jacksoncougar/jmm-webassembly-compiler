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
    // the traversal can be short-circuited but will always run both the pre and post order function on every visited node.
    auto $continue = pre_order_function(root);
    if ($continue) {
        for (auto &child : root.children()) {
            pre_post_order_apply(*child, pre_order_function, post_order_function);
        }
    }
    post_order_function(root);
    return $continue;
}
