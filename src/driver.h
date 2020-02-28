#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include <memory>
#include "lexer.h"
#include "tokens.h"

namespace yy
{
    class Driver
    {
    public:
        std::string streamname;
        class std::unique_ptr<Lexer> lexer;
        
        void error(const class location& l, const std::string& m)
        {
            ::error(l, ": ", m);
        }

        void parse_stream(std::istream& stream);
    };
} // namespace yy

#endif