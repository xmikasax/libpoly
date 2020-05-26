#ifndef INCLUDE_INTEGER_MOD_RING_HPP
#define INCLUDE_INTEGER_MOD_RING_HPP

#include <cstddef>

namespace NLibPoly {

template<size_t UModulo>
class TIntegerMod {
public:
    using TUnsignedInteger = size_t;

public:
    TIntegerMod() = default;
    TIntegerMod(TUnsignedInteger value);

    TIntegerMod& operator+=(const TIntegerMod& other);
    friend TIntegerMod operator+(const TIntegerMod& im1, const TIntegerMod& im2)
    {
        TIntegerMod integer_mod(im1);
        integer_mod += im2;
        return integer_mod;
    };

    TIntegerMod& operator-=(const TIntegerMod& other);
    friend TIntegerMod operator-(const TIntegerMod& im1, const TIntegerMod& im2)
    {
        TIntegerMod integer_mod(im1);
        integer_mod -= im2;
        return integer_mod;
    };

    TIntegerMod& operator*=(const TIntegerMod& other);
    friend TIntegerMod operator*(const TIntegerMod& im1, const TIntegerMod& im2)
    {
        TIntegerMod integer_mod(im1);
        integer_mod *= im2;
        return integer_mod;
    };

    TIntegerMod& operator/=(const TIntegerMod& other);
    friend TIntegerMod operator/(const TIntegerMod& im1, const TIntegerMod& im2)
    {
        TIntegerMod integer_mod(im1);
        integer_mod /= im2;
        return integer_mod;
    };

    friend bool operator==(const TIntegerMod& im1, const TIntegerMod& im2)
    {
        return im1.Value == im2.Value;
    }

    friend bool operator!=(const TIntegerMod& im1, const TIntegerMod& im2)
    {
        return !(im1 == im2);
    }

private:
    TUnsignedInteger Value = TUnsignedInteger(0);
};

}

#include "integer_mod.tpp"

#endif // INCLUDE_INTEGER_MOD_RING_HPP
