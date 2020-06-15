#include "algorithms.hpp"

#include "polynomial.hpp"
#include "term.hpp"
#include "utils.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> Reduce(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    for (auto term_iterator = lhs.rbegin(); term_iterator != lhs.rend(); ++term_iterator) {
        if (IsDivisibleBy(*term_iterator, rhs.Leader())) {
            return lhs - rhs * (*term_iterator / rhs.Leader());
        }
    }

    NUtils::Halt("Polynomial is irreducible");
}

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder> SPolynomial(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomial<UCoefficientType, UOrder>& rhs)
{
    auto lcm = Lcm(lhs.Leader(), rhs.Leader());

    return lhs * (lcm / lhs.Leader()) - rhs * (lcm / rhs.Leader());
}

template<typename UCoefficientType, typename UOrder>
TPolynomialSet<UCoefficientType, UOrder>
Buchberger(TPolynomialSet<UCoefficientType, UOrder> polynomial_set)
{
    std::vector<TPolynomial<UCoefficientType, UOrder>> current_set(
        polynomial_set.begin(), polynomial_set.end());

    TPolynomialSet<UCoefficientType, UOrder> res;

    for (auto& polynomial : current_set) {
        res.Insert(std::move(polynomial));
    }

    return res;
}

}
