#ifndef INCLUDE_MONOMIAL_HPP
#define INCLUDE_MONOMIAL_HPP

#include <cstdint>
#include <map>

namespace NLibPoly {

class TMonomial {
public:
    using TIndex = size_t;
    using TDegree = int32_t;

private:
    TDegree Degree;
    std::map<TIndex, TDegree> Variables;

public:
    TMonomial();
    TMonomial(const TMonomial &other) = default;
    TMonomial(TIndex index, TDegree degree);
    TMonomial(const std::initializer_list<TDegree> &init_list);

    virtual void Set(TIndex index, TDegree degree);

    virtual TDegree operator[](TIndex index);
    virtual const TDegree &At(TIndex index);
    virtual const TDegree &At(TIndex index) const;

    virtual const TDegree &GetDegree() const;

    TMonomial &operator*=(const TMonomial &other);
    TMonomial operator*(const TMonomial &other) const;
    TMonomial &operator/=(const TMonomial &other);
    TMonomial operator/(const TMonomial &other) const;

    friend TMonomial Lcm(const TMonomial &a, const TMonomial &b);
};

TMonomial Lcm(const TMonomial &a, const TMonomial &b);

}

#endif // INCLUDE_MONOMIAL_HPP
