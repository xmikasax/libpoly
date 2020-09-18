#ifndef INCLUDE_INTEGER_MOD_RING_HPP
#define INCLUDE_INTEGER_MOD_RING_HPP

#include <cstddef>

namespace NLibPoly {

template<long long UModulo>
class TIntegerMod {

    static_assert(UModulo > 1);

public:
    using TInnerInteger = long long;

public:
    TIntegerMod() = default;
    TIntegerMod(TInnerInteger value);

    TIntegerMod operator-() const;
    TIntegerMod& operator+=(const TIntegerMod& other);
    TIntegerMod& operator-=(const TIntegerMod& other);
    TIntegerMod& operator*=(const TIntegerMod& other);
    TIntegerMod& operator/=(const TIntegerMod& other);

    friend bool operator==(const TIntegerMod& lhs, const TIntegerMod& rhs)
    {
        return lhs.Value == rhs.Value;
    }

    friend bool operator!=(const TIntegerMod& lhs, const TIntegerMod& rhs)
    {
        return !(lhs == rhs);
    }

    template<long long UOutputModulo>
    friend std::ostream& operator<<(std::ostream& out, const TIntegerMod<UOutputModulo>& im);

private:
    TInnerInteger Value = TInnerInteger(0);
};

template<long long UModulo>
TIntegerMod<UModulo> operator-(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

template<long long UModulo>
TIntegerMod<UModulo> operator+(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

template<long long UModulo>
TIntegerMod<UModulo> operator*(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

template<long long UModulo>
TIntegerMod<UModulo> operator/(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

}

#include "integer_mod.tpp"

#endif // INCLUDE_INTEGER_MOD_RING_HPP
