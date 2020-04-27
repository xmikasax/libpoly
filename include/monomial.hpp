#ifndef INCLUDE_MONOMIAL_HPP
#define INCLUDE_MONOMIAL_HPP

#include <cstdint>
#include <map>

namespace NLibPoly {

class TMonomial {
public:
    using TIndex = size_t;
    using TDegree = size_t;

public:
    TMonomial() = default;
    TMonomial(const TMonomial &other) = default;
    TMonomial(TIndex index, TDegree degree);
    TMonomial(const std::initializer_list<TDegree> &init_list);

    TDegree GetDegree(TIndex index) const;
    void SetDegree(TIndex index, TDegree degree);

    TMonomial &operator*=(const TMonomial &other);
    TMonomial operator*(const TMonomial &other) const;
    TMonomial &operator/=(const TMonomial &other);
    TMonomial operator/(const TMonomial &other) const;

    friend TMonomial Lcm(const TMonomial &a, const TMonomial &b);

private:
    std::map<TIndex, TDegree> Variables;
};

TMonomial Lcm(const TMonomial &a, const TMonomial &b);

}

#endif // INCLUDE_MONOMIAL_HPP
