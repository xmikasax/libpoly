#ifndef INCLUDE_INTEGER_MOD_RING_HPP
#define INCLUDE_INTEGER_MOD_RING_HPP

#include <cstddef>

namespace NLibPoly {

template<size_t M>
class TIntegerModRing {
public:
    using TUnsignedInteger = size_t;

public:
    TIntegerModRing(TUnsignedInteger value);

private:
    TUnsignedInteger value = TUnsignedInteger(0);
};

}

#endif // INCLUDE_INTEGER_MOD_RING_HPP
