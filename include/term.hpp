#ifndef INCLUDE_TERM_HPP
#define INCLUDE_TERM_HPP

#include "monomial.hpp"

#include <utility>

namespace NLibPoly {

template <typename UCoefficientType>
class TTerm {
public:
    using TIndex = TMonomial::TIndex;
    using TDegree = TMonomial::TDegree;

public:
    TTerm() = default;
    TTerm(UCoefficientType coefficient, TMonomial monomial);
    TTerm(
        UCoefficientType coefficient,
        const std::initializer_list<std::pair<TIndex, TDegree>> &init_list);
    TTerm(const std::initializer_list<std::pair<TIndex, TDegree>> &init_list);

    UCoefficientType GetCoefficient() const;
    void SetCoefficient(UCoefficientType coefficient);

    TDegree GetDegree(TIndex index) const;
    void SetDegree(TIndex index, TDegree degree);

    TTerm &operator*=(const TTerm &other);
    TTerm operator*(const TTerm &other) const;
    TTerm &operator/=(const TTerm &other);
    TTerm operator/(const TTerm &other) const;

    bool operator==(const TTerm &other) const;
    bool operator!=(const TTerm &other) const;

    template<typename T>
    friend TTerm<T> Lcm(
        const TTerm<T> &a,
        const TTerm<T> &b);

private:
    UCoefficientType Coefficient = UCoefficientType(1);
    TMonomial Monomial;
};

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
