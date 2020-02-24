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
#include "driver.h"
#include "parser.hpp"


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

        yy::Driver driver;
        driver.parse_stream(ifs);
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