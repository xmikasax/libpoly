#include "integer_mod.hpp"

#include "utils.hpp"

namespace NLibPoly {

template<size_t UModulo>
TIntegerMod<UModulo>::TIntegerMod(TUnsignedInteger value) : Value(value % UModulo)
{}

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator+=(const TIntegerMod& other)
{
    Value = (Value + other.Value) % UModulo;
    return *this;
}

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator-=(const TIntegerMod& other)
{
    Value = ((Value - other.Value) % UModulo + UModulo) % UModulo;
    return *this;
}

template<size_t UModulo>
TIntegerMod<UModulo>& TIntegerMod<UModulo>::operator*=(const TIntegerMod& other)
{
    Value = (Value * other.Value) % UModulo;
    return *this;
}

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

}
