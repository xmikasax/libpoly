#include "tests.hpp"

#include <cassert>
#include <iostream>

#include "algorithms.hpp"
#include "integer_mod.hpp"
#include "monomial.hpp"
#include "order.hpp"
#include "polynomial.hpp"
#include "polynomial_set.hpp"
#include "term.hpp"
#include "utils.hpp"

void TestAll()
{
    TestMonomial();
    TestTerm();
    TestOrder();
    TestPolynomial();
    TestPolynomialSet();
    TestAlgorithms();
}

void TestMonomial()
{
    using namespace NLibPoly;

    {
        TMonomial a;
        assert(a.GetDegree(0) == 0);
        a.SetDegree(2, 2);
        assert(a.GetDegree(2) == 2);
    }

    {
        TMonomial a{ { 2, 2 } };
        TMonomial b{ { 2, 1 } };
        TMonomial c = a / b;
        assert(c.GetDegree(0) == 0);
        assert(c.GetDegree(2) == 1);
    }

    {
        TMonomial a{ { 2, 2 } };
        TMonomial b{ { 2, 1 } };
        TMonomial c = b * a;
        assert(c.GetDegree(2) == 3);
    }

    {
        TMonomial a{ { 2, 2 } };
        TMonomial b{ { 2, 1 }, { 3, 1 } };
        TMonomial c = Lcm(a, b);

        assert(c.GetDegree(2) == 2);
        assert(c.GetDegree(3) == 1);
    }

    {
        TMonomial a{ { 2, 2 } };
        TMonomial b{ { 2, 1 }, { 3, 1 } };
        try {
            TMonomial bad = b / a;
            assert(false);
        } catch (NUtils::TLibPolyException& e) {
        }
    }

    {
        TMonomial a{ { 2, 2 } };
        TMonomial b{ { 2, 1 } };
        assert(b * b == a);
        assert(b != a);
    }

    {
        TMonomial a{ { 2, 2 } };
        TMonomial b{ { 2, 1 } };
        TMonomial c{ { 2, 1 }, { 3, 1 } };

        assert(IsDivisibleBy(a, b));
        assert(IsDivisibleBy(c, b));
        assert(!IsDivisibleBy(b, c));
    }

    std::cerr << "Monomial tests OK!" << std::endl;
}

void TestTerm()
{
    using namespace NLibPoly;

    {
        TTerm<TIntegerMod<5>> a;
        assert(a.GetDegree(0) == 0);
        a.SetDegree(2, 1);
        a.SetCoefficient(2);
        assert(a.GetDegree(2) == 1);
        assert(a.GetCoefficient() == 2);
    }

    {
        TTerm<TIntegerMod<5>> a{ 2, { { 2, 1 } } };
        TTerm<TIntegerMod<5>> b{ 2, { 2, 1 } };
        TTerm<TIntegerMod<5>> c = a / b;
        assert(c.GetCoefficient() == 1);
        assert(c.GetDegree(2) == 0);
    }

    {
        TTerm<TIntegerMod<5>> a{ 2, { { 2, 1 } } };
        TTerm<TIntegerMod<5>> b{ { 2, 1 } };
        TTerm<TIntegerMod<5>> d = b * a;
        assert(d.GetDegree(2) == 2);
        assert(d.GetCoefficient() == 2);
    }

    {
        TTerm<TIntegerMod<5>> a{ 2, { { 2, 2 } } };
        TTerm<TIntegerMod<5>> b{ { 2, 1 } };
        b.SetDegree(3, 1);
        TTerm<TIntegerMod<5>> c = Lcm(a, b);

        assert(c.GetDegree(2) == 2);
        assert(c.GetDegree(3) == 1);
        assert(c.GetCoefficient() == 2);
    }

    std::cerr << "Term tests OK!" << std::endl;
}

