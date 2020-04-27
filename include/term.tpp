#include "term.hpp"

#include <utility>

namespace NLibPoly {

template <typename TCoefficientType>
TTerm<TCoefficientType>::TTerm()
    : Coefficient(1) {}

template <typename TCoefficientType>
TTerm<TCoefficientType>::TTerm(TCoefficientType coeff, TMonomial monomial)
    : TMonomial(monomial), Coefficient(coeff) {}

template<typename TCoefficientType>
TTerm<TCoefficientType>::TTerm(
    const std::initializer_list<std::pair<TIndex, TDegree>> &init_list
)
    : TMonomial(init_list), Coefficient(1) {}

template <typename TCoefficientType>
TCoefficientType TTerm<TCoefficientType>::GetCoefficient() const {
    return Coefficient;
}

template <typename TCoefficientType>
void TTerm<TCoefficientType>::SetCoefficient(TCoefficientType new_coeff) {
    Coefficient = new_coeff;
}

template <typename TCoefficientType>
TTerm<TCoefficientType> &TTerm<TCoefficientType>::operator*=(
    const TTerm<TCoefficientType> &other)
{
    TMonomial::operator*=(other);
    Coefficient *= other.Coefficient;
    return (*this);
}

template <typename TCoefficientType>
TTerm<TCoefficientType> TTerm<TCoefficientType>::operator*(
    const TTerm<TCoefficientType> &other) const
{
    TTerm<TCoefficientType> res(*this);
    return res *= other;
}

template <typename TCoefficientType>
TTerm<TCoefficientType> &TTerm<TCoefficientType>::operator/=(
    const TTerm<TCoefficientType> &other)
{
    TMonomial::operator/=(other);
    Coefficient /= other.Coefficient;
    return (*this);
}

template <typename TCoefficientType>
TTerm<TCoefficientType> TTerm<TCoefficientType>::operator/(
    const TTerm<TCoefficientType> &other) const
{
    TTerm<TCoefficientType> res(*this);
    return res /= other;
}

template <typename TCoefficientType>
TTerm<TCoefficientType> Lcm(
    const TTerm<TCoefficientType> &a,
    const TTerm<TCoefficientType> &b)
{
    return TTerm<TCoefficientType>(
        a.Coefficient * b.Coefficient,
        Lcm(static_cast<const TMonomial&>(a), static_cast<const TMonomial&>(b)));
}

}
