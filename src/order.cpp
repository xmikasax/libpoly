#include "order.hpp"

#include "monomial.hpp"
#include "term.hpp"

namespace NLibPoly {

int TOrder::operator()(const TMonomial &m1, const TMonomial &m2) const {
    return Cmp(m1, m2) < 0;
}

template <typename UCoefficientType>
int TOrder::operator()(const TTerm<UCoefficientType> &t1, const TTerm<UCoefficientType> &t2) const {
    return Cmp(t1.GetMonomial(), t2.GetMonomial()) < 0;
}

int TLexicographicOrder::Cmp(const TMonomial &m1, const TMonomial &m2) const {
    auto it1 = m1.cbegin();
    auto it2 = m2.cbegin();

    while (it1 != m1.cend() && it2 != m2.cend()) {
        if (it1->first > it2->first) {
            return -1;
        } else if (it1->first < it2->first) {
            return 1;
        }

        if (it1->second > it2->second) {
            return 1;
        } else if (it1->second < it2->second) {
            return -1;
        }

        ++it1;
        ++it2;
    }

    if (it1 != m1.cend()) {
        return 1;
    } else if (it2 != m2.cend()) {
        return -1;
    }

    return 0;
}

int TDegreeOrder::Cmp(const TMonomial &m1, const TMonomial &m2) const {
    TMonomial::TDegree degree1 = 0;
    for (const auto &it : m1) {
        degree1 += it.second;
    }

    TMonomial::TDegree degree2 = 0;
    for (const auto &it : m2) {
        degree2 += it.second;
    }

    if (degree1 < degree2) {
        return -1;
    } else if (degree1 == degree2) {
        return 0;
    } else {
        return 1;
    }
}

}
