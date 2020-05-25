#include "integer_mod_ring.hpp"

namespace NLibPoly {

template<size_t M>
TIntegerModRing<M>::TIntegerModRing(TUnsignedInteger value)
        : value(value % M)
{
}

}
