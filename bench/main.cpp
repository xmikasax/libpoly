#include <chrono>
#include <iostream>

#include "algorithm.hpp"
#include "integer_mod.hpp"
#include "monomial.hpp"
#include "order.hpp"
#include "polynomial.hpp"
#include "polynomial_set.hpp"

class TTimer {
private:
    std::chrono::high_resolution_clock::time_point Timer;

public:
    TTimer() : Timer(std::chrono::high_resolution_clock::now()) {}

    double GetDuration() const
    {
        std::chrono::high_resolution_clock::time_point current_time =
            std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<double>>(current_time - Timer)
            .count();
    }
};

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

    TTimer timer;
    auto res = AutoReduce(Buchberger(set));
    std::cout << timer.GetDuration() << "\n";
}
