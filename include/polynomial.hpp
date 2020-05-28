#ifndef INCLUDE_POLYNOMIAL_HPP
#define INCLUDE_POLYNOMIAL_HPP

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
    friend TPolynomial operator+(const TPolynomial& p1, const TPolynomial& p2)
    {
        TPolynomial res(p1);
        res += p2;
        return res;
    }
    TPolynomial& operator+=(const TTerm<UCoefficientType>& other);
    friend TPolynomial operator+(const TPolynomial& p, const TTerm<UCoefficientType>& t)
    {
        TPolynomial res(p);
        res += t;
        return res;
    }
    friend TPolynomial operator+(const TTerm<UCoefficientType>& t, const TPolynomial& p)
    {
        TPolynomial res(p);
        res += t;
        return res;
    }

    TPolynomial& operator-=(const TPolynomial& other);
    friend TPolynomial operator-(const TPolynomial& p1, const TPolynomial& p2)
    {
        TPolynomial res(p1);
        res -= p2;
        return res;
    }
    TPolynomial& operator-=(const TTerm<UCoefficientType>& other);
    friend TPolynomial operator-(const TPolynomial& p, const TTerm<UCoefficientType>& t)
    {
        TPolynomial res(p);
        res -= t;
        return res;
    }
    friend TPolynomial operator-(const TTerm<UCoefficientType>& t, const TPolynomial& p)
    {
        TPolynomial res(p);
        res -= t;
        return res;
    }

    friend bool operator==(const TPolynomial& p1, const TPolynomial& p2)
    {
        return p1.Terms == p2.Terms;
    }

    friend bool operator!=(const TPolynomial& p1, const TPolynomial& p2)
    {
        return !(p1 == p2);
    }

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

}

#include "polynomial.tpp"

#endif // INCLUDE_POLYNOMIAL_HPP
