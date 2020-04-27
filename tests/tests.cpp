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
    assert(a.GetDegree(0) == 0);
    a.SetDegree(2, 2);
    assert(a.GetDegree(2) == 2);

    NLibPoly::TMonomial b{0, 0, 1};
    NLibPoly::TMonomial c = a / b;
    assert(c.GetDegree(0) == 0);
    assert(c.GetDegree(2) == 1);

    NLibPoly::TMonomial d = b * a;
    assert(d.GetDegree(2) == 3);

    b.SetDegree(3, 1);
    NLibPoly::TMonomial e = NLibPoly::Lcm(b, d);

    assert(e.GetDegree(2) == 3);
    assert(e.GetDegree(3) == 1);

    std::cerr << "Monomial tests OK!" << std::endl;
}

void TestTerm() {
    NLibPoly::TTerm<size_t> a;
    assert(a.GetDegree(0) == 0);
    a.SetDegree(2, 1);
    a.SetCoefficient(2);
    assert(a.GetDegree(2) == 1);
    assert(a.GetCoefficient() == 2);

    NLibPoly::TTerm<size_t> b{0, 0, 1};
    NLibPoly::TTerm<size_t> c = a / b;
    assert(c.GetCoefficient() == 2);
    assert(c.GetDegree(2) == 0);

    NLibPoly::TTerm<size_t> d = b * a;
    assert(d.GetDegree(2) == 2);
    assert(d.GetCoefficient() == 2);

    b.SetDegree(3, 1);
    NLibPoly::TTerm<size_t> e = NLibPoly::Lcm(b, d);

    assert(e.GetDegree(2) == 2);
    assert(e.GetDegree(3) == 1);
    assert(e.GetCoefficient() == 2);

    std::cerr << "Term tests OK!" << std::endl;
}
