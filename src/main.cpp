/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>

#include "tokens.h"

#if !defined(yyFlexLexerOnce)
// apparently this fixes a specific problem with flex++
#include <FlexLexer.h>
#endif

class Lexer : public yyFlexLexer
{
public:
    /**
     * Returns the attributes associated with the token returned by a previous 
     * call to yylex()
     */
    TokenAttributes attributes()
    {
        return {lineno(), std::string(YYText(), YYLeng())};
    }
};

int main(int argc, char **argv)
{
    try
    {
        if (argc < 2)
        {
            throw "You must pass the pathname of an input file to scan as the first program argument.";
        }
        if (argc > 2)
        {
            throw "This program must accept exactly one command-line argument: the pathname of an input file.";
        }

        std::ifstream ifs(argv[1]);
        if (!ifs.is_open())
        {
            throw "Could not open input file '" + std::string(argv[1]) + "'";
        }

        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>();

        lexer->yyrestart(ifs); // set lexer to read from input file.

        int token;
        while ((token = lexer->yylex()) != 0)
        {
            auto attributes = lexer->attributes();

            std::cout << "(" << tokenToString(token) << ", "
                      << attributes << ")\n";
        }
    }
    catch (const char *e)
    {
        error(e);
        exit(1);
    }
    catch (const std::string &e)
    {
        error(e);
        exit(1);
    }

    return 0;
}