# include <string>
# include <vector>

using namespace std;

class Instance {
public:
    Instance(int n, int l, int u, int b, int o, vector<vector<int>> distances);
    int getN();
    int getL();
    int getU();
    int getB();
    int getO();
    vector<vector<int>> getDistances();
    void print();

private:
    int n;
    int l;
    int u;
    int b;
    int o;
    vector<vector<int>> distances;
};

Instance readTxtInstance(string filename);

class Tournament {
public:
    Tournament(vector<vector<int>> schedule); 
    vector<int> calculateTotalDistanceByTeam(vector<vector<int>> distances);
    int verifyConsecutiveLocalGamesBounds(int l, int u);
    int verifyConsecutiveAwayGamesBounds(int l, int u);
    int verifyConsecutiveMaxGames(int b);
    int verifyConsecutiveMaxByes(int o);
    int verifyAllConstraints(Instance instance);
    
    void print();
private:
    vector<vector<int>> schedule;
    
};


void greedy(Instance instance);