#ifndef INCLUDE_UTILS_HPP
#define INCLUDE_UTILS_HPP

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace NLibPoly {

namespace NUtils {

class TLibPolyException : public std::runtime_error {
public:
    TLibPolyException(const char* error) : runtime_error(error) {}
};

void Halt(const char* error);

}

}

#include "utils.tpp"

#endif // INCLUDE_UTILS_HPP
