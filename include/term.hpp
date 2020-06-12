#ifndef INCLUDE_TERM_HPP
#define INCLUDE_TERM_HPP

#include "monomial.hpp"

#include <iostream>
#include <type_traits>

namespace NLibPoly {

template<typename UCoefficientType>
class TTerm {
public:
    using TIndex               = TMonomial::TIndex;
    using TDegree              = TMonomial::TDegree;
    using TConstCoefficientRef = std::conditional_t<
        std::is_arithmetic_v<UCoefficientType>,
        UCoefficientType,
        std::add_lvalue_reference_t<std::add_const_t<UCoefficientType>>>;

public:
    TTerm() = default;
    TTerm(UCoefficientType coefficient, TMonomial monomial);
    TTerm(
        UCoefficientType coefficient, std::initializer_list<std::pair<TIndex, TDegree>> init_list);
    TTerm(std::initializer_list<std::pair<TIndex, TDegree>> init_list);

    const TMonomial& GetMonomial() const;

    TConstCoefficientRef GetCoefficient() const;
    void SetCoefficient(UCoefficientType coefficient);

    TDegree GetDegree(TIndex index) const;
    void SetDegree(TIndex index, TDegree degree);

    TTerm& operator*=(const TTerm& other);
    TTerm& operator/=(const TTerm& other);

private:
    UCoefficientType Coefficient = UCoefficientType(0);
    TMonomial Monomial;
};

template<typename UCoefficientType>
TTerm<UCoefficientType>
operator*(const TTerm<UCoefficientType>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename UCoefficientType>
TTerm<UCoefficientType>
operator/(const TTerm<UCoefficientType>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename UCoefficientType>
bool operator==(const TTerm<UCoefficientType>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename UCoefficientType>
bool operator==(const TTerm<UCoefficientType>& lhs, const TTerm<UCoefficientType>& rhs);

template<typename T>
TTerm<T> Lcm(const TTerm<T>& lhs, const TTerm<T>& rhs);

template<typename T>
bool IsDivisibleBy(const TTerm<T>& lhs, const TTerm<T>& rhs);

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
