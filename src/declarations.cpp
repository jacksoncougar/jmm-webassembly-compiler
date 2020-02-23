#include "declarations.h"
#include <cstdlib>

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = static_cast<struct numval *>(malloc(sizeof(struct ast)));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newnum(double d)
{
    struct numval *a = static_cast<struct numval *>(malloc(sizeof(struct numval)));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct ast *)a;
}