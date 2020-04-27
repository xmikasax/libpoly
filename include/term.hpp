#ifndef INCLUDE_TERM_HPP
#define INCLUDE_TERM_HPP

#include "monomial.hpp"

#include <utility>

namespace NLibPoly {

template <typename TCoefficientType>
class TTerm : public TMonomial {
public:
    TTerm() = default;
    TTerm(TCoefficientType coeff, TMonomial monomial);
    TTerm(const std::initializer_list<std::pair<TIndex, TDegree>> &init_list);

    TCoefficientType GetCoefficient() const;
    void SetCoefficient(TCoefficientType new_coeff);

    TTerm &operator*=(const TTerm &other);
    TTerm operator*(const TTerm &other) const;
    TTerm &operator/=(const TTerm &other);
    TTerm operator/(const TTerm &other) const;

    template<typename T>
    friend TTerm<T> Lcm(
        const TTerm<T> &a,
        const TTerm<T> &b);

private:
    TCoefficientType Coefficient = TCoefficientType(1);
};

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
