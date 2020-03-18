#ifndef INCLUDE_MONOMIAL_HPP
#define INCLUDE_MONOMIAL_HPP

#include <cstdint>
#include <map>

namespace NLibPoly {

    class TMonomial {

        using TIndex = size_t;
        using TDegree = uint32_t;

    private:
        TDegree Degree;
        std::map<TIndex, TDegree> Variables;

    public:
        TMonomial() = default;
        TMonomial(TIndex index, TDegree degree);

        TDegree &operator[](TIndex index);
        TDegree &at(TIndex index);
        const TDegree &at(TIndex index) const;
    };

}

#endif // INCLUDE_MONOMIAL_HPP
