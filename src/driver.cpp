#include "driver.h"
#include "parser.hpp"

void Driver::parse_stream(std::istream stream)
    {
        lexer = std::make_unique<Lexer>();
        lexer->yyrestart(stream); // set lexer to read from input file.

        Parser parser(*this);
        parser.parse();
    }