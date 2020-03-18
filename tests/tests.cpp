#include "tests.hpp"

#include "monomial.hpp"

#include <iostream>
#include <cassert>

void TestAll() {
    TestMonomial();
}

void TestMonomial() {
    NLibPoly::TMonomial monomial;
    assert(monomial[0] == 0);
    monomial[2] = 1;
    assert(monomial[2] == 1);

    std::cerr << "Monomial tests OK!" << std::endl;
}