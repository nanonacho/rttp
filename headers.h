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

void greedy(Instance instance);