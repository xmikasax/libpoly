#include "tests.hpp"

#include "monomial.hpp"

#include <iostream>
#include <cassert>

void TestAll() {
    TestMonomial();
}

void TestMonomial() {
    NLibPoly::TMonomial a;
    assert(a[0] == 0);
    a.Set(2, 1);
    assert(a[2] == 1);

    NLibPoly::TMonomial b;
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