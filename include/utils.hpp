#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>

namespace NLibPoly {

namespace NUtils {

class TLibPolyException : public std::exception {
public:
    TLibPolyException(const char *error);

    virtual const char* what() const noexcept;

private:
    const char *error = nullptr;
};

void Halt(const char *error);

}

}
