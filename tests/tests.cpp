#include "tests.hpp"

#include <iostream>
#include <cassert>

#include "monomial.hpp"
#include "term.hpp"
#include "utils.hpp"
#include "order.hpp"

void TestAll() {
    TestMonomial();
    TestTerm();
    TestOrder();
}

void TestMonomial() {
    using namespace NLibPoly;

    TMonomial a;
    assert(a.GetDegree(0) == 0);
    a.SetDegree(2, 2);
    assert(a.GetDegree(2) == 2);

    TMonomial b{{2, 1}};
    TMonomial c = a / b;
    assert(c.GetDegree(0) == 0);
    assert(c.GetDegree(2) == 1);

    TMonomial d = b * a;
    assert(d.GetDegree(2) == 3);

    b.SetDegree(3, 1);
    TMonomial e = Lcm(b, d);

    assert(e.GetDegree(2) == 3);
    assert(e.GetDegree(3) == 1);

    try {
        TMonomial bad = b / a;
        assert(false);
    } catch (NUtils::TLibPolyException& e) {}

    assert(c * c == a);
    assert(c != a);

    std::cerr << "Monomial tests OK!" << std::endl;
}

void TestTerm() {
    using namespace NLibPoly;

    TTerm<size_t> a;
    assert(a.GetDegree(0) == 0);
    a.SetDegree(2, 1);
    a.SetCoefficient(2);
    assert(a.GetDegree(2) == 1);
    assert(a.GetCoefficient() == 2);

    TTerm<size_t> b{{2, 1}};
    TTerm<size_t> c = a / b;
    assert(c.GetCoefficient() == 2);
    assert(c.GetDegree(2) == 0);

    TTerm<size_t> d = b * a;
    assert(d.GetDegree(2) == 2);
    assert(d.GetCoefficient() == 2);

    b.SetDegree(3, 1);
    TTerm<size_t> e = Lcm(b, d);

    assert(e.GetDegree(2) == 2);
    assert(e.GetDegree(3) == 1);
    assert(e.GetCoefficient() == 2);

    std::cerr << "Term tests OK!" << std::endl;
}

void TestOrder() {
    using namespace NLibPoly;

    TMonomial a{{1, 1}, {2, 1}};
    TMonomial b{{1, 1}, {2, 1}};

    assert(TLexOrder()(a, b) == 0);

    TMonomial c{{1, 1}, {2, 1}};
    TMonomial d{{1, 1}, {2, 2}};

    assert(TLexOrder()(c, d) < 0);

    TMonomial e{{1, 2}, {2, 1}};
    TMonomial f{{1, 1}, {2, 1}};

    assert(TLexOrder()(e, f) > 0);

    std::cerr << "Order tests OK!" << std::endl;
}
