#ifndef INCLUDE_ORDER_TPP
#define INCLUDE_ORDER_TPP

#include "order.hpp"

#include "monomial.hpp"
#include "term.hpp"

namespace NLibPoly {

template<typename UOrder>
int TOrder<UOrder>::Compare(const TMonomial& lhs, const TMonomial& rhs)
{
    return UOrder::CompareInternal(lhs, rhs);
}

template<typename UOrder>
bool TOrder<UOrder>::operator()(const TMonomial& lhs, const TMonomial& rhs) const
{
    return UOrder::CompareInternal(lhs, rhs) < 0;
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

int TLexicographicOrder::CompareInternal(const TMonomial& lhs, const TMonomial& rhs)
{
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();

    while (it1 != lhs.end() && it2 != rhs.end()) {
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

    if (it1 != lhs.end()) {
        return 1;
    } else if (it2 != rhs.end()) {
        return -1;
    }

    return 0;
}

int TReverseLexicographicOrder::CompareInternal(const TMonomial& lhs, const TMonomial& rhs)
{
    auto it1 = lhs.rbegin();
    auto it2 = rhs.rbegin();

    while (it1 != lhs.rend() && it2 != rhs.rend()) {
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

    if (it1 != lhs.rend()) {
        return -1;
    } else if (it2 != rhs.rend()) {
        return 1;
    }

    return 0;
}

int TDegreeOrder::CompareInternal(const TMonomial& lhs, const TMonomial& rhs)
{
    TMonomial::TDegree degree1 = 0;
    for (const auto& variable : lhs) {
        degree1 += variable.second;
    }

    TMonomial::TDegree degree2 = 0;
    for (const auto& variable : rhs) {
        degree2 += variable.second;
    }

    if (degree1 < degree2) {
        return -1;
    } else if (degree1 == degree2) {
        return 0;
    } else {
        return 1;
    }
}

int TReverseDegreeOrder::CompareInternal(const TMonomial& lhs, const TMonomial& rhs)
{
    return TDegreeOrder::Compare(lhs, rhs) * -1;
}

template<typename UOrder, typename... UOrders>
int TCombineOrder<UOrder, UOrders...>::CompareInternal(const TMonomial& lhs, const TMonomial& rhs)
{
    int comparison = UOrder::Compare(lhs, rhs);
    if (comparison != 0) {
        return comparison;
    }

    return TCombineOrder<UOrders...>::Compare(lhs, rhs);
}

template<typename UOrder>
int TCombineOrder<UOrder>::CompareInternal(const TMonomial& lhs, const TMonomial& rhs)
{
    return UOrder::Compare(lhs, rhs);
}

}

#endif // INCLUDE_ORDER_TPP
