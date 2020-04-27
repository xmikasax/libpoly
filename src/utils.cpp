#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>

namespace NLibPoly {

namespace NUtils {

class TLibPolyException : public std::exception {
public:
    TLibPolyException(const char *error)
        : Error(error) {}

    virtual const char* what() const noexcept {
        return Error;
    }

private:
    const char *Error = nullptr;
};

void Halt(const char *error) {
    throw TLibPolyException(error);
}

}

}
