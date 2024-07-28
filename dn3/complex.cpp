#include "complex.h"

Complex::Complex(double re, double im) : re(re), im(im) {}

Complex::Complex(double re) : re(re), im(0.0) {}
Complex::Complex() : re(0.0), im(0.0) {}

Complex Complex::times(const Complex& other) {
    return Complex(re * other.re - im * other.im, re * other.im + im * other.re);
}

Complex Complex::divide(double x) {
    return Complex(re / x, im / x);
}

Complex Complex::plus(const Complex& other) {
    return Complex(re + other.re, im + other.im);
}

Complex Complex::minus(const Complex& other) {
    return Complex(re - other.re, im - other.im);
}

double Complex::toDouble() const {
    return re;
}

std::vector<double> Complex::toDouble(const std::vector<Complex>& c) {
    std::vector<double> d(c.size());
    for (std::size_t i = 0; i < c.size(); i++) {
        d[i] = c[i].toDouble();
    }
    return d;
}

std::vector<Complex> Complex::toComplex(const std::vector<double>& c) {
    std::vector<Complex> d(c.size());
    for (std::size_t i = 0; i < c.size(); i++) {
        d[i] = Complex(c[i]);
    }
    return d;
}

