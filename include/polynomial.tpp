#include "polynomial.hpp"

#include <iostream>

namespace NLibPoly {

template<typename UCoefficientType, typename UOrder>
TPolynomial<UCoefficientType, UOrder>::TPolynomial(std::initializer_list<TTerm<UCoefficientType>> init_list)
    : Terms(init_list)
{}

template<typename UCoefficientType, typename UOrder>
bool TPolynomial<UCoefficientType, UOrder>::operator==(const TPolynomial &other) const {
    return Terms == other.Terms;
}

template<typename UCoefficientType, typename UOrder>
bool TPolynomial<UCoefficientType, UOrder>::operator!=(const TPolynomial &other) const {
    return !(*this == other);
}

template <typename UCoefficientType, typename UOrder>
std::ostream &operator<<(std::ostream &out, const TPolynomial<UCoefficientType, UOrder> &polynomial) {
    if (polynomial.begin() == polynomial.end()) {
        out << "0";
    } else {
        bool first = true;
        for (const auto &it : polynomial) {
            if (!first) {
                out << " + ";
            } else {
                first = false;
            }
            out << it;
        }
    }

    return out;
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TIterator
TPolynomial<UCoefficientType, UOrder>::begin() {
    return Terms.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::end() {
    return Terms.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::begin() const {
    return Terms.begin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::end() const {
    return Terms.end();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rbegin() {
    return Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rend() {
    return Terms.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rbegin() const {
    return Terms.rbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::rend() const {
    return Terms.rend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::cbegin() const {
    return Terms.cbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::cend() const {
    return Terms.cend();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::crbegin() const {
    return Terms.crbegin();
}

template<typename UCoefficientType, typename UOrder>
typename TPolynomial<UCoefficientType, UOrder>::TConstReverseIterator
TPolynomial<UCoefficientType, UOrder>::TPolynomial::crend() const {
    return Terms.crend();
}


}
