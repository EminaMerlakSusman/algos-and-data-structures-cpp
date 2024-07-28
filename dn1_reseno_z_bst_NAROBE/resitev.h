#include <string>
#include "bst.h"
using std::string;


class Resitev {



public:


    /*
    Ukaz je oblike "v 12 1000" (vstavi 1000 ob času 12),
    ali pa         "p 6 100" (poizvedba okoli 100 za čas 6).
    
    Vrne naj odgovor na poizvedbo (če je ukaz poizvedba), ali pa karkoli (npr. 0).
    */
    int obdelaj(const string & ukaz);
    
};