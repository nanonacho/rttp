# include "headers.h"
# include <iostream>
# include <vector>
# include <algorithm>
#include <ctime>

// Function to create schedule using polygon method and assign byes and local games randomly
// Returns a Tournament with schedule created
Tournament initialSolution(Instance instance) {
    // Seed for random number generator
    srand(time(0));
    
    int n = instance.getN();
    
    // Initialize teams
    vector<int> teams;
    for (int i = 1; i < n; i++) {
        teams.push_back(i);
    }

    // Initialize schedule with 0s
    vector<vector<int>> schedule;
    for (int t = 0; t < n; t++) {
        vector<int> team;
        for (int r = 0; r < 4 * (n - 1); r++) {
            team.push_back(0);
        }
        schedule.push_back(team);
    }

    // Create matches using polygon method and assign byes and local games randomly
    for (int r = 0; r < n - 1; r++) {
        for (int i = 2; i <= n / 2 ; i++) {

            int random = rand() % 2;
            int away_or_local = (random == 0) ? -1 : 1;
            int bye_or_not = rand() % 2;

            // If bye_or_not == 1, then the team will play in the round r but will have a bye in the round r + n - 1
            if (bye_or_not == 1){
                schedule[teams[i - 1] - 1][r] = away_or_local * teams[n - i + 1 - 1];
                schedule[teams[n - i + 1 - 1] - 1][r] = -1 * away_or_local * teams[i - 1];

                schedule[teams[i - 1] - 1][r + 2 * (n - 1)] = -1 * away_or_local * teams[n - i + 1 - 1];
                schedule[teams[n - i + 1 - 1] - 1][r + 2 * (n - 1)] = away_or_local * teams[i - 1];
            }
            else{
                schedule[teams[i - 1] - 1][r + n - 1] = away_or_local * teams[n - i + 1 - 1];
                schedule[teams[n - i + 1 - 1] - 1][r + n - 1] = -1 * away_or_local * teams[i - 1];

                schedule[teams[i - 1] - 1][r + 3 * (n - 1)] = -1 * away_or_local * teams[n - i + 1 - 1];
                schedule[teams[n - i + 1 - 1] - 1][r + 3 * (n - 1)] = away_or_local * teams[i - 1];
            }
        } 
        
        int random = rand() % 2;
        int away_or_local = (random == 0) ? -1 : 1;
        int bye_or_not = rand() % 2;
        
        // If bye_or_not == 1, then the team will play in the round r but will have a bye in the round r + n - 1
        if (bye_or_not == 1) {
            schedule[teams[0] - 1][r] = away_or_local * n;
            schedule[n - 1][r] = -1 * away_or_local * teams[0];

            schedule[teams[0] - 1][r + 2 * (n - 1)] = -1 * away_or_local * n;
            schedule[n - 1][r + 2 * (n - 1)] = away_or_local * teams[0];
        }
        else { 
            schedule[teams[0] - 1][r + n - 1] = away_or_local * n;
            schedule[n - 1][r + n - 1] = -1 * away_or_local * teams[0];

            schedule[teams[0] - 1][r + 3 * (n - 1)] = -1 * away_or_local * n;
            schedule[n - 1][r + 3 * (n - 1)] = away_or_local * teams[0];
        }

        rotate(teams.begin(), teams.end() - 1, teams.end());
        
        //cout << endl;
    }

    Tournament tournament = Tournament(schedule);
    
    return tournament;
} 
