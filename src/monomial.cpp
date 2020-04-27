#include "monomial.hpp"
#include <iostream>

namespace NLibPoly {

TMonomial::TMonomial(TIndex index, TDegree degree) {
    SetDegree(index, degree);
}

TMonomial::TMonomial(const std::initializer_list<TDegree> &init_list) {
    TIndex index(0);
    for (const auto &it : init_list) {
        SetDegree(index, it);
        ++index;
    }
}

TMonomial::TDegree TMonomial::GetDegree(TIndex index) const {
    const auto &it = Variables.find(index);
    if (it == Variables.end()) {
        return 0;
    }
    return it->second;
}

void TMonomial::SetDegree(TIndex index, TDegree degree) {
    Variables[index] = degree;
}

TMonomial &TMonomial::operator*=(const TMonomial &other) {
    for (auto it : other.Variables) {
        Variables[it.first] += it.second;
    }
    return *this;
}

TMonomial operator*(const TMonomial &m1, const TMonomial &m2) {
    TMonomial res(m1);
    return res *= m2;
}

TMonomial &TMonomial::operator/=(const TMonomial &other) {
    for (auto it : other.Variables) {
        Variables[it.first] -= it.second;
    }
    return *this;
}

TMonomial operator/(const TMonomial &m1, const TMonomial &m2) {
    TMonomial res(m1);
    return res /= m2;
}

TMonomial Lcm(const TMonomial &a, const TMonomial &b) {
    TMonomial res(a);
    for (auto it : b.Variables) {
        res.SetDegree(it.first, std::max(
            res.GetDegree(it.first),
            it.second
        ));
    }
    return res;
}

}
