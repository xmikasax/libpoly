#include "term.hpp"

#include <utility>

namespace NLibPoly {

template <typename UCoefficientType>
TTerm<UCoefficientType>::TTerm(UCoefficientType coeff, TMonomial monomial)
    : TMonomial(monomial), Coefficient(coeff) {}

template<typename UCoefficientType>
TTerm<UCoefficientType>::TTerm(
    const std::initializer_list<std::pair<TIndex, TDegree>> &init_list
)
    : TMonomial(init_list) {}

template <typename UCoefficientType>
UCoefficientType TTerm<UCoefficientType>::GetCoefficient() const {
    return Coefficient;
}

template <typename UCoefficientType>
void TTerm<UCoefficientType>::SetCoefficient(UCoefficientType new_coeff) {
    Coefficient = new_coeff;
}

template <typename UCoefficientType>
TTerm<UCoefficientType> &TTerm<UCoefficientType>::operator*=(
    const TTerm<UCoefficientType> &other)
{
    TMonomial::operator*=(other);
    Coefficient *= other.Coefficient;
    return (*this);
}

template <typename UCoefficientType>
TTerm<UCoefficientType> TTerm<UCoefficientType>::operator*(
    const TTerm<UCoefficientType> &other) const
{
    TTerm<UCoefficientType> res(*this);
    res *= other;
    return res;
}

template <typename UCoefficientType>
TTerm<UCoefficientType> &TTerm<UCoefficientType>::operator/=(
    const TTerm<UCoefficientType> &other)
{
    TMonomial::operator/=(other);
    Coefficient /= other.Coefficient;
    return (*this);
}

template <typename UCoefficientType>
TTerm<UCoefficientType> TTerm<UCoefficientType>::operator/(
    const TTerm<UCoefficientType> &other) const
{
    TTerm<UCoefficientType> res(*this);
    res /= other;
    return res;
}

template <typename UCoefficientType>
TTerm<UCoefficientType> Lcm(
    const TTerm<UCoefficientType> &lhs,
    const TTerm<UCoefficientType> &rhs)
{
    return TTerm<UCoefficientType>(
        lhs.Coefficient * rhs.Coefficient,
        Lcm(static_cast<const TMonomial&>(lhs), static_cast<const TMonomial&>(rhs)));
}

}
