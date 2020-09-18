#ifndef INCLUDE_ALGORITHMS_HPP
#define INCLUDE_ALGORITHMS_HPP

#include "polynomial.hpp"
#include "polynomial_set.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> Reduce(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> SPolynomial(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomialSet<UCoefficientType, UOrder>
Buchberger(TPolynomialSet<UCoefficientType, UOrder> polynomial_set);

template<typename UCoefficientType, typename UOrder>
TPolynomialSet<UCoefficientType, UOrder>
AutoReduce(TPolynomialSet<UCoefficientType, UOrder> polynomial_set);

}

#include "algorithm.tpp"

#endif // INCLUDE_ALGORITHMS_HPP
