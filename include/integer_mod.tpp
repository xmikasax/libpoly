#ifndef INCLUDE_INTEGER_MOD_TPP
#define INCLUDE_INTEGER_MOD_TPP

#include "integer_mod.hpp"

#include "utils.hpp"

namespace NLibPoly {

template<size_t UModulo>
TIntegerMod<UModulo>::TIntegerMod(TUnsignedInteger value) : Value(value % UModulo)
{}

template<size_t UModulo>
TIntegerMod<UModulo> TIntegerMod<UModulo>::operator-() const
{
    return TIntegerMod((-Value + UModulo) % UModulo);
}

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator+=(const TIntegerMod& other)
{
    Value = (Value + other.Value) % UModulo;
    return *this;
}

template<size_t UModulo>
TIntegerMod<UModulo> operator+(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs)
{
    TIntegerMod integer_mod(lhs);
    integer_mod += rhs;
    return integer_mod;
};

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator-=(const TIntegerMod& other)
{
    Value = ((Value - other.Value) % UModulo + UModulo) % UModulo;
    return *this;
}

template<size_t UModulo>
TIntegerMod<UModulo> operator-(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs)
{
    TIntegerMod integer_mod(lhs);
    integer_mod -= rhs;
    return integer_mod;
};

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator*=(const TIntegerMod& other)
{
    Value = (Value * other.Value) % UModulo;
    return *this;
}

template<size_t UModulo>
TIntegerMod<UModulo> operator*(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs)
{
    TIntegerMod integer_mod(lhs);
    integer_mod *= rhs;
    return integer_mod;
};

namespace {
template<size_t UModulo>
TIntegerMod<UModulo> Power(TIntegerMod<UModulo> value, size_t power)
{
    if (power == 0) {
        return TIntegerMod<UModulo>(1);
    } else if (power % 2 == 1) {
        return value * Power(value, power - 1);
    } else {
        auto result = Power(value, power / 2);
        return result * result;
    }
}
}

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator/=(const TIntegerMod& other)
{
    if (other.Value == TUnsignedInteger(0)) {
        NUtils::Halt("Division by zero");
    }

    *this *= Power(other, UModulo - 2);
    return *this;
}

template<size_t UModulo>
TIntegerMod<UModulo> operator/(const TIntegerMod<UModulo>& lhs, const TIntegerMod<UModulo>& rhs)
{
    TIntegerMod integer_mod(lhs);
    integer_mod /= rhs;
    return integer_mod;
};

template<size_t UOutputModulo>
std::ostream& operator<<(std::ostream& out, const TIntegerMod<UOutputModulo>& im)
{
    out << im.Value;
    return out;
}

}

#endif // INCLUDE_INTEGER_MOD_TPP
