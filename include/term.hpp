#ifndef INCLUDE_TERM_HPP
#define INCLUDE_TERM_HPP

#include "monomial.hpp"

namespace NLibPoly {

template <typename TCoefficientType>
class TTerm : public TMonomial {
public:
    TTerm();
    TTerm(const TTerm<TCoefficientType> &other) = default;
    TTerm(TCoefficientType coeff, TMonomial monomial);
    TTerm(const std::initializer_list<TDegree> &init_list);

    TCoefficientType GetCoefficient() const;
    void SetCoefficient(TCoefficientType new_coeff);

    TTerm<TCoefficientType> &operator*=(const TTerm<TCoefficientType> &other);
    TTerm<TCoefficientType> operator*(const TTerm<TCoefficientType> &other) const;
    TTerm<TCoefficientType> &operator/=(const TTerm<TCoefficientType> &other);
    TTerm<TCoefficientType> operator/(const TTerm<TCoefficientType> &other) const;

    template<typename T>
    friend TTerm<T> Lcm(
        const TTerm<T> &a,
        const TTerm<T> &b);

private:
    TCoefficientType Coefficient;
};

}

#include "term.tpp"

#endif // INCLUDE_TERM_HPP