void TestOrder()
{
    using namespace NLibPoly;

    {
        TMonomial a{ { 1, 1 }, { 2, 1 } };
        TMonomial b{ { 1, 1 }, { 2, 1 } };

        assert(!TLexicographicOrder()(a, b));
        assert(TLexicographicOrder::Compare(a, b) == 0);
    }

    {
        TMonomial a{ { 1, 1 }, { 2, 1 } };
        TMonomial b{ { 1, 1 }, { 2, 2 } };

        assert(TLexicographicOrder()(a, b));
        assert(TLexicographicOrder::Compare(a, b) < 0);
    }

    {
        TMonomial a{ { 1, 2 }, { 2, 1 } };
        TMonomial b{ { 1, 1 }, { 2, 1 } };

        assert(!TLexicographicOrder()(a, b));
        assert(TLexicographicOrder::Compare(a, b) > 0);
    }

    {
        TMonomial a{ { 1, 1 }, { 2, 2 } };
        TMonomial b{ { 1, 2 }, { 2, 1 } };

        assert(!TDegreeOrder()(a, b));
    }

    {
        TMonomial a{ { 1, 1 }, { 2, 1 } };
        TMonomial b{ { 1, 1 }, { 2, 2 } };

        assert(TDegreeOrder()(a, b));
    }

    {
        TMonomial a{ { 1, 1 }, { 2, 1 }, { 3, 1 } };
        TMonomial b{ { 1, 1 }, { 2, 1 } };

        assert(!TLexicographicOrder()(a, b));
    }

    {
        TMonomial a{ { 1, 2 }, { 2, 1 }, { 3, 1 } };
        TMonomial b{ { 1, 1 }, { 2, 4 } };
        TMonomial c{ { 1, 1 }, { 2, 2 }, { 3, 1 } };

        assert(TGradedLexicographicOrder::Compare(a, b) < 0);
        assert(!TGradedLexicographicOrder()(b, c));
    }

    {
        TMonomial a{ { 1, 0 }, { 2, 2 }, { 3, 1 } };
        TMonomial b{ { 1, 0 }, { 2, 1 }, { 3, 2 } };
        TMonomial c{ { 1, 1 }, { 2, 1 }, { 3, 2 } };

        assert(TReverseLexicographicOrder::Compare(a, b) > 0);
        assert(TReverseLexicographicOrder::Compare(b, c) > 0);
    }

    {
        TMonomial a{ { 1, 2 } };
        TMonomial b{ { 1, 1 }, { 2, 1 } };
        TMonomial c{ { 2, 2 } };
        TMonomial d{ { 1, 1 }, { 3, 1 } };
        TMonomial e{ { 2, 1 }, { 3, 1 } };
        TMonomial f{ { 3, 2 } };

        assert(TGradedReverseLexicographicOrder::Compare(a, b) > 0);
        assert(TGradedReverseLexicographicOrder::Compare(b, c) > 0);
        assert(TGradedReverseLexicographicOrder::Compare(c, d) > 0);
        assert(TGradedReverseLexicographicOrder::Compare(d, e) > 0);
        assert(TGradedReverseLexicographicOrder::Compare(e, f) > 0);
    }

    std::cerr << "Order tests OK!" << std::endl;
}

void TestPolynomial()
{
    using namespace NLibPoly;

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { { 1, 2 }, { 3, 4 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { { 1, 2 }, { 3, 4 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{ { 1, { { 2, 3 } } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> d{ { { 1, 2 }, { 3, 5 } } };

        assert(a == b);
        assert(b != d);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { { 1, 2 } }, { { 3, 4 } } };

        assert(a.size() == 2);
        assert(a.Size() == 2);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { { 3, 4 }, { 5, 6 } }, { { 7, 8 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c = a + b;
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> d{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { 2, { { 3, 4 }, { 5, 6 } } },
                                                            { { 7, 8 } } };

        assert(c == d);
        assert(c - b == a);
        assert(d - a == b);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TTerm<TIntegerMod<5>> b{ { 3, 4 }, { 5, 6 } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{
            { 2, { { 1, 2 }, { 3, 4 } } },
        };

        assert(a - b == c);
        assert(a - b + b == a);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { { 1, 2 } }, { { 3, 4 } } };

        TTerm<TIntegerMod<5>> b{ 2, { 3, 4 } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { 2, { 3, 8 } } };

        assert(a * b == c);
    }

    std::cerr << "Polynomial tests OK!" << std::endl;
}

void TestPolynomialSet()
{
    using namespace NLibPoly;

    {
        TPolynomialSet<TIntegerMod<5>, TLexicographicOrder> a;

        assert(a.Size() == 0);

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        a.Insert(b);

        assert(a.Size() == 1);

        a.Insert(b);

        assert(a.Size() == 1);

        a.Erase(b);

        assert(a.Size() == 0);

        a.Erase(b);

        assert(a.Size() == 0);
    }

    std::cerr << "Polynomial Set tests OK!" << std::endl;
}

void TestAlgorithms()
{
    using namespace NLibPoly;

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{ { { 5, 6 } }, { { 7, 8 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> d;
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> e{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { 4, { { 3, 4 }, { 7, 8 } } } };

        assert(Reduce(a, b) == d);
        assert(Reduce(a, c) == e);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{ { { 5, 6 } }, { { 7, 8 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> d;
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> e{ { 3, { { 1, 2 }, { 3, 4 }, { 7, 8 } } },
                                                            { { { 3, 4 }, { 5, 12 } } } };

        assert(SPolynomial(a, b) == d);
        assert(SPolynomial(a, c) == e);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { 2, { { 1, 2 }, { 3, 4 } } },
                                                            { { 3, 4 }, { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { { 5, 6 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> c{ { 3, { { 1, 2 }, { 3, 4 }, { 7, 8 } } },
                                                            { { { 3, 4 }, { 5, 12 } } } };

        TPolynomialSet<TIntegerMod<5>, TLexicographicOrder> d;

        d.Insert(a);
        d.Insert(b);

        assert(Reduce(c, d).Size() == 0);
    }

    {
        TPolynomial<TIntegerMod<5>, TLexicographicOrder> a{ { { 1, 1 }, { 2, 1 } },
                                                            { 4, { 4, 1 } } };

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> b{ { { 1, 1 }, { 3, 1 } },
                                                            { 4, { 4, 1 } } };

        TPolynomialSet<TIntegerMod<5>, TLexicographicOrder> c;

        c.Insert(a);
        c.Insert(b);

        auto d = Buchberger(c);

        d.Erase(a);
        d.Erase(b);

        TPolynomial<TIntegerMod<5>, TLexicographicOrder> e{ { { 2, 1 }, { 4, 1 } },
                                                            { 4, { { 3, 1 }, { 4, 1 } } } };

        assert(d.Size() == 1);
        assert(*d.begin() == e);
    }

    std::cerr << "Algorithms tests OK!" << std::endl;
}
