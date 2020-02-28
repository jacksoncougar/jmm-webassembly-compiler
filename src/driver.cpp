#include "driver.h"
#include "parser.hpp"

void yy::Driver::parse_stream(std::istream &stream)
{

    lexer = std::make_unique<Lexer>();
    lexer->yyrestart(stream); // set lexer to read from input file.

    Parser parser(*this);

    // this wasted 2 hours of my life I'm never getting back.
    parser.set_debug_level(0);

    parser.parse();
}