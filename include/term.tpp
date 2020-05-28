#ifndef INCLUDE_TERM_TPP
#define INCLUDE_TERM_TPP

#include "term.hpp"

#include <iostream>

namespace NLibPoly {

template<typename UCoefficientType>
TTerm<UCoefficientType>::TTerm(UCoefficientType coefficient, TMonomial monomial)
        : Coefficient(std::move(coefficient)), Monomial(std::move(monomial))
{
    if (coefficient == UCoefficientType(0)) {
        Monomial = TMonomial();
    }
}

template<typename UCoefficientType>
TTerm<UCoefficientType>::TTerm(
    UCoefficientType coefficient, std::initializer_list<std::pair<TIndex, TDegree>> init_list)
        : Coefficient(std::move(coefficient)), Monomial(init_list)
{
    if (coefficient == UCoefficientType(0)) {
        Monomial = TMonomial();
    }
}

template<typename UCoefficientType>
TTerm<UCoefficientType>::TTerm(std::initializer_list<std::pair<TIndex, TDegree>> init_list)
        : Coefficient(UCoefficientType(1)), Monomial(init_list)
{}

template<typename UCoefficientType>
const TMonomial& TTerm<UCoefficientType>::GetMonomial() const
{
    return Monomial;
}

template<typename UCoefficientType>
typename TTerm<UCoefficientType>::TConstCoefficientRef
TTerm<UCoefficientType>::GetCoefficient() const
{
    return Coefficient;
}

template<typename UCoefficientType>
void TTerm<UCoefficientType>::SetCoefficient(UCoefficientType coefficient)
{
    Coefficient = std::move(coefficient);
    if (Coefficient == UCoefficientType(0)) {
        Monomial = TMonomial();
    }
}

template<typename UCoefficientType>
typename TTerm<UCoefficientType>::TDegree TTerm<UCoefficientType>::GetDegree(TIndex index) const
{
    return Monomial.GetDegree(index);
}

template<typename UCoefficientType>
void TTerm<UCoefficientType>::SetDegree(TIndex index, TDegree degree)
{
    Monomial.SetDegree(index, degree);
}

template<typename UCoefficientType>
TTerm<UCoefficientType>& TTerm<UCoefficientType>::operator*=(const TTerm<UCoefficientType>& other)
{
    Monomial *= other.Monomial;
    Coefficient *= other.Coefficient;

    if (Coefficient == UCoefficientType(0)) {
        Monomial = TMonomial();
    }

    return *this;
}

template<typename UCoefficientType>
TTerm<UCoefficientType>& TTerm<UCoefficientType>::operator/=(const TTerm<UCoefficientType>& other)
{
    Monomial /= other.Monomial;
    Coefficient /= other.Coefficient;

    if (Coefficient == UCoefficientType(0)) {
        Monomial = TMonomial();
    }

    return *this;
}

template<typename UCoefficientType>
TTerm<UCoefficientType> Lcm(const TTerm<UCoefficientType>& lhs, const TTerm<UCoefficientType>& rhs)
{
    return TTerm<UCoefficientType>(
        lhs.Coefficient * rhs.Coefficient, Lcm(lhs.Monomial, rhs.Monomial));
}

template<typename UCoefficientType>
std::ostream& operator<<(std::ostream& out, const TTerm<UCoefficientType>& term)
{

    if (term.Coefficient == UCoefficientType(0)) {
        out << "0";
    } else {
        if (term.Coefficient == UCoefficientType(1)) {
            out << term.GetMonomial();
        } else {
            out << term.GetCoefficient() << " " << term.GetMonomial();
        }
    }

    return out;
}
}

#endif // INCLUDE_TERM_TPP
