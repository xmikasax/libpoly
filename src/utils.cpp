#include "utils.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>

namespace NLibPoly {

namespace NUtils {

void Halt(const char *error) {
    throw TLibPolyException(error);
}

}

}
