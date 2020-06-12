#ifndef INCLUDE_MONOMIAL_HPP
#define INCLUDE_MONOMIAL_HPP

#include <cstdint>
#include <iostream>
#include <map>

namespace NLibPoly {

class TMonomial {
public:
    using TIndex                = size_t;
    using TDegree               = size_t;
    using TContainer            = std::map<TIndex, TDegree>;
    using TIterator             = TContainer::iterator;
    using TConstIterator        = TContainer::const_iterator;
    using TReverseIterator      = TContainer::reverse_iterator;
    using TConstReverseIterator = TContainer::const_reverse_iterator;

public:
    TMonomial() = default;
    TMonomial(TIndex index, TDegree degree);
    TMonomial(std::initializer_list<std::pair<TIndex, TDegree>> init_list);

    TDegree GetDegree(TIndex index) const;
    void SetDegree(TIndex index, TDegree degree);

    TMonomial& operator*=(const TMonomial& other);
    TMonomial& operator/=(const TMonomial& other);

    friend bool operator==(const TMonomial& lhs, const TMonomial& rhs);
    friend bool operator!=(const TMonomial& lhs, const TMonomial& rhs);

    friend TMonomial Lcm(const TMonomial& lhs, const TMonomial& rhs);

    friend std::ostream& operator<<(std::ostream& out, const TMonomial& monomial);

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
    TContainer Variables;
};

TMonomial operator*(const TMonomial& lhs, const TMonomial& m2);
TMonomial operator/(const TMonomial& lhs, const TMonomial& m2);
bool operator==(const TMonomial& lhs, const TMonomial& m2);
bool operator!=(const TMonomial& lhs, const TMonomial& m2);

TMonomial Lcm(const TMonomial& a, const TMonomial& b);
bool IsDivisibleBy(const TMonomial& lhs, const TMonomial& rhs);

}

#include "monomial.tpp"

#endif // INCLUDE_MONOMIAL_HPP
