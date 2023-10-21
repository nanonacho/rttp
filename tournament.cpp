# include "headers.h"
# include "iostream"

using namespace std;

Tournament::Tournament(vector<vector<int>> schedule) {
    this->schedule = schedule;
}

vector<int> Tournament::calculateTotalDistanceByTeam(vector<vector<int>> distances) {
    vector<int> total_distance_by_team;
    
    for (int i = 0; i < int(distances.size()); i++) {
        total_distance_by_team.push_back(0);
    }

    for (int e = 0; e < int(schedule.size()); e++) {
        int current_loc = e + 1;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            
            if (schedule[e][r] < 0) {
                total_distance_by_team[e] += distances[current_loc - 1][schedule[e][r] * -1 - 1];
                current_loc = schedule[e][r] * -1;
            }
            else if (schedule[e][r] > 0) {
                total_distance_by_team[e] += distances[current_loc - 1][e];
                current_loc = e + 1;
            }
        }
        total_distance_by_team[e] += distances[current_loc - 1][e];
    }

    return total_distance_by_team;
}

void Tournament::print() {
    int i = 1;
    for (vector<int> row : schedule) {
        cout << i++ << ": ";
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    cout << endl;
}