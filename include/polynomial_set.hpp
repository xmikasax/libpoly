#ifndef INCLUDE_POLYNOMIAL_SET_HPP
#define INCLUDE_POLYNOMIAL_SET_HPP

#include "polynomial.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
class TPolynomialSet {
public:
    using TContainer            = std::set<TPolynomial<UCoefficientType, UOrder>>;
    using TIterator             = typename TContainer::iterator;
    using TConstIterator        = typename TContainer::const_iterator;
    using TReverseIterator      = typename TContainer::reverse_iterator;
    using TConstReverseIterator = typename TContainer::const_reverse_iterator;

public:
    TPolynomialSet() = default;

    size_t Size() const;

    template<class UPolynomial>
    void Insert(UPolynomial&& polynomial);

    template<class UPolynomial>
    void Erase(UPolynomial&& polynomial);

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
    TContainer Polynomials;
};

template<typename UCoefficientType, typename UOrder>
std::ostream&
operator<<(std::ostream& out, const TPolynomialSet<UCoefficientType, UOrder>& polynomial_set);

}

#include "polynomial_set.tpp"

#endif // INCLUDE_POLYNOMIAL_SET_HPP
