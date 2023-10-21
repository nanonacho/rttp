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
    /*
    int verifyConsecutive(vector<vector<int>> schedule);
    int verifyConsecutiveMinLocalGames(vector<vector<int>> schedule, int l);
    int verifyConsecutiveMinAwayGames(vector<vector<int>> schedule, int l);
    int verifyConsecutiveMaxLocalGames(vector<vector<int>> schedule, int u);
    int verifyConsecutiveMaxAwayGames(vector<vector<int>> schedule, int u);
    int verifyConsecutiveMaxGames(vector<vector<int>> schedule, int b);
    int verifyConsecutiveMaxByes(vector<vector<int>> schedule, int o);
    */
    void print();
private:
    vector<vector<int>> schedule;
    
};


void greedy(Instance instance);