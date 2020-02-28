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
