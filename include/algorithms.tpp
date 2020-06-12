#include "algorithms.hpp"

#include "utils.hpp"

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>
Reduce(TPolynomial<UCoefficientType, UOrder> lhs, TPolynomial<UCoefficientType, UOrder> rhs)
{
    for (auto term_iterator = lhs.rbegin(); term_iterator != lhs.rend(); ++term_iterator) {
        if (IsDivisibleBy(*term_iterator, rhs.Leader())) {
            return lhs - rhs * (*term_iterator / rhs.Leader());
        }
    }

    NUtils::Halt("Polynomial is irreducible");
}

}
