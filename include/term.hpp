#ifndef INCLUDE_TERM_HPP
#define INCLUDE_TERM_HPP

#include "monomial.hpp"

#include <utility>

namespace NLibPoly {

template <typename UCoefficientType>
class TTerm : public TMonomial {
public:
    TTerm() = default;
    TTerm(UCoefficientType coeff, TMonomial monomial);
    TTerm(const std::initializer_list<std::pair<TIndex, TDegree>> &init_list);

    UCoefficientType GetCoefficient() const;
    void SetCoefficient(UCoefficientType new_coeff);

    TTerm &operator*=(const TTerm &other);
    TTerm operator*(const TTerm &other) const;
    TTerm &operator/=(const TTerm &other);
    TTerm operator/(const TTerm &other) const;

    template<typename T>
    friend TTerm<T> Lcm(
        const TTerm<T> &a,
        const TTerm<T> &b);

private:
    UCoefficientType Coefficient = UCoefficientType(1);
};

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
