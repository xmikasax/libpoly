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
    friend TTerm operator*(const TTerm& t1, const TTerm& t2)
    {
        TTerm res(t1);
        res *= t2;
        return res;
    }

    TTerm& operator/=(const TTerm& other);
    friend TTerm operator/(const TTerm& t1, const TTerm& t2)
    {
        TTerm res(t1);
        res /= t2;
        return res;
    }

    friend bool operator==(const TTerm& t1, const TTerm& t2)
    {
        return t1.Coefficient == t2.Coefficient && t1.Monomial == t2.Monomial;
    }

    friend bool operator!=(const TTerm& t1, const TTerm& t2)
    {
        return !(t1 == t2);
    }

    template<typename T>
    friend TTerm<T> Lcm(const TTerm<T>& a, const TTerm<T>& b);

private:
    UCoefficientType Coefficient = UCoefficientType(0);
    TMonomial Monomial;
};

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
