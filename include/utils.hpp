#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>

namespace NLibPoly {

namespace NUtils {

class TLibPolyException : public std::runtime_error {
public:
    TLibPolyException(const char *error)
        : runtime_error(error) {}
};

void Halt(const char *error);

}

}
