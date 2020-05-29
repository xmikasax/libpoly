#include "utils.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace NLibPoly {

namespace NUtils {

void Halt(const char* error)
{
    throw TLibPolyException(error);
}

}

}
