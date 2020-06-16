#include <iostream>

#include "algorithm.hpp"
#include "integer_mod.hpp"
#include "monomial.hpp"
#include "order.hpp"
#include "polynomial.hpp"
#include "polynomial_set.hpp"

constexpr size_t P = 127;

int main()
{
    using namespace NLibPoly;

    size_t polynomials_cnt = 0;
    TPolynomialSet<TIntegerMod<P>, TGradedReverseLexicographicOrder> set;

    std::cin >> polynomials_cnt;

    for (size_t i = 0; i < polynomials_cnt; ++i) {
        size_t terms_cnt = 0;
        TPolynomial<TIntegerMod<P>, TGradedReverseLexicographicOrder> polynomial;

        std::cin >> terms_cnt;

        for (size_t j = 0; j < terms_cnt; ++j) {
            char sign                                 = '+';
            TIntegerMod<P>::TInnerInteger coefficient = 0;
            size_t variables_cnt                      = 0;
            TTerm<TIntegerMod<P>> term;

            std::cin >> sign >> coefficient >> variables_cnt;

            if (sign == '+') {
                term.SetCoefficient(coefficient);
            } else {
                term.SetCoefficient(-coefficient);
            }

            for (size_t t = 0; t < variables_cnt; ++t) {
                TTerm<TIntegerMod<P>>::TIndex index   = 0;
                TTerm<TIntegerMod<P>>::TDegree degree = 0;

                std::cin >> index >> degree;

                term.SetDegree(index, degree);
            }

            polynomial += term;
        }

        set.Insert(polynomial);
    }

    auto res = AutoReduce(Buchberger(set));
    std::cout << res << "\n\n";
    std::cout << res.Size() << "\n";
}
