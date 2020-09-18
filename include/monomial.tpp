#include "monomial.hpp"

#include <iostream>

#include "utils.hpp"

namespace NLibPoly {

TMonomial::TMonomial(TIndex index, TDegree degree)
{
    SetDegree(index, degree);
}

TMonomial::TMonomial(std::initializer_list<std::pair<TIndex, TDegree>> init_list)
{
    for (const auto& variable : init_list) {
        SetDegree(variable.first, variable.second);
    }
}

TMonomial::TDegree TMonomial::GetDegree(TIndex index) const
{
    const auto& variable_iterator = Variables.find(index);
    if (variable_iterator == Variables.end()) {
        return TDegree(0);
    }
    return variable_iterator->second;
}

void TMonomial::SetDegree(TIndex index, TDegree degree)
{
    if (degree == TDegree(0)) {
        Variables.erase(index);
    } else {
        Variables[index] = degree;
    }
}

// No need to check for zero degree
TMonomial& TMonomial::operator*=(const TMonomial& other)
{
    for (const auto& variable : other.Variables) {
        Variables[variable.first] += variable.second;
    }
    return *this;
}

TMonomial operator*(const TMonomial& lhs, const TMonomial& rhs)
{
    TMonomial res(lhs);
    res *= rhs;
    return res;
}

TMonomial& TMonomial::operator/=(const TMonomial& other)
{
    for (const auto& variable : other.Variables) {
        TDegree degree = GetDegree(variable.first);
        if (degree < variable.second) {
            NUtils::Halt("Underflow while dividing monomials");
        }
        SetDegree(variable.first, degree - variable.second);
    }
    return *this;
}

TMonomial operator/(const TMonomial& lhs, const TMonomial& rhs)
{
    TMonomial res(lhs);
    res /= rhs;
    return res;
}

bool operator==(const TMonomial& lhs, const TMonomial& rhs)
{
    return lhs.Variables == rhs.Variables;
}

bool operator!=(const TMonomial& lhs, const TMonomial& rhs)
{
    return !(lhs == rhs);
}

TMonomial Lcm(const TMonomial& lhs, const TMonomial& rhs)
{
    TMonomial res(lhs);
    for (const auto& variable : rhs.Variables) {
        res.SetDegree(variable.first, std::max(res.GetDegree(variable.first), variable.second));
    }
    return res;
}

bool IsDivisibleBy(const TMonomial& lhs, const TMonomial& rhs)
{
    for (const auto& variable : rhs) {
        if (lhs.GetDegree(variable.first) < variable.second) {
            return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const TMonomial& monomial)
{
    if (monomial.begin() == monomial.end()) {
        out << "0";
    } else {
        bool first = true;
        for (const auto& variable : monomial) {
            if (!first) {
                out << " ";
            } else {
                first = false;
            }
            out << "x_{" << variable.first << "}^{" << variable.second << "}";
        }
    }

    return out;
}

TMonomial::TIterator TMonomial::begin()
{
    return Variables.begin();
}

TMonomial::TIterator TMonomial::end()
{
    return Variables.end();
}

TMonomial::TConstIterator TMonomial::begin() const
{
    return Variables.begin();
}

TMonomial::TConstIterator TMonomial::end() const
{
    return Variables.end();
}

TMonomial::TReverseIterator TMonomial::rbegin()
{
    return Variables.rbegin();
}

TMonomial::TReverseIterator TMonomial::rend()
{
    return Variables.rend();
}

TMonomial::TConstReverseIterator TMonomial::rbegin() const
{
    return Variables.rbegin();
}

TMonomial::TConstReverseIterator TMonomial::rend() const
{
    return Variables.rend();
}

TMonomial::TConstIterator TMonomial::cbegin() const
{
    return Variables.cbegin();
}

TMonomial::TConstIterator TMonomial::cend() const
{
    return Variables.cend();
}

TMonomial::TConstReverseIterator TMonomial::crbegin() const
{
    return Variables.crbegin();
}

TMonomial::TConstReverseIterator TMonomial::crend() const
{
    return Variables.crend();
}

}
