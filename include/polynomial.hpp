#ifndef INCLUDE_POLYNOMIAL_HPP
#define INCLUDE_POLYNOMIAL_HPP

#include <algorithm>
#include <iostream>
#include <set>

#include "term.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
class TPolynomial {
public:
    using TContainer            = std::set<TTerm<UCoefficientType>, UOrder>;
    using TIterator             = typename TContainer::iterator;
    using TConstIterator        = typename TContainer::const_iterator;
    using TReverseIterator      = typename TContainer::reverse_iterator;
    using TConstReverseIterator = typename TContainer::const_reverse_iterator;

public:
    TPolynomial() = default;
    TPolynomial(std::initializer_list<TTerm<UCoefficientType>> init_list);

    size_t Size() const;
    size_t size() const
    {
        return Size();
    }

    TPolynomial& operator+=(const TPolynomial& other);
    TPolynomial& operator+=(const TTerm<UCoefficientType>& other);
    TPolynomial& operator-=(const TPolynomial& other);
    TPolynomial& operator-=(const TTerm<UCoefficientType>& other);
    TPolynomial& operator*=(const TTerm<UCoefficientType>& other);

    friend bool operator==(const TPolynomial& lhs, const TPolynomial& rhs)
    {
        return lhs.Terms == rhs.Terms;
    }

    friend bool operator!=(const TPolynomial& lhs, const TPolynomial& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const TPolynomial& lhs, const TPolynomial& rhs)
    {
        return std::lexicographical_compare(
            lhs.Terms.begin(), lhs.Terms.end(), rhs.Terms.begin(), rhs.Terms.end(), UOrder());
    }

    const TTerm<UCoefficientType>& Leader() const;

    TIterator begin();
    TIterator end();
    TConstIterator begin() const;
    TConstIterator end() const;
    TReverseIterator rbegin();
    TReverseIterator rend();
    TConstReverseIterator rbegin() const;
    TConstReverseIterator rend() const;
    TConstIterator cbegin() const;
    TConstIterator cend() const;
    TConstReverseIterator crbegin() const;
    TConstReverseIterator crend() const;

private:
    TContainer Terms;
};

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> operator+(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator+(const TPolynomial<UCoefficientType, UOrder>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator+(const TTerm<UCoefficientType>& lhs, const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> operator-(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator-(const TPolynomial<UCoefficientType, UOrder>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator-(const TTerm<UCoefficientType>& lhs, const TPolynomial<UCoefficientType, UOrder>& rhs);

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
operator*(const TPolynomial<UCoefficientType, UOrder>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename UCoefficientType, typename UOrder>
std::ostream&
operator<<(std::ostream& out, const TPolynomial<UCoefficientType, UOrder>& polynomial);

template<typename UCoefficientType, typename UOrder>
bool IsReducibleBy(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs);

}

#include "polynomial.tpp"

#endif // INCLUDE_POLYNOMIAL_HPP
