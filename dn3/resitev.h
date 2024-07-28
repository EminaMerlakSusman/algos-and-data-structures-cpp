#include <vector>
#include <string>
using std::vector;
using std::string;


class Resitev{

public:
    /*
    Metoda sprejme vektor verjetnosti p_i in vrne vektor verjetnosti P_k,
    ki je za ena daljši od vhodnega vektorja.
    */
    static vector<double> izracunajVerjetnosti(const vector<double> & verjetnosti, string naloga);
};