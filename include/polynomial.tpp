#ifndef INCLUDE_POLYNOMIAL_TPP
#define INCLUDE_POLYNOMIAL_TPP

#include "polynomial.hpp"
#include "term.hpp"

#include <iostream>

#include "utils.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>::TPolynomial(
    std::initializer_list<TTerm<UCoefficientType>> init_list)
        : Terms(init_list)
{
    if (Terms.size() == 1 && Terms.begin()->GetCoefficient() == UCoefficientType(0)) {
        Terms.clear();
    }
}

template<typename UCoefficientType, typename UOrder>
size_t TPolynomial<UCoefficientType, UOrder>::Size() const
{
    return Terms.size();
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>&
TPolynomial<UCoefficientType, UOrder>::operator+=(const TPolynomial& other)
{
    for (const auto& term : other) {
        auto term_iterator = Terms.lower_bound(term);
        if (UOrder::Compare(*term_iterator, term)) {
            Terms.insert(term_iterator, term);
        } else {
            auto value = std::move(*term_iterator);
            value.SetCoefficient(value.GetCoefficient() + term.GetCoefficient());
            auto next_iterator = Terms.erase(term_iterator);
            if (value.GetCoefficient() != UCoefficientType(0)) {
                Terms.insert(next_iterator, std::move(value));
            }
        }
    }

    return *this;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> operator+(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    TPolynomial res(lhs);
    res += rhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>&
TPolynomial<UCoefficientType, UOrder>::operator+=(const TTerm<UCoefficientType>& other)
{
    *this += TPolynomial({ other });

    return *this;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator+(const TPolynomial<UCoefficientType, UOrder>& lhs, const TTerm<UCoefficientType>& rhs)
{
    TPolynomial res(lhs);
    res += rhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator+(const TTerm<UCoefficientType>& lhs, const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    TPolynomial res(rhs);
    res += lhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>&
TPolynomial<UCoefficientType, UOrder>::operator-=(const TPolynomial& other)
{
    for (const auto& term : other) {
        auto term_iterator = Terms.lower_bound(term);
        if (UOrder::Compare(*term_iterator, term)) {
            Terms.insert(term_iterator, { -term.GetCoefficient(), term.GetMonomial() });
        } else {
            auto value = std::move(*term_iterator);
            value.SetCoefficient(value.GetCoefficient() - term.GetCoefficient());
            auto next_iterator = Terms.erase(term_iterator);
            if (value.GetCoefficient() != UCoefficientType(0)) {
                Terms.insert(next_iterator, std::move(value));
            }
        }
    }

    return *this;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> operator-(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    TPolynomial res(lhs);
    res -= rhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>&
TPolynomial<UCoefficientType, UOrder>::operator-=(const TTerm<UCoefficientType>& other)
{
    *this -= TPolynomial({ other });

    return *this;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator-(const TPolynomial<UCoefficientType, UOrder>& lhs, const TTerm<UCoefficientType>& rhs)
{
    TPolynomial res(lhs);
    res -= rhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator-(const TTerm<UCoefficientType>& lhs, const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    TPolynomial res(rhs);
    res -= lhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>&
TPolynomial<UCoefficientType, UOrder>::operator*=(const TTerm<UCoefficientType>& other)
{
    TPolynomial res;

    for (const auto& term : *this) {
        res += term * other;
    }

    *this = std::move(res);

    return *this;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator*(const TPolynomial<UCoefficientType, UOrder>& lhs, const TTerm<UCoefficientType>& rhs)
{
    TPolynomial res(lhs);
    res *= rhs;
    return res;
}

template<typename UCoefficientType, typename UOrder>
std::ostream& operator<<(std::ostream& out, const TPolynomial<UCoefficientType, UOrder>& polynomial)
{
    if (polynomial.begin() == polynomial.end()) {
        out << "0";
    } else {
        bool first = true;
        for (auto term_iterator = polynomial.rbegin(); term_iterator != polynomial.rend();
             ++term_iterator) {
            if (!first) {
                out << " + ";
            } else {
                first = false;
            }
            out << *term_iterator;
        }
    }

    return out;
}

template<typename UCoefficientType, typename UOrder>
bool IsReducibleBy(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    for (const auto& term : lhs) {
        if (IsDivisibleBy(term, rhs.Leader())) {
            return true;
        }
    }

    return false;
}

template<typename UCoefficientType, typename UOrder>
const TTerm<UCoefficientType>& TPolynomial<UCoefficientType, UOrder>::Leader() const
{
    if (Size() <= 0) {
        NUtils::Halt("Polynomial is zero");
    }
    return *Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TIterator
TPolynomial<UCoefficientType, UOrder>::begin()
{
    return Terms.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TIterator
TPolynomial<UCoefficientType, UOrder>::end()
{
    return Terms.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::begin() const
{
    return Terms.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::end() const
{
    return Terms.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TReverseIterator
TPolynomial<UCoefficientType, UOrder>::rbegin()
{
    return Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TReverseIterator
TPolynomial<UCoefficientType, UOrder>::rend()
{
    return Terms.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::rbegin() const
{
    return Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::rend() const
{
    return Terms.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::cbegin() const
{
    return Terms.cbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::cend() const
{
    return Terms.cend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::crbegin() const
{
    return Terms.crbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::crend() const
{
    return Terms.crend();
}

}

#endif // INCLUDE_POLYNOMIAL_TPP
