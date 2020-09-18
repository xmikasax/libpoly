#ifndef INCLUDE_INTEGER_MOD_RING_HPP
#define INCLUDE_INTEGER_MOD_RING_HPP

#include <cstddef>

namespace NLibPoly {

// TODO: enable if UModulo > 1
template<size_t UModulo>
class TIntegerMod {
public:
    using TUnsignedInteger = size_t;

public:
    TIntegerMod() = default;
    TIntegerMod(TUnsignedInteger value);

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

    template<size_t UOutputModulo>
    friend std::ostream& operator<<(std::ostream& out, const TIntegerMod<UOutputModulo>& im);

private:
    TUnsignedInteger Value = TUnsignedInteger(0);
};

template<size_t UModulo>
TIntegerMod<UModulo> operator-(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

template<size_t UModulo>
TIntegerMod<UModulo> operator+(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

template<size_t UModulo>
TIntegerMod<UModulo> operator*(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

template<size_t UModulo>
TIntegerMod<UModulo> operator/(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs);

}

#include "integer_mod.tpp"

#endif // INCLUDE_INTEGER_MOD_RING_HPP
