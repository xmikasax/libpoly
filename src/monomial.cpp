#include "monomial.hpp"
#include <iostream>

namespace NLibPoly {

TMonomial::TMonomial(TIndex index, TDegree degree) {
    (*this)[index] = degree;
    Degree = degree;
}

TMonomial::TDegree &TMonomial::operator[](TIndex index) {
    return Variables[index];
}

TMonomial::TDegree &TMonomial::at(TIndex index) {
    return Variables.at(index);
}

const TMonomial::TDegree &TMonomial::at(TIndex index) const {
    return Variables.at(index);
}

}