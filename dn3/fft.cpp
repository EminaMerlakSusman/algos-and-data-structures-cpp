#include "fft.h"
#include "complex.h"
#include <cmath>
#include <algorithm>

std::vector<Complex> FFT::fft(std::vector<Complex> a, bool jeInverzno) {
    int n = a.size();
    if (n == 1) {
        return a;
    } else {
        std::vector<Complex> sodi(n / 2);
        std::vector<Complex> lihi(n / 2);
        for (int i = 0; 2 * i < n; i++) {
            sodi[i] = a[2 * i];
            lihi[i] = a[2 * i + 1];
        }
        std::vector<Complex> sodiFFT = fft(sodi, jeInverzno);
        std::vector<Complex> lihiFFT = fft(lihi, jeInverzno);
        Complex w(1.0);
        double alfa = 2.0 * M_PI / n * (jeInverzno ? -1 : 1);
        Complex w0(cos(alfa), sin(alfa));
        for (int i = 0; 2 * i < n; i++) {
            Complex c = w.times(lihiFFT[i]);
            a[i] = sodiFFT[i].plus(c);
            a[i + n / 2] = sodiFFT[i].minus(c);
            if (jeInverzno) {
                a[i] = a[i].divide(2.0);
                a[i + n / 2] = a[i + n / 2].divide(2.0);
            }
            w = w.times(w0);
        }
    }
    return a;
}

std::vector<double> FFT::zmnoziPolinome(const std::vector<double>& a, const std::vector<double>& b) {
    int stA = a.size() - 1;
    int stB = b.size() - 1;
    int n = 1;
    while (n <= stA + stB) {
        n *= 2;
    }
    std::vector<Complex> aC(n);
    std::vector<Complex> bC(n);
    for (int i = 0; i < n; i++) {
        aC[i] = i <= stA ? Complex(a[i]) : Complex(0.0);
        bC[i] = i <= stB ? Complex(b[i]) : Complex(0.0);
    }
    std::vector<Complex> aFFT = fft(aC, false);
    std::vector<Complex> bFFT = fft(bC, false);
    std::vector<Complex> abFFT(n);
    for (int i = 0; i < n; i++) {
        abFFT[i] = aFFT[i].times(bFFT[i]);
    }
    std::vector<double> ab = Complex::toDouble(fft(abFFT, true));
    return std::vector<double>(ab.begin(), ab.begin() + stA + stB + 1);
}
