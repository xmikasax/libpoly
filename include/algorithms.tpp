#include "algorithms.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
Reduce(TPolynomial<UCoefficientType, UOrder> p1, TPolynomial<UCoefficientType, UOrder> p2)
{
    return p1 + p2;
    // for (auto term_iterator = p1.rbegin(); term_iterator != p1.rend(); ++term_iterator) {
    // }
}

}
