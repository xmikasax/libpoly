#include "monomial.hpp"

#include <utility>

#include "utils.hpp"

namespace NLibPoly {

TMonomial::TMonomial(TIndex index, TDegree degree) {
    SetDegree(index, degree);
}

TMonomial::TMonomial(const std::initializer_list<std::pair<TIndex, TDegree>> &init_list) {
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

TMonomial operator*(const TMonomial &m1, const TMonomial &m2) {
    TMonomial res(m1);
    return res *= m2;
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

TMonomial operator/(const TMonomial &m1, const TMonomial &m2) {
    TMonomial res(m1);
    return res /= m2;
}

bool operator==(const TMonomial &m1, const TMonomial &m2) {
    return m1.Variables == m2.Variables;
}

bool operator!=(const TMonomial &m1, const TMonomial &m2) {
    return !(m1 == m2);
}

TMonomial Lcm(const TMonomial &a, const TMonomial &b) {
    TMonomial res(a);
    for (const auto &it : b.Variables) {
        res.SetDegree(it.first, std::max(
            res.GetDegree(it.first),
            it.second
        ));
    }
    return res;
}

}
