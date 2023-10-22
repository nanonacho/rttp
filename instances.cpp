# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include "headers.h"

using namespace std;

Instance::Instance(int n, int l, int u, int b, int o, vector<vector<int>> distances) {
    this->n = n;
    this->l = l;
    this->u = u;
    this->b = b;
    this->o = o;
    this->distances = distances;
}

int Instance::getN() {
    return n;
}

int Instance::getL() {
    return l;
}

int Instance::getU() {
    return u;
}

int Instance::getB() {
    return b;
}

int Instance::getO() {
    return o;
}

vector<vector<int>> Instance::getDistances() {
    return distances;
}

void Instance::print() {
    cout << "n: " << n << endl;
    cout << "\n" << endl;
    cout << "l: " << l << endl;
    cout << "u: " << u << endl;
    cout << "b: " << b << endl;
    cout << "o: " << o << endl;
    cout << "\n" << endl;
    int i = 0;
    for (vector<int> row : distances) {
        cout << i++ << ": ";
        for (int distance : row) {
            cout << distance << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to read a .txt instance file and return an Instance object
Instance readTxtInstance(string filename) {
    ifstream file(filename);
    string line;
    int n, l, u, b, o;
    vector<vector<int>> distances;

    if (file.is_open()) {
        getline(file, line);
        n = stoi(line.substr(2));

        getline(file, line);

        getline(file, line);
        l = stoi(line.substr(2));

        getline(file, line);
        u = stoi(line.substr(2));

        getline(file, line);
        b = stoi(line.substr(2));

        getline(file, line);
        o = stoi(line.substr(2));

        getline(file, line);

        for (int i = 0; i < n; i++) {
            getline(file, line);
            stringstream ss(line);
            vector<int> row;
            for (int j = 0; j < n; j++) {
                int distance;
                ss >> distance;
                row.push_back(distance);
            }
            distances.push_back(row);
        }  
    } 
    else {
        cout << "Unable to open file" << endl;
    }

    return Instance(n, l, u, b, o, distances);
}


