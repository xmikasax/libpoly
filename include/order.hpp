#ifndef INCLUDE_ORDER_HPP
#define INCLUDE_ORDER_HPP

#include "monomial.hpp"
#include "term.hpp"

namespace NLibPoly {

class TOrder {
public:
    int operator()(const TMonomial &m1, const TMonomial &m2) const;

    template <typename UCoefficientType>
    int operator()(const TTerm<UCoefficientType> &t1, const TTerm<UCoefficientType> &t2) const;

    virtual ~TOrder() {}
private:
    virtual int Cmp(const TMonomial &m1, const TMonomial &m2) const = 0;
};

class TLexOrder : public TOrder {
private:
    int Cmp(const TMonomial &m1, const TMonomial &m2) const override;
};

}

#endif // INCLUDE_ORDER_HPP
