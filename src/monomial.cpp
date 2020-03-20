#include "monomial.hpp"
#include <iostream>

namespace NLibPoly {

TMonomial::TMonomial()
    : Degree(0) {}

TMonomial::TMonomial(TIndex index, TDegree degree)
    : TMonomial()
{
    Set(index, degree);
}

TMonomial::TMonomial(const std::initializer_list<TDegree> &init_list)
    : TMonomial()
{
    TIndex index(0);
    for (const auto &it : init_list) {
        Set(index, it);
        ++index;
    }
}

void TMonomial::Set(TIndex index, TDegree degree) {
    TDegree diff = degree - Variables[index];
    Variables[index] += diff;
    Degree += diff;
}

TMonomial::TDegree TMonomial::operator[](TIndex index) {
    return Variables[index];
}

const TMonomial::TDegree &TMonomial::At(TIndex index) {
    return Variables.at(index);
}

const TMonomial::TDegree &TMonomial::At(TIndex index) const {
    return Variables.at(index);
}

const TMonomial::TDegree &TMonomial::GetDegree() const {
    return Degree;
}

TMonomial &TMonomial::operator*=(const TMonomial &other) {
    for (auto it : other.Variables) {
        Variables[it.first] += it.second;
        Degree += it.second;
    }
    return *this;
}

TMonomial TMonomial::operator*(const TMonomial &other) const {
    TMonomial res(*this);
    return res *= other;
}

TMonomial &TMonomial::operator/=(const TMonomial &other) {
    for (auto it : other.Variables) {
        Variables[it.first] -= it.second;
        Degree -= it.second;
    }
    return *this;
}

TMonomial TMonomial::operator/(const TMonomial &other) const {
    TMonomial res(*this);
    return res /= other;
}

TMonomial Lcm(const TMonomial &a, const TMonomial &b) {
    TMonomial res(a);
    for (auto it : b.Variables) {
        TMonomial::TDegree diff = std::max(res[it.first], it.second) - res[it.first];
        res.Variables[it.first] += diff;
        res.Degree += diff;
    }
    return res;
}

}