#ifndef INCLUDE_TERM_HPP
#define INCLUDE_TERM_HPP

#include "monomial.hpp"

#include <utility>
#include <type_traits>

namespace NLibPoly {

template <typename UCoefficientType>
class TTerm {
public:
    using TIndex = TMonomial::TIndex;
    using TDegree = TMonomial::TDegree;
    using TConstCoefficientRef = std::conditional_t<
        std::is_arithmetic_v<UCoefficientType>,
        UCoefficientType,
        std::add_lvalue_reference_t<std::add_const_t<UCoefficientType>>
    >;

public:
    TTerm() = default;
    TTerm(UCoefficientType coefficient, TMonomial monomial);
    TTerm(
        UCoefficientType coefficient,
        std::initializer_list<std::pair<TIndex, TDegree>> init_list);
    TTerm(std::initializer_list<std::pair<TIndex, TDegree>> init_list);

    TConstCoefficientRef GetCoefficient() const;
    void SetCoefficient(TConstCoefficientRef coefficient);

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
    UCoefficientType Coefficient = UCoefficientType(0);
    TMonomial Monomial;
};

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
