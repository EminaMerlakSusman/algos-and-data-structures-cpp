#include "resitev.h"
#include "fft.h"
#include "complex.h"
#include <cmath>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

std::vector<std::vector<double>> sestaviPolinome(const std::vector<double>& verjetnosti) {
    std::vector<std::vector<double>> polinomi;
    for (double p : verjetnosti) {
        std::vector<double> polinom = {1 - p, p};
        polinomi.push_back(polinom);
    }
    return polinomi;
}

std::vector<double> zmnoziRekurzivno(std::vector<std::vector<double>>& polinomi, int levo, int desno, FFT& fft) {
    if (levo == desno) {
        return polinomi[levo];
    }

    int sred = levo + (desno - levo) / 2;
    std::vector<double> p1 = zmnoziRekurzivno(polinomi, levo, sred, fft);
    std::vector<double> p2 = zmnoziRekurzivno(polinomi, sred + 1, desno, fft);
    return fft.zmnoziPolinome(p1, p2);
}

vector<double> Resitev::izracunajVerjetnosti(const vector<double> &verjetnosti, string naloga)
{
    FFT fft;
    int A = verjetnosti.size();
    vector<double> Pk (verjetnosti.size() + 1);
    std::fill(Pk.begin(), Pk.end(), -1.0);

    //Naredi matriko velikosti A x {dolžina posamezne vrstice}.
    //Element na mestu (k, n) v matriki opisuje verjetnost, da na prvih
    // k avtomatih dobiš n točk, označeno P_k(T = n). Zadnja vrstica matrike 
    // predstavlja rešitev, torej verjetnosti, da na A avtomatih dobiš od 1 do A pik.
    // vector<vector<double>> matrika;

    // for (int k = 0; k < A; k++) {
    //     // Posamezna vrstica je lahko dolga samo k+1, saj P_k(T = n) = 0, 
    //     // ko n > k + 1 (ni možno dobiti več pik, kot pa ko so vsi avtomati prižgani)
    //     vector<double> P_k;
    //     double pk = verjetnosti[k];
        
    //     for (int n = 0; n < k+1; n++) {
    //         // P_k(T = n) = P_k-1(n - 1) * pk + P_k-1(n) * (1 - pk)
    //         // torej: al si na prejšnih k-1 avtomatih dobil n-1 pik pa je ta prižgan,
    //         // al pa da si na prejšnih dobil vseh n pik pa je ta ugasnen
    //         if (k==0) {
    //             if (n == 0) {
    //                 P_k.push_back(1 - pk);
    //             }
    //             else {
    //                 P_k.push_back(pk);
    //             }
    //             P_k.push_back(pk);
    //         }
    //         else {
    //             vector<double> prejsna_vrstica = matrika[k - 1];
    //             P_k.push_back(prejsna_vrstica[n-1] * pk + prejsna_vrstica[n] * (1 - pk));
    //         }
            
    //     }

    //     if (k != 0){
    //         P_k.push_back(pk * matrika[k-1][k]);
    //     };
        
    //     matrika.push_back(P_k);
        
    // };


    vector<double> p1_inv = {verjetnosti[0], 1 - verjetnosti[0]};
    vector<double> p1 = {verjetnosti[1], 1 - verjetnosti[1]};
    std::vector<std::vector<double>> polinomi = sestaviPolinome(verjetnosti);
    std::vector<double> rezultat = zmnoziRekurzivno(polinomi, 0, polinomi.size() - 1, fft);

    Pk = rezultat;

    return Pk;
}
