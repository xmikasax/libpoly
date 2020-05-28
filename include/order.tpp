#ifndef INCLUDE_ORDER_TPP
#define INCLUDE_ORDER_TPP

#include "order.hpp"

#include "monomial.hpp"
#include "term.hpp"

namespace NLibPoly {

template<typename UOrder>
int TOrder<UOrder>::Compare(const TMonomial& m1, const TMonomial& m2)
{
    return UOrder::CompareInternal(m1, m2);
}

template<typename UOrder>
bool TOrder<UOrder>::operator()(const TMonomial& m1, const TMonomial& m2) const
{
    return UOrder::CompareInternal(m1, m2) < 0;
}

template<typename UOrder>
template<typename UCoefficientType>
int TOrder<UOrder>::Compare(const TTerm<UCoefficientType>& t1, const TTerm<UCoefficientType>& t2)
{
    return UOrder::CompareInternal(t1.GetMonomial(), t2.GetMonomial());
}

template<typename UOrder>
template<typename UCoefficientType>
bool TOrder<UOrder>::operator()(
    const TTerm<UCoefficientType>& t1, const TTerm<UCoefficientType>& t2) const
{
    return UOrder::CompareInternal(t1.GetMonomial(), t2.GetMonomial()) < 0;
}

int TLexicographicOrder::CompareInternal(const TMonomial& m1, const TMonomial& m2)
{
    auto it1 = m1.begin();
    auto it2 = m2.begin();

    while (it1 != m1.end() && it2 != m2.end()) {
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

    if (it1 != m1.end()) {
        return 1;
    } else if (it2 != m2.end()) {
        return -1;
    }

    return 0;
}

int TReverseLexicographicOrder::CompareInternal(const TMonomial& m1, const TMonomial& m2)
{
    auto it1 = m1.rbegin();
    auto it2 = m2.rbegin();

    while (it1 != m1.rend() && it2 != m2.rend()) {
        if (it1->first > it2->first) {
            return -1;
        } else if (it1->first < it2->first) {
            return 1;
        }

        if (it1->second > it2->second) {
            return -1;
        } else if (it1->second < it2->second) {
            return 1;
        }

        ++it1;
        ++it2;
    }

    if (it1 != m1.rend()) {
        return -1;
    } else if (it2 != m2.rend()) {
        return 1;
    }

    return 0;
}

int TDegreeOrder::CompareInternal(const TMonomial& m1, const TMonomial& m2)
{
    TMonomial::TDegree degree1 = 0;
    for (const auto& it : m1) {
        degree1 += it.second;
    }

    TMonomial::TDegree degree2 = 0;
    for (const auto& it : m2) {
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

template<typename UOrder, typename... UOrders>
int TCombineOrder<UOrder, UOrders...>::CompareInternal(const TMonomial& m1, const TMonomial& m2)
{
    int comparison = UOrder::Compare(m1, m2);
    if (comparison != 0) {
        return comparison;
    }

    return TCombineOrder<UOrders...>::Compare(m1, m2);
}

template<typename UOrder>
int TCombineOrder<UOrder>::CompareInternal(const TMonomial& m1, const TMonomial& m2)
{
    return UOrder::Compare(m1, m2);
}

}

#endif // INCLUDE_ORDER_TPP
