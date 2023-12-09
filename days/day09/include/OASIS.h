#pragma once
#include <vector>
#include <string>
#include <iostream>

class IntPolynomial {
public:
    IntPolynomial(const std::vector<double> &coeffs) : m_coeffs(coeffs) {};
    void mul(double x); // multiply by (n+x)
    void add(const IntPolynomial &p);
    long int eval(long int x);
    friend std::ostream& operator<< (std::ostream& stream, const IntPolynomial& p);
private:
    std::vector<double> m_coeffs;
};

class OASIS {
public:
    OASIS(std::istream &in);
    long int getNextTermSumScore();
    long int getPrevTermSumScore();
private:
    void createPolynomial(const std::string &x);
    std::vector<IntPolynomial> m_polynomials;
    std::vector<unsigned int> m_initial_length;
};