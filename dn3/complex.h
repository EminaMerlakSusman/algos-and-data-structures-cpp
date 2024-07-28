#ifndef COMPLEX_H
#define COMPLEX_H

#include <vector>

class Complex {
private:
    double re;
    double im;
public:
    Complex(double re, double im);
    Complex(double re);
    Complex(); // Default constructor

    Complex times(const Complex& other);
    Complex divide(double x);
    Complex plus(const Complex& other);
    Complex minus(const Complex& other);

    double toDouble() const;

    static std::vector<double> toDouble(const std::vector<Complex>& c);
    static std::vector<Complex> toComplex(const std::vector<double>& c);
};

#endif // COMPLEX_H
