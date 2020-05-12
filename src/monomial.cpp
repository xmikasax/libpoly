#include "monomial.hpp"

#include <iostream>

#include "utils.hpp"

namespace NLibPoly {

TMonomial::TMonomial(TIndex index, TDegree degree) {
    SetDegree(index, degree);
}

TMonomial::TMonomial(std::initializer_list<std::pair<TIndex, TDegree>> init_list) {
    for (const auto &it : init_list) {
        SetDegree(it.first, it.second);
    }
}

TMonomial::TDegree TMonomial::GetDegree(TIndex index) const {
    const auto &it = Variables.find(index);
    if (it == Variables.end()) {
        return TDegree(0);
    }
    return it->second;
}

void TMonomial::SetDegree(TIndex index, TDegree degree) {
    if (degree == TDegree(0)) {
        Variables.erase(index);
    } else {
        Variables[index] = degree;
    }
}

// No need to check for zero degree
TMonomial &TMonomial::operator*=(const TMonomial &other) {
    for (const auto &it : other.Variables) {
        Variables[it.first] += it.second;
    }
    return *this;
}

TMonomial operator*(const TMonomial &lhs, const TMonomial &rhs) {
    TMonomial res(lhs);
    res *= rhs;
    return res;
}

TMonomial &TMonomial::operator/=(const TMonomial &other) {
    for (const auto &it : other.Variables) {
        TDegree degree = GetDegree(it.first);
        if (degree < it.second) {
            NUtils::Halt("Underflow while dividing monomials");
        }
        SetDegree(it.first, degree - it.second);
    }
    return *this;
}

TMonomial operator/(const TMonomial &lhs, const TMonomial &rhs) {
    TMonomial res(lhs);
    res /= rhs;
    return res;
}

bool operator==(const TMonomial &lhs, const TMonomial &rhs) {
    return lhs.Variables == rhs.Variables;
}

bool operator!=(const TMonomial &lhs, const TMonomial &rhs) {
    return !(lhs == rhs);
}

TMonomial Lcm(const TMonomial &lhs, const TMonomial &rhs) {
    TMonomial res(lhs);
    for (const auto &it : rhs.Variables) {
        res.SetDegree(it.first, std::max(
            res.GetDegree(it.first),
            it.second
        ));
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const TMonomial &monomial) {
    if (monomial.begin() == monomial.end()) {
        out << "0";
    } else {
        bool first = true;
        for (const auto &it : monomial) {
            if (!first) {
                out << " ";
            } else {
                first = false;
            }
            out << "x_{" << it.first << "}^{" << it.second << "}";
        }
    }

    return out;
}

TMonomial::TIterator TMonomial::begin() {
    return Variables.begin();
}

TMonomial::TIterator TMonomial::end() {
    return Variables.end();
}

TMonomial::TConstIterator TMonomial::begin() const {
    return Variables.begin();
}

TMonomial::TConstIterator TMonomial::end() const {
    return Variables.end();
}

TMonomial::TReverseIterator TMonomial::rbegin() {
    return Variables.rbegin();
}

TMonomial::TReverseIterator TMonomial::rend() {
    return Variables.rend();
}

TMonomial::TConstReverseIterator TMonomial::rbegin() const {
    return Variables.rbegin();
}

TMonomial::TConstReverseIterator TMonomial::rend() const {
    return Variables.rend();
}

TMonomial::TConstIterator TMonomial::cbegin() const {
    return Variables.cbegin();
}

TMonomial::TConstIterator TMonomial::cend() const {
    return Variables.cend();
}

TMonomial::TConstReverseIterator TMonomial::crbegin() const {
    return Variables.crbegin();
}

TMonomial::TConstReverseIterator TMonomial::crend() const {
    return Variables.crend();
}

}
