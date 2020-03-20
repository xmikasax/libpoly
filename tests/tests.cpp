#include "tests.hpp"

#include "monomial.hpp"
#include "term.hpp"

#include <iostream>
#include <cassert>

void TestAll() {
    TestMonomial();
    TestTerm();
}

void TestMonomial() {
    NLibPoly::TMonomial a;
    assert(a[0] == 0);
    a.Set(2, 1);
    assert(a[2] == 1);

    NLibPoly::TMonomial b{0, 0};
    NLibPoly::TMonomial c = b / a;
    assert(c.GetDegree() == -1);
    assert(c[2] == -1);

    NLibPoly::TMonomial d = b * a;
    assert(d.GetDegree() == 1);
    assert(d[2] == 1);

    b.Set(3, 1);
    NLibPoly::TMonomial e = NLibPoly::Lcm(b, d);

    assert(e.GetDegree() == 2);
    assert(e[2] == 1);
    assert(e[3] == 1);

    std::cerr << "Monomial tests OK!" << std::endl;
}

void TestTerm() {
    NLibPoly::TTerm<int> a;
    assert(a[0] == 0);
    a.Set(2, 1);
    a.SetCoefficient(2);
    assert(a[2] == 1);
    assert(a.GetCoefficient() == 2);

    NLibPoly::TTerm<int> b{0, 0};
    NLibPoly::TTerm<int> c = b / a;
    assert(c.GetDegree() == -1);
    assert(c.GetCoefficient() == 0);
    assert(c[2] == -1);

    NLibPoly::TTerm<int> d = b * a;
    assert(d.GetDegree() == 1);
    assert(d.GetCoefficient() == 2);
    assert(d[2] == 1);

    b.Set(3, 1);
    NLibPoly::TTerm<int> e = NLibPoly::Lcm(b, d);

    assert(e.GetDegree() == 2);
    assert(e.GetCoefficient() == 2);
    assert(e[2] == 1);
    assert(e[3] == 1);

    std::cerr << "Term tests OK!" << std::endl;
}