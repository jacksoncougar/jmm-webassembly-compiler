extern int yylineno;

class AST {
    ASTNode *root;
};

struct ASTNode {
    int nodetype;
    std::vector<ASTNode> children;
};

