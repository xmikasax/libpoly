#ifndef INCLUDE_MONOMIAL_HPP
#define INCLUDE_MONOMIAL_HPP

#include <cstdint>
#include <map>
#include <utility>

namespace NLibPoly {

class TMonomial {
public:
    using TIndex = size_t;
    using TDegree = size_t;

public:
    TMonomial() = default;
    TMonomial(TIndex index, TDegree degree);
    TMonomial(std::initializer_list<std::pair<TIndex, TDegree>> init_list);

    TDegree GetDegree(TIndex index) const;
    void SetDegree(TIndex index, TDegree degree);

    TMonomial &operator*=(const TMonomial &other);
    friend TMonomial operator*(const TMonomial &m1, const TMonomial &m2);
    TMonomial &operator/=(const TMonomial &other);
    friend TMonomial operator/(const TMonomial &m1, const TMonomial &m2);

    friend bool operator==(const TMonomial &m1, const TMonomial &m2);
    friend bool operator!=(const TMonomial &m1, const TMonomial &m2);

    friend TMonomial Lcm(const TMonomial &a, const TMonomial &b);

private:
    std::map<TIndex, TDegree> Variables;
};

TMonomial Lcm(const TMonomial &a, const TMonomial &b);
TMonomial operator*(const TMonomial &m1, const TMonomial &m2);
TMonomial operator/(const TMonomial &m1, const TMonomial &m2);
bool operator==(const TMonomial &m1, const TMonomial &m2);
bool operator!=(const TMonomial &m1, const TMonomial &m2);

}

#endif // INCLUDE_MONOMIAL_HPP
