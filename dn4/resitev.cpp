#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <bitset>
#include "resitev.h"

using std::unordered_map;
using std::unordered_set;
using std::bitset;
using std::cout;
using std::endl;

typedef unordered_map<Vozlisce, unordered_set<Vozlisce>> NeusmerjenGraf;

std::hash<int> intHash;

template <>
struct std::hash<Vozlisce>
{
 std::size_t operator()(const pair<int, int> &par) const
 {
    // to je samo ena od moznih implementacij ...
   return intHash(par.first) ^ intHash(par.second);
 }
};


/*
Pretvori vektor povezav v {vozlisce: {sosed1, sosed2, ...}}.
To lahko mirno pobrišete, če se vam zdi nepotrebno.
Če ne bi imeli funkcije hash za Vozlisce (pair<int, int>),
bi se tukaj zgodila napaka.
*/
NeusmerjenGraf pretvoriVGraf(const vector<Povezava> &povezave)
{
    NeusmerjenGraf graf;
    for (auto const &povezava : povezave)
    {
        auto u = povezava.first;
        auto v = povezava.second;
        graf[u].insert(v);
        graf[v].insert(u);
    }
    return graf;
}
//**********************************FUNKCIJE ZA HIERARHIJO****************************
// Definicija hierarhije enot {enota : {podrejena enota 1, podrejena enota 2, ...}}
typedef unordered_map<int, unordered_set<int>> HierarhijaEnot;

// Seznam vseh možnih hierarhij npr [{0 : {1, 2}}, {0: {1, 3}}, {1: {3}}]
typedef vector<HierarhijaEnot> SeznamHierarhij;

// DFS za hierarhijo
void dfs(const Vozlisce &v, NeusmerjenGraf &graf, unordered_map<int, bool> &obiskaneEnote, HierarhijaEnot &hierarhija) {
    obiskaneEnote[v.first] = true;
    for (auto& sosed : graf[v]) {
        if (v.first != sosed.first) { // če sta v različnih enotah,
            if (v.first < sosed.first) { // je manjši indeks v podrejeni enoti
                hierarhija[v.first].insert(sosed.first);
            }
        }
        if (!obiskaneEnote[sosed.first]) {
            dfs(sosed, graf, obiskaneEnote, hierarhija);
        }
    }
}

// Zgradi hierarhijo enot
SeznamHierarhij zgradiHierarhije(NeusmerjenGraf &graf, int n) {
    unordered_map<int, bool> obiskaneEnote;
    for (auto& vozlisce : graf) {
        obiskaneEnote[vozlisce.first.first] = false;
    }
    SeznamHierarhij hierarhije;

    // Sprehodi se po vseh vozliščih
    for (auto& vozlisce: graf) {
        if (!obiskaneEnote[vozlisce.first.first]) {
            HierarhijaEnot novaHierarhija;
            dfs(vozlisce.first, graf, obiskaneEnote, novaHierarhija);
            hierarhije.push_back(novaHierarhija);
        }
    }
    return hierarhije;
}
// ************************************************************************************

//************FUNKCIJE ZA ISKANJE SUBSETOV*********************************************
// Najde podmnožice dolžine k
vector<bitset<8>> seznamPodmnozic(int k)
{
    vector<bitset<8>> seznam_podmnozic;
    // bit manipulation
    for (int i = 0; i < (1 << k); i++) {
        bitset<8> podmnozica(i);
        seznam_podmnozic.push_back(podmnozica);
    }
    return seznam_podmnozic;
    }

// Preveri če bitmask predstavlja neodvisno množico
bool jeNeodvisna(bitset<8> subsetMask, const NeusmerjenGraf& graf, int enota) {
    for (int i = 0; i < 8; ++i) {
        if (!subsetMask[i]) continue;  // če i ni v subsetu, skip
        for (int j = i + 1; j < 8; ++j) {
            if (!subsetMask[j]) continue;  // če j ni v subsetu, skip
            Vozlisce a(enota, i), b(enota, j);
            if (graf.count(a) > 0 && graf.at(a).count(b) > 0) {
                return false;
            }
        }
    }
    return true;
}

