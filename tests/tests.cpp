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

    {
        TMonomial a;
        assert(a.GetDegree(0) == 0);
        a.SetDegree(2, 2);
        assert(a.GetDegree(2) == 2);
    }

    {
        TMonomial a{{2, 2}};
        TMonomial b{{2, 1}};
        TMonomial c = a / b;
        assert(c.GetDegree(0) == 0);
        assert(c.GetDegree(2) == 1);
    }

    {
        TMonomial a{{2, 2}};
        TMonomial b{{2, 1}};
        TMonomial c = b * a;
        assert(c.GetDegree(2) == 3);
    }

    {
        TMonomial a{{2, 2}};
        TMonomial b{{2, 1}, {3, 1}};
        TMonomial c = Lcm(a, b);

        assert(c.GetDegree(2) == 2);
        assert(c.GetDegree(3) == 1);
    }

    {
        TMonomial a{{2, 2}};
        TMonomial b{{2, 1}, {3, 1}};
        try {
            TMonomial bad = b / a;
            assert(false);
        } catch (NUtils::TLibPolyException& e) {}
    }

    {
        TMonomial a{{2, 2}};
        TMonomial b{{2, 1}};
        assert(b * b == a);
        assert(b != a);
    }

    std::cerr << "Monomial tests OK!" << std::endl;
}

void TestTerm() {
    using namespace NLibPoly;

    {
        TTerm<size_t> a;
        assert(a.GetDegree(0) == 0);
        a.SetDegree(2, 1);
        a.SetCoefficient(2);
        assert(a.GetDegree(2) == 1);
        assert(a.GetCoefficient() == 2);
    }

    {
        TTerm<size_t> a(2, {{2, 1}});
        TTerm<size_t> b{{2, 1}};
        TTerm<size_t> c = a / b;
        assert(c.GetCoefficient() == 2);
        assert(c.GetDegree(2) == 0);
    }

    {
        TTerm<size_t> a(2, {{2, 1}});
        TTerm<size_t> b{{2, 1}};
        TTerm<size_t> d = b * a;
        assert(d.GetDegree(2) == 2);
        assert(d.GetCoefficient() == 2);
    }

    {
        TTerm<size_t> a(2, {{2, 2}});
        TTerm<size_t> b{{2, 1}};
        b.SetDegree(3, 1);
        TTerm<size_t> c = Lcm(a, b);

        assert(c.GetDegree(2) == 2);
        assert(c.GetDegree(3) == 1);
        assert(c.GetCoefficient() == 2);
    }

    std::cerr << "Term tests OK!" << std::endl;
}

void TestOrder() {
    using namespace NLibPoly;

    {
        TMonomial a{{1, 1}, {2, 1}};
        TMonomial b{{1, 1}, {2, 1}};

        assert(TLexOrder()(a, b) == 0);
    }

    {
        TMonomial a{{1, 1}, {2, 1}};
        TMonomial b{{1, 1}, {2, 2}};

        assert(TLexOrder()(a, b) < 0);
    }

    {
        TMonomial a{{1, 2}, {2, 1}};
        TMonomial b{{1, 1}, {2, 1}};

        assert(TLexOrder()(a, b) > 0);
    }

    std::cerr << "Order tests OK!" << std::endl;
}
