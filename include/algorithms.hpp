#ifndef INCLUDE_ALGORITHMS_HPP
#define INCLUDE_ALGORITHMS_HPP

#include "polynomial.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> Reduce(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> SPolynomial(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

}

#include "algorithms.tpp"

#endif // INCLUDE_ALGORITHMS_HPP
