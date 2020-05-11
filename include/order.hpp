#ifndef INCLUDE_ORDER_HPP
#define INCLUDE_ORDER_HPP

#include "monomial.hpp"
#include "term.hpp"

namespace NLibPoly {

template <typename UOrder>
class TOrder {
public:
    static int Compare(const TMonomial &m1, const TMonomial &m2);
    bool operator()(const TMonomial &m1, const TMonomial &m2) const;

    template <typename UCoefficientType>
    static int Compare(const TTerm<UCoefficientType> &t1, const TTerm<UCoefficientType> &t2);
    template <typename UCoefficientType>
    bool operator()(const TTerm<UCoefficientType> &t1, const TTerm<UCoefficientType> &t2) const;
};

class TLexicographicOrder : public TOrder<TLexicographicOrder> {
    friend class TOrder<TLexicographicOrder>;
private:
    static int CompareInternal(const TMonomial &m1, const TMonomial &m2);
};

class TDegreeOrder : public TOrder<TDegreeOrder> {
    friend class TOrder<TDegreeOrder>;
private:
    static int CompareInternal(const TMonomial &m1, const TMonomial &m2);
};

template<typename UOrder, typename... UOrders>
class TCombineOrder : public TOrder<TCombineOrder<UOrder, UOrders...>> {
    friend class TOrder<TCombineOrder<UOrder, UOrders...>>;
private:
    static int CompareInternal(const TMonomial &m1, const TMonomial &m2);
};

template<typename UOrder>
class TCombineOrder<UOrder> : public TOrder<TCombineOrder<UOrder>> {
    friend class TOrder<TCombineOrder<UOrder>>;
private:
    static int CompareInternal(const TMonomial &m1, const TMonomial &m2);
};

}

#include "order.tpp"

#endif // INCLUDE_ORDER_HPP
