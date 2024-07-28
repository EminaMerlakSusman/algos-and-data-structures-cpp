#include <vector>
#include <utility>
#include <memory>
#include <queue>
#include <stdexcept>

using std::vector;
using std::pair;
struct NodeDistance;
class KDDrevo {

    bool jeList = true;
    int dimenzija;
    double mediana;
    vector<double> tocka;
    std::unique_ptr<KDDrevo> levo; // brez kazalca ne moremo vedeti, koliko spomina porabi KDDrevo
    std::unique_ptr<KDDrevo> desno;

public:
    KDDrevo();
    KDDrevo(const vector<vector<double>> & xs, const int dimenzija);
    ~KDDrevo();

    pair<vector<double>, double> najdi(const vector<double> & x) const;
    pair<vector<double>, double> najdiPomoc(
        const vector<double> & x, 
        const std::unique_ptr<KDDrevo> & glavno,
        const std::unique_ptr<KDDrevo> & drugo
    ) const;

    vector<vector<double>> tocke() const;
        
    static double izracunajMediano(const vector<vector<double>> & xs, const int dimension);
    static double izracunajEvklidsko2(const vector<double> & x0, const vector<double> & x1);

    static std::unique_ptr<KDDrevo> narediDrevo(const vector<vector<double>> & xs, const int dimenzija);
    vector<pair<vector<double>, double>> kNajblizjih(const vector<double> & x, int k) const;
    void najdiKBliznjih(const vector<double> & x, int k, std::priority_queue<NodeDistance> & heap) const;

};


class KDDSemidinamicno {
    vector<std::unique_ptr<KDDrevo>> drevesa;
    std::unique_ptr<KDDrevo> zadnje_drevo;

public:
    KDDSemidinamicno();


    
    void vstavi(const vector<double> & x);
    pair<vector<double>, double> najdi(const vector<double> & x) const;
    std::unique_ptr<KDDrevo>& getZadnjeDrevo() {
        if (zadnje_drevo == nullptr) {
        KDDrevo zadnje_drevo = KDDrevo.narediDrevo();
    }
        return zadnje_drevo;
    }
private:
    //std::unique_ptr<KDDrevo> zadnje_drevo;
};