bitset<8> dobiSosede(bitset<8> S, const NeusmerjenGraf& graf, int podrejena_enota, int nadrejena_enota) {
    bitset<8> sosedi;

    for (int i = 0; i < 8; ++i) {
        if (!S[i]) continue;  // če i-ti element ni v S, skip
        Vozlisce a(nadrejena_enota, i);
        for (int j = 0; j < 8; ++j) {
            Vozlisce b(podrejena_enota, j);
            if (graf.count(a) > 0 && graf.at(a).count(b) > 0) {  // Če je povezava med a in b
                sosedi.set(j);  // Označi b kot soseda od S
            }
        }
    }

    return sosedi;
}

struct BitSetHash {
    std::size_t operator()(const std::bitset<8>& bitset) const {
        return bitset.to_ulong();
    }
};


typedef unordered_map<bitset<8>, int, BitSetHash> SubsetMap;

vector<SubsetMap> dobiMaxNeodvisnoMnozico(const NeusmerjenGraf& graf, const HierarhijaEnot& hierarhija, int n, int k) {
    // Matrika ki vsebuje velikost največje neodvisne množice za vsak Y in vsako enoto
    vector<SubsetMap> c(n);

    for (auto& map : c) {
        for (int i = 0; i < (1<<k); ++i) {
            map[bitset<8>(i)] = 0;
        }
    }

    // dobi vse subsete S za računat c[i][Y]
    auto podmnozice_S = seznamPodmnozic(k);

    // izračunaj vrednosti c[i][j] za vse enote od listov navzgor
    for (int i = n - 1; i >= 0; --i) {
        // za vsak možen subset Y (kot bitset<8>)
        for (int j = 0; j < (1<<k); ++j) {
            bitset<8> Y(j);
            // izračunaj vse subsete X \ Y
            for (auto& S : podmnozice_S) {
                if ((S & Y) == 0 && jeNeodvisna(S, graf, i)) {  // če je S NEODVISNA podmnožica X \ Y
                    int vsota = S.count();  // dodaj S.count, kar je število enk v S
                    // za vsako child enoto i-ja, dodaj maksimalne vsote te child enote brez sosedov od S
                    if (hierarhija.count(i) > 0) { // če sploh ma childe
                    for (auto& podrejena_enota : hierarhija.at(i)) {
                        bitset<8> sosedi = dobiSosede(S, graf, podrejena_enota, i);
                        vsota += c[podrejena_enota][sosedi]; // c ki excluda sosede v podrejeni_enoti
                        }
                    // updataj c[i][Y] če je vsota večja
                    c[i][Y] = std::max(c[i][Y], vsota);
                    
                }
            }
        }
    }

    
    }
    return c;

}

int Resitev::velikostTurnirja(const vector<Povezava> &povezave, int n, int k) {
    auto graf = pretvoriVGraf(povezave);
    SeznamHierarhij seznamHierarhij = zgradiHierarhije(graf, n);

    // X_i je množica elementov i-te enote. Gremo po istem principu kot za
    // weighted independent set v gridu.
    // Če smo v listu (enoti na dnu piramide), za Y <= X_i, zgeneriramo vse
    // subsete S <= X_i \ Y. Pol je c[i, Y] = max (sum(S)).
    // Če nismo v listu, je rekurzivna zveza: c[i, Y] = max (sum(S) + c[j, N(S) && X_j]), X_j njegovi otroci

    int vsota_po_poddrevesih = 0;
    for (auto& hierarhijaEnot: seznamHierarhij) {
        vector<SubsetMap> c = dobiMaxNeodvisnoMnozico(graf, hierarhijaEnot, n, k);
        bitset<8> Y;  // Empty set
        // cout << c[0][Y] << endl;
        int najvecja_podmnozica = 0;
        for (SubsetMap& map : c) {
        for (auto& pair : map) {
            bitset<8> key = pair.first;
            int value = pair.second;
            if (value > najvecja_podmnozica) {
                najvecja_podmnozica = value;
            }
        }
        }
        vsota_po_poddrevesih += najvecja_podmnozica;
        
     }
    return vsota_po_poddrevesih;
    }

    

