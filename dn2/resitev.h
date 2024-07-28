#include <string>
#include <vector>
#include <unordered_map>
#include "sip.h"


using std::vector;
using std::string;


class Resitev {
private:
    vector<long long> emsoOtrok; // declare the member variable
    std::unordered_map<long long, int> emsoti_z_indeksi; // hashmap emšoti v indekse
    vector<int> seznam_vozlisc; //seznam vozlisc drevesa, na začetku samo integerj 0 do len(emsoOtrok)
    VsotaZGlavo vsota_z_glavo_instance = VsotaZGlavo(seznam_vozlisc);
public:
    // potrebujemo (tudi) tak konstruktor
    Resitev(vector<long long> emsoOtrok);

    // in tako metodo obdelaj
    int obdelaj(const string & ukaz);
    std::unordered_map<long long, int> naredi_hash_map(vector<long long> emsoOtrok);
};