#ifndef FFT_H
#define FFT_H

#include "complex.h"
#include <string>
#include <vector>

class FFT {
public:
    static std::vector<Complex> fft(std::vector<Complex> a, bool jeInverzno);
    static std::vector<double> zmnoziPolinome(const std::vector<double>& a, const std::vector<double>& b);

private:
    static std::vector<double> predelajVSeznam(const std::string& x);
};

#endif // FFT_H
