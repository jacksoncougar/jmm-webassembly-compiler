#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include <memory>
#include "lexer.h"

namespace yy
{
class Driver
{
public:
    class std::unique_ptr<Lexer> lexer;

    void parse_stream(std::istream stream);
};
} // namespace yy

#endif