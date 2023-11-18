# include <vector>
# include <string>

using namespace std;

// instance.cpp
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

// tournament.cpp
class Tournament {
public:
    Tournament(vector<vector<int>> schedule); 
    vector<vector<int>> getSchedule();
    vector<int> calculateTotalDistanceByTeam(vector<vector<int>> distances);
    int calculateTotalDistance(vector<vector<int>> distances);
    int verifyConsecutiveLocalGamesBounds(int l, int u);
    int verifyConsecutiveAwayGamesBounds(int l, int u);
    int verifyConsecutiveMaxGames(int b);
    int verifyConsecutiveMaxByes(int o);
    int countViolationsConsecutiveLocalGamesBounds(int l, int u);
    int countViolationsConsecutiveAwayGamesBounds(int l, int u);
    int countViolationsConsecutiveMaxGames(int b);
    int countViolationsConsecutiveMaxByes(int o);
    int verifyAllConstraints(Instance instance);
    int countAllViolations(Instance instance);
    int calculateConstraintsViolated(Instance instance);
    int calculateFitness(Instance instance);
    int calculateAverageDistance(vector<vector<int>> distances);
    
    void print();
private:
    vector<vector<int>> schedule;
    
};

// initial_solution.cpp
Tournament initialSolution(Instance instance, int random_seed);

// moves.cpp
Tournament swapRounds(Tournament tournament, int round1, int round2);
Tournament swapHomes(Tournament tournament, int team1, int team2);
Tournament swapTeams(Tournament tournament, int team1, int team2);
Tournament hyperMove(Tournament tournament, Instance instance);

// hc.cpp
Tournament hillClimbingFI(Tournament initial_solution, Instance instance, int iter);

// test.cpp
void testHC(int restarts, int n_iter, Instance instance);