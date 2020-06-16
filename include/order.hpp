#ifndef INCLUDE_ORDER_HPP
#define INCLUDE_ORDER_HPP

#include "monomial.hpp"
#include "term.hpp"

namespace NLibPoly {

template<typename UOrder>
class TOrder {
public:
    static int Compare(const TMonomial& lhs, const TMonomial& rhs);
    bool operator()(const TMonomial& lhs, const TMonomial& rhs) const;

    template<typename UCoefficientType>
    static int Compare(const TTerm<UCoefficientType>& t1, const TTerm<UCoefficientType>& t2);
    template<typename UCoefficientType>
    bool operator()(const TTerm<UCoefficientType>& t1, const TTerm<UCoefficientType>& t2) const;
};

class TLexicographicOrder : public TOrder<TLexicographicOrder> {
    friend class TOrder<TLexicographicOrder>;

private:
    static int CompareInternal(const TMonomial& lhs, const TMonomial& rhs);
};

class TReverseLexicographicOrder : public TOrder<TReverseLexicographicOrder> {
    friend class TOrder<TReverseLexicographicOrder>;

private:
    static int CompareInternal(const TMonomial& lhs, const TMonomial& rhs);
};

class TDegreeOrder : public TOrder<TDegreeOrder> {
    friend class TOrder<TDegreeOrder>;

private:
    static int CompareInternal(const TMonomial& lhs, const TMonomial& rhs);
};

class TReverseDegreeOrder : public TOrder<TReverseDegreeOrder> {
    friend class TOrder<TReverseDegreeOrder>;

private:
    static int CompareInternal(const TMonomial& lhs, const TMonomial& rhs);
};

template<typename UOrder, typename... UOrders>
class TCombineOrder : public TOrder<TCombineOrder<UOrder, UOrders...>> {
    friend class TOrder<TCombineOrder<UOrder, UOrders...>>;

private:
    static int CompareInternal(const TMonomial& lhs, const TMonomial& rhs);
};

template<typename UOrder>
class TCombineOrder<UOrder> : public TOrder<TCombineOrder<UOrder>> {
    friend class TOrder<TCombineOrder<UOrder>>;

private:
    static int CompareInternal(const TMonomial& lhs, const TMonomial& rhs);
};

using TGradedLexicographicOrder        = TCombineOrder<TDegreeOrder, TLexicographicOrder>;
using TGradedReverseLexicographicOrder = TCombineOrder<TDegreeOrder, TReverseLexicographicOrder>;
using TReverseGradedReverseLexicographicOrder =
    TCombineOrder<TReverseDegreeOrder, TReverseLexicographicOrder>;

}

#include "order.tpp"

#endif // INCLUDE_ORDER_HPP
