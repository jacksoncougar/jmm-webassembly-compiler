/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#include <string>
#include <iomanip>

#include "tokens.h"

std::ostream &operator<<(std::ostream &out, const TokenAttributes &attributes)
{
    out << attributes.lineno << ", " << attributes.lexeme;
    return out;
}

std::string tokenToString(int token)
{
    switch (token)
    {
    case T_TYPE_INT:
        return "T_TYPE_INT";
    case T_TYPE_BOOLEAN:
        return "T_TYPE_BOOLEAN";
    case T_ID:
        return "T_ID";
    case T_LITERAL_STRING:
        return "T_LITERAL_STRING";
    case T_LITERAL_BOOLEAN:
        return "T_LITERAL_BOOLEAN";
    case T_LITERAL_DECIMAL:
        return "T_LITERAL_DECIMAL";
    case T_KEYWORD_TRUE:
        return "T_KEYWORD_TRUE";
    case T_KEYWORD_FALSE:
        return "T_KEYWORD_FALSE";
    case T_KEYWORD_BOOLEAN:
        return "T_KEYWORD_BOOLEAN";
    case T_KEYWORD_INT:
        return "T_KEYWORD_INT";
    case T_KEYWORD_VOID:
        return "T_KEYWORD_VOID";
    case T_KEYWORD_IF:
        return "T_KEYWORD_IF";
    case T_KEYWORD_ELSE:
        return "T_KEYWORD_ELSE";
    case T_KEYWORD_WHILE:
        return "T_KEYWORD_WHILE";
    case T_KEYWORD_BREAK:
        return "T_KEYWORD_BREAK";
    case T_KEYWORD_RETURN:
        return "T_KEYWORD_RETURN";
    case T_OP_PLUS:
        return "T_OP_PLUS";
    case T_OP_MINUS:
        return "T_OP_MINUS";
    case T_OP_MULTIPLY:
        return "T_OP_MULTIPLY";
    case T_OP_DIVIDE:
        return "T_OP_DIVIDE";
    case T_OP_MODULO:
        return "T_OP_MODULO";
    case T_OP_ASSIGNMENT:
        return "T_OP_ASSIGNMENT";
    case T_OP_GT:
        return "T_OP_GT";
    case T_OP_LT:
        return "T_OP_LT";
    case T_OP_LE:
        return "T_OP_LE";
    case T_OP_GE:
        return "T_OP_GE";
    case T_OP_EQ:
        return "T_OP_EQ";
    case T_OP_NE:
        return "T_OP_NE";
    case T_OP_NOT:
        return "T_OP_NOT";
    case T_OP_AND:
        return "T_OP_AND";
    case T_OP_OR:
        return "T_OP_OR";
    case T_PARENTHESIS_OPEN:
        return "T_PARENTHESIS_OPEN";
    case T_PARENTHESIS_CLOSE:
        return "T_PARENTHESIS_CLOSE";
    case T_BRACE_OPEN:
        return "T_BRACE_OPEN";
    case T_BRACE_CLOSE:
        return "T_BRACE_CLOSE";
    case T_SEMICOLON:
        return "T_SEMICOLON";
    case T_COMMA:
        return "T_COMMA";
    case T_UNKNOWN_TOKEN:
        return "T_UNKNOWN_TOKEN";
    default:
        return "<<ERROR>>";
    }
}