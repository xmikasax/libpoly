#include "algorithm.hpp"

#include <vector>

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
TPolynomial<UCoefficientType, UOrder> Reduce(
    const TPolynomial<UCoefficientType, UOrder>& lhs,
    const TPolynomialSet<UCoefficientType, UOrder>& rhs)
{
    bool reducing = true;
    auto res      = lhs;

    while (reducing) {
        reducing = false;

        for (const auto& polynomial : rhs) {
            try {
                res = Reduce(res, polynomial);

                if (res.Size() == 0) {
                    reducing = false;
                    break;
                }

                reducing = true;
            } catch (const NUtils::TLibPolyException&) {
            }
        }
    }

    return res;
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

    std::vector<TPolynomial<UCoefficientType, UOrder>> current_set_vector(
        polynomial_set.begin(), polynomial_set.end());

    for (size_t i = 0; i < current_set_vector.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            auto spolynomial = SPolynomial(current_set_vector[i], current_set_vector[j]);
            auto remainder   = Reduce(spolynomial, polynomial_set);

            // std::cout << "(" << current_set_vector[i] << ", " << current_set_vector[j] << ") => "
            //           << spolynomial << " => " << remainder << "\n\n";

            if (remainder.Size() > 0) {
                polynomial_set.Insert(remainder);
                current_set_vector.push_back(std::move(remainder));
            }
        }
    }

    return polynomial_set;
}

template<typename UCoefficientType, typename UOrder>
TPolynomialSet<UCoefficientType, UOrder>
AutoReduce(TPolynomialSet<UCoefficientType, UOrder> polynomial_set)
{
    auto res = polynomial_set;

    bool reducing = true;

    while (reducing) {
        reducing = false;

        for (const auto& polynomial : polynomial_set) {
            res.Erase(polynomial);

            auto reduced = Reduce(polynomial, res);

            if (reduced.Size() > 0) {
                res.Insert(reduced);

                if (reduced != polynomial) {
                    reducing = true;
                }
            }
        }

        polynomial_set = res;
    }

    for (const auto& polynomial : polynomial_set) {
        res.Erase(polynomial);

        const auto& leader = polynomial.Leader();

        res.Insert(
            polynomial
            * TTerm<UCoefficientType>(UCoefficientType(1) / leader.GetCoefficient(), {}));
    }

    return res;
}

}
