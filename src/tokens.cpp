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
