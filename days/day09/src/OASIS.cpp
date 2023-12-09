#include "OASIS.h"
#include <cmath>
#include <sstream>

std::ostream& operator <<(std::ostream& stream, const IntPolynomial& p) {
    stream << p.m_coeffs[0];
    for (unsigned int i = 1; i< p.m_coeffs.size(); i++) {
        stream << " +" << p.m_coeffs[i] << "n^" << i;
    }
    return stream;
}

long int IntPolynomial::eval(long int x) {
    double res = 0;
    for (unsigned int i = 0; i < m_coeffs.size(); i++) {
        res += m_coeffs[i] * std::pow(x, i);
    }
    return std::lround(res);
}

void IntPolynomial::mul(double x) { // mul by n+x
    std::vector<double> new_coeffs(m_coeffs.size() + 1,0);
    for(unsigned int i = 0; i < m_coeffs.size(); i++) {
        new_coeffs[i] = x * m_coeffs[i];
    }
    for(unsigned int i = 0; i < m_coeffs.size(); i++){
        new_coeffs[i + 1] += m_coeffs[i];
    }
    m_coeffs = new_coeffs;
}

void IntPolynomial::add(const IntPolynomial &p) {
    std::vector<double> new_coeffs(std::max(m_coeffs.size(), p.m_coeffs.size()),0);
    for (unsigned int i = 0; i < m_coeffs.size(); i++) {
        new_coeffs[i] += m_coeffs[i];
    }
    for (unsigned int i = 0; i < p.m_coeffs.size(); i++) {
        new_coeffs[i] += p.m_coeffs[i];
    }
    m_coeffs = new_coeffs;
}

OASIS::OASIS(std::istream &in) {
    for(std::string x; std::getline(in, x);) {
        createPolynomial(x);
    }
}

long int OASIS::getNextTermSumScore() {
    long int res = 0;
    for (unsigned int i = 0; i < m_polynomials.size(); i++) {
        res +=m_polynomials[i].eval(m_initial_length[i]);
    }
    return res;
}

long int OASIS::getPrevTermSumScore() {
    long int res = 0;
    for (unsigned int i = 0; i < m_polynomials.size(); i++) {
        res +=m_polynomials[i].eval(-1);
    }
    return res;
}
void OASIS::createPolynomial(const std::string &x) {
    long int term;
    std::vector<std::vector<long int>> diffs;
    diffs.push_back(std::vector<long int>());
    std::stringstream iss(x);
    while ( iss >> term ) diffs.back().push_back( term );
    m_initial_length.push_back(diffs.back().size());

    bool constant = false;
    while (!constant) {
        auto prev = diffs.back();
        diffs.push_back(std::vector<long int>());
        constant = true;
        for(unsigned int i = 0; i < prev.size() - 1; i++) {
            diffs.back().push_back(prev[i + 1] - prev[i]);
            constant &= (diffs.back().back() == diffs.back()[0]);
        }
    }
    m_polynomials.push_back(IntPolynomial({0}));
    for(unsigned int i = 0; i < diffs.size(); i++) {
        double den = 1;
        for(unsigned int j = 2; j <= i; j++) {
            den *= j;
        }
        auto p = IntPolynomial({(double)(diffs[i][0]) / den});
        for(unsigned int j = 0; j < i; j++) {
            p.mul(-1 * (double)j);
        }
        m_polynomials.back().add(p);
    }
}
