#include "polynomial_set.hpp"

#include <utility>

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
size_t TPolynomialSet<UCoefficientType, UOrder>::Size() const
{
    return Polynomials.size();
}

template<typename UCoefficientType, typename UOrder>
template<class UPolynomial>
void TPolynomialSet<UCoefficientType, UOrder>::Insert(UPolynomial&& polynomial)
{
    Polynomials.insert(std::forward<UPolynomial>(polynomial));
}

template<typename UCoefficientType, typename UOrder>
template<class UPolynomial>
void TPolynomialSet<UCoefficientType, UOrder>::Erase(UPolynomial&& polynomial)
{
    Polynomials.erase(std::forward<UPolynomial>(polynomial));
}

template<typename UCoefficientType, typename UOrder>
std::ostream&
operator<<(std::ostream& out, const TPolynomialSet<UCoefficientType, UOrder>& polynomial_set)
{
    out << "[";

    bool first = true;
    for (const auto& polynomial : polynomial_set) {
        if (!first) {
            out << ", ";
        } else {
            first = false;
        }
        out << polynomial;
    }

    out << "]";

    return out;
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TIterator
TPolynomialSet<UCoefficientType, UOrder>::begin()
{
    return Polynomials.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TIterator
TPolynomialSet<UCoefficientType, UOrder>::end()
{
    return Polynomials.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstIterator
TPolynomialSet<UCoefficientType, UOrder>::begin() const
{
    return Polynomials.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstIterator
TPolynomialSet<UCoefficientType, UOrder>::end() const
{
    return Polynomials.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TReverseIterator
TPolynomialSet<UCoefficientType, UOrder>::rbegin()
{
    return Polynomials.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TReverseIterator
TPolynomialSet<UCoefficientType, UOrder>::rend()
{
    return Polynomials.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomialSet<UCoefficientType, UOrder>::rbegin() const
{
    return Polynomials.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomialSet<UCoefficientType, UOrder>::rend() const
{
    return Polynomials.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstIterator
TPolynomialSet<UCoefficientType, UOrder>::cbegin() const
{
    return Polynomials.cbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstIterator
TPolynomialSet<UCoefficientType, UOrder>::cend() const
{
    return Polynomials.cend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomialSet<UCoefficientType, UOrder>::crbegin() const
{
    return Polynomials.crbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomialSet<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomialSet<UCoefficientType, UOrder>::crend() const
{
    return Polynomials.crend();
}

}
