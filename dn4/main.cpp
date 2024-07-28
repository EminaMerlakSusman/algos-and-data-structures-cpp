#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <functional>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <tuple>

#include "resitev.h"

#include <stdio.h>

using std::pair;

using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::vector;

Graf preberiGraf(std::fstream &datoteka, int n, int k, int nPovezav)
{
    vector<Povezava> povezave;
    string vrstica;
    int u1, u2, v1, v2;
    for (int i = 0; i < nPovezav; i++)
    {
        getline(datoteka, vrstica);
        std::istringstream iss(vrstica);
        iss >> u1 >> u2 >> v1 >> v2;
        povezave.push_back(
            std::make_pair(
                std::make_pair(u1, u2),
                std::make_pair(v1, v2)));
    }
    return std::make_tuple(povezave, n, k);
}

vector<Graf> preberiVhod(const string &pot)
{
    vector<Graf> grafi;
    std::fstream datoteka;
    datoteka.open(pot, std::ios::in);
    if (datoteka.is_open())
    {
        string vrstica;
        while (getline(datoteka, vrstica))
        {
            string brezveze;
            int n, k, nPovezav;
            std::istringstream iss(vrstica);
            iss >> brezveze >> n >> k >> nPovezav;
            if (brezveze != "GRAF")
            {
                throw "Nepricakovan zacetek: " + brezveze;
            }
            grafi.push_back(preberiGraf(datoteka, n, k, nPovezav));
        }
        datoteka.close();
    }
    else
    {
        cout << "Nisem mogel prebrati datoteke " << pot << "\nLep pozdrav, tvoj c++" << endl;
    }
    return grafi;
}

vector<int> preberiIzhod(const string &pot)
{
    vector<int> velikosti;
    std::fstream datoteka;
    datoteka.open(pot, std::ios::in);
    if (datoteka.is_open())
    {
        string vrstica;
        while (getline(datoteka, vrstica))
        {
            int n;
            std::istringstream iss(vrstica);
            iss >> n;
            velikosti.push_back(n);
        }
        datoteka.close();
    }
    else
    {
        cout << "Nisem mogel prebrati datoteke " << pot << "\nLep pozdrav, tvoj c++" << endl;
    }
    return velikosti;
}

bool preveriPravilnostEne(int i, const int &resitev, const int &odgovor)
{
    bool jeOK = resitev == odgovor;
    if (!jeOK)
    {
        cout << "Resitev ni pravilna. Prva napaka se zgodi pri poizvedbi i = " << i << " (>= 0)." << endl;
        cout << "Pravilen odgovor = " << resitev << " != " << odgovor << endl;
        return false;
    }
    return jeOK;
}

void preveri(const string &naloga, long long maxT)
{
    cout << "Preverjam " << naloga << endl;
    auto podatki = preberiVhod(naloga + ".in");
    auto resitve = preberiIzhod(naloga + ".out");
    if (podatki.size() != resitve.size())
    {
        cout << "Stevilo vprasanj (" << podatki.size() << ") in odgovorov (" << resitve.size() << ") se ne ujemata." << endl;
        return;
    }
    int iPoizvedba = 0;
    auto t0 = std::chrono::high_resolution_clock::now();
    bool jeOK = true;
    for (const auto &verjetnosti : podatki)
    {
        cout << "    graf #" << iPoizvedba << endl;
        auto const &[povezave, n, k] = podatki[iPoizvedba];
        auto odgovor = Resitev::velikostTurnirja(povezave, n, k);
        jeOK = preveriPravilnostEne(iPoizvedba, resitve[iPoizvedba], odgovor);
        if (!jeOK)
        {
            cout << "Prekinjam preverjanje." << endl;
            break;
        }
        iPoizvedba++;
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    auto trajanje = (std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0)).count() / 1000;
    string glagol = trajanje < maxT ? "leti kot sneta sekira" : "je prepocasna";
    cout << "Resitev " << glagol << ": trajala je " << trajanje << "ms";
    cout << " (dovoljeno: " << maxT << " ms)" << endl;
    if (jeOK){
        cout << "Resitev je pravilna." << endl;
    }
    
}

long long izracunajMaxT()
{
    auto t0 = std::chrono::high_resolution_clock::now();
    int vsota = 0;
    for (int i = 0; i < 1; i++)
    {
        for (int j = i; j >= -i; j--)
        {
            vsota += (i + j) / 2;
        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    auto trajanje = (std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0)).count() / 1000;
    return trajanje;
}


int main()
{
    auto maxT = 10 * 60 * 1000;   // izracunajMaxT();
    vector<string> naloge = {"nalogaA0", "nalogaA1"};
    for (auto const &naloga : naloge)
    {
        preveri(naloga, maxT);
        cout << endl;
    }
    return 0;
}
