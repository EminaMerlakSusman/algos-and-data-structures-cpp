#include <string>
#include <vector>
#include <utility>


using std::string;
using std::pair;
using std::vector;
using std::tuple;

typedef pair<int, int> Vozlisce;
typedef pair<Vozlisce, Vozlisce> Povezava;
typedef tuple<vector<Povezava>, int, int> Graf;

class Resitev{

public:
    static int velikostTurnirja(const vector<Povezava> &povezave, int n, int k);
};
