#include "polynomial.hpp"

#include <iostream>

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
    for (const auto& it : other) {
        auto term_iterator = Terms.lower_bound(it);
        if (*term_iterator != it) {
            Terms.insert(term_iterator, it);
        } else {
            auto value = std::move(*term_iterator);
            value.SetCoefficient(value.GetCoefficient() + it.GetCoefficient());
            auto next_iterator = Terms.erase(term_iterator);
            if (value.GetCoefficient() != UCoefficientType(0)) {
                Terms.insert(next_iterator, std::move(value));
            }
        }
    }

    return *this;
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>&
TPolynomial<UCoefficientType, UOrder>::operator-=(const TPolynomial& other)
{
    for (const auto& it : other) {
        auto term_iterator = Terms.lower_bound(it);
        if (*term_iterator != it) {
            Terms.insert(term_iterator, { -it.GetCoefficient(), it.GetMonomial() });
        } else {
            auto value = std::move(*term_iterator);
            value.SetCoefficient(value.GetCoefficient() - it.GetCoefficient());
            auto next_iterator = Terms.erase(term_iterator);
            if (value.GetCoefficient() != UCoefficientType(0)) {
                Terms.insert(next_iterator, std::move(value));
            }
        }
    }

    return *this;
}

template<typename UCoefficientType, typename UOrder>
std::ostream& operator<<(std::ostream& out, const TPolynomial<UCoefficientType, UOrder>& polynomial)
{
    if (polynomial.begin() == polynomial.end()) {
        out << "0";
    } else {
        bool first = true;
        for (auto it = polynomial.rbegin(); it != polynomial.rend(); ++it) {
            if (!first) {
                out << " + ";
            } else {
                first = false;
            }
            out << *it;
        }
    }

    return out;
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TIterator
TPolynomial<UCoefficientType, UOrder>::begin()
{
    return Terms.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::end()
{
    return Terms.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::begin() const
{
    return Terms.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::end() const
{
    return Terms.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rbegin()
{
    return Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rend()
{
    return Terms.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rbegin() const
{
    return Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rend() const
{
    return Terms.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::cbegin() const
{
    return Terms.cbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::cend() const
{
    return Terms.cend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::crbegin() const
{
    return Terms.crbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::crend() const
{
    return Terms.crend();
}

}
