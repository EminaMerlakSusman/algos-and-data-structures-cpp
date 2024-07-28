#include <algorithm>
#include <iostream>
#include "resitev.h"


using std::cout;
using std::endl;

Resitev::Resitev(vector<long long> emsoOtrok) {
    this->emsoOtrok = emsoOtrok; // assign the constructor parameter to the member variable
    this->emsoti_z_indeksi = this->naredi_hash_map(emsoOtrok);
    this->vsota_z_glavo_instance = VsotaZGlavo(this->seznam_vozlisc);
    //this->vsota_z_glavo_instance.sprintaj_vozlisca();
}

std::unordered_map<long long, int> Resitev::naredi_hash_map(vector<long long> emsoOtrok) {
    // naredi slovar, kjer so ključi posamezne vpisne številke,
    // vrednosti pa indeksi vpisnih številk.
    // To je dobr zato kr potem ko dobimo poizvedbo lahka hitr
    // ugotovimo na katerem indeksu v vrsti nej bi se nahajala
    // ta vpisna številka.
    std::unordered_map<long long, int> emsoti_z_indeksi;

    for (int i = 0; i < emsoOtrok.size(); i++) {
        emsoti_z_indeksi.insert({emsoOtrok[i], i});
        this->seznam_vozlisc.push_back(i);
    }
    //cout << "insertano, začetno stanje vozlišč:" << endl;
    
    return emsoti_z_indeksi;
}

int Resitev::obdelaj(const string & ukaz){
    
    if (ukaz[0] == 'p'){
    // extract vpisna0
    size_t pos = ukaz.find(' ');
    long long vpisna0 = std::stoll(ukaz.substr(ukaz.find(' ')+1));

    // extract vpisna1
    size_t pos1 = ukaz.find(' ', pos+1); 
    long long vpisna1 = std::stoll(ukaz.substr(pos1+1));

    size_t pos2 = ukaz.find(' ', pos1+1); 
    int x = std::stoi(ukaz.substr(pos2+1)); 
    int indeks_vpisna0 = emsoti_z_indeksi.at(vpisna0);
    int indeks_vpisna1 = emsoti_z_indeksi.at(vpisna1);
    
    
    vsota_z_glavo_instance.povecaj(indeks_vpisna0, indeks_vpisna1, x);
    /* cout << "povecano stanje" << " ";
    cout << "( " << indeks_vpisna0 << ", ";
    cout << " " << indeks_vpisna1 << ", )x: " << x << endl; */
    //vsota_z_glavo_instance.sprintaj_vozlisca();
    
    } else { // ukaz[0] == 'o'
    // extract vpisna0
    size_t pos = ukaz.find(' ');
    long long vpisna0 = std::stoll(ukaz.substr(ukaz.find(' ')+1)); 

    // extract vpisna1
    size_t pos1 = ukaz.find(' ', pos+1);
    long long vpisna1 = std::stoll(ukaz.substr(pos1+1));
    int indeks_vpisna0 = emsoti_z_indeksi.at(vpisna0);
    int indeks_vpisna1 = emsoti_z_indeksi.at(vpisna1);
    return vsota_z_glavo_instance.odgovori(indeks_vpisna0, indeks_vpisna1);

    }
    return -1;
}
