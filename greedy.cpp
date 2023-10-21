# include <iostream>
# include <vector>
# include "headers.h"
using namespace std;

void greedy(Instance instance) {
    vector<vector<int>> distance = instance.getDistances();

    int n = instance.getN();
    
    // Aux variables
    int current_loc[n] = {0, 1, 2, 3};
    int last_op[n] = {0, 0, 0, 0};
    int byes[n] = {0, 0, 0, 0};
    int home_consecutive[n] = {0, 0, 0, 0};
    int away_consecutive[n] = {0, 0, 0, 0};

    int match_assigned[n][n] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    int sol[n][4 * (n - 1)] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Rounds
    for (int r = 0; r < 4 * (n - 1); r++) {
        int team_assigned[n] = {0, 0, 0, 0};

        // Teams
        for (int e = 0; e < n; e++) {
            // If team already assigned, skip
            if (team_assigned[e] == 1) {
                cout << "Team " << e << " already assigned" << endl;
                continue;
            }

            int min = 100000;
            int min_index = -9;
            
            // Opponents
            for (int op = 0; op < n; op++) {

                if (distance[e][op] + distance[current_loc[e]][e] < min && match_assigned[e][op] == 0 && team_assigned[op] == 0 && e != op) {
                    min = distance[e][op] + distance[current_loc[e]][e];
                    min_index = op;
                }
            }

            if (min_index == -9) {
                cout << "No opponent found for team " << e << endl;
                continue;
            }

            // Assign opponent
            match_assigned[e][min_index] = 1;
            team_assigned[e] = 1;
            team_assigned[min_index] = 1;
            
            // Update aux variables
            last_op[e] = min_index;
            last_op[min_index] = e;
            current_loc[e] = e;
            current_loc[min_index] = e;

            // Update solution
            sol[e][r] = -min_index;
            sol[min_index][r] = e;

            cout << "Round: " << r << " Team: " << e << " Opponent: " << min_index << endl;

            // Print all aux variables
            cout << "Current loc: ";
            for (int i = 0; i < n; i++) {
                cout << current_loc[i] << " ";
            }
            cout << endl;
            cout << "Last op: ";
            for (int i = 0; i < n; i++) {
                cout << last_op[i] << " ";
            }
            cout << endl;
            cout << "team_assigned: ";
            for (int i = 0; i < n; i++) {
                cout << team_assigned[i] << " ";
            }
            cout << "\n"<< endl;

            }
        }
            
    // print solution
    for (int e = 0; e < n; e++) {
        for (int r = 0; r < 4 * (n - 1); r++) {
            cout << sol[e][r] << " ";
        }
        cout << endl;
    }
    // print total distances for each team
    for (int e = 0; e < n; e++) {
        int total = 0;
        for (int r = 0; r < 4 * (n - 1); r++) {
            if (sol[e][r] < 0) {
                total += distance[e][-sol[e][r]];
            } else {
                total += distance[e][sol[e][r]];
            }
        }
        cout << "Total distance for team " << e << ": " << total << endl;
    }
}