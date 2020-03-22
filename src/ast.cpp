#include "ast.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const ASTNodeBase &node)
{
    return node.print(out);
}

void ASTNodeBase::add(ASTNodeBase *node)
{
    m_children.emplace_back(std::unique_ptr<ASTNodeBase>(node));
}

void pre_order_apply(const ASTNodeBase &root, const std::function<void(const ASTNodeBase &)> &function) {
    function(root);
    for(auto& child : root.children()) {
        pre_order_apply(*child, function);
    }
}

void post_order_apply(const ASTNodeBase &root, const std::function<void(const ASTNodeBase &)> &function) {
    for(auto& child : root.children()) {
        post_order_apply(*child, function);
    }
    function(root);
}

void pre_post_order_apply(
    const ASTNodeBase &root, const std::function<void(const ASTNodeBase &)> &pre_order_function,
    const std::function<void(const ASTNodeBase &)> &post_order_function
) {
    pre_order_function(root);
    for(auto& child : root.children()) {
        pre_post_order_apply(*child, pre_order_function, post_order_function);
    }
    post_order_function(root);
}
