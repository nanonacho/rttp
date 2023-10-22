# include "headers.h"
# include "iostream"

using namespace std;

Tournament::Tournament(vector<vector<int>> schedule) {
    this->schedule = schedule;
}

// Function to calculate the total distance traveled by each team 
vector<int> Tournament::calculateTotalDistanceByTeam(vector<vector<int>> distances) {
    vector<int> total_distance_by_team;
    
    for (int i = 0; i < int(distances.size()); i++) {
        total_distance_by_team.push_back(0);
    }

    for (int e = 0; e < int(schedule.size()); e++) {
        int current_loc = e + 1;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            // If the value is negative, it means that the team must travel to opponent home
            if (schedule[e][r] < 0) {
                total_distance_by_team[e] += distances[current_loc - 1][schedule[e][r] * -1 - 1];
                current_loc = schedule[e][r] * -1;
            }
            // If the value is positive, it means that the team must travel to home
            else if (schedule[e][r] > 0) {
                total_distance_by_team[e] += distances[current_loc - 1][e];
                current_loc = e + 1;
            }
        }
        total_distance_by_team[e] += distances[current_loc - 1][e];
    }

    return total_distance_by_team;
}

// Function to verify that the number of consecutive local games for any team is between l and u
// Returns 1 if the condition is met, 0 otherwise
int Tournament::verifyConsecutiveLocalGamesBounds(int l, int u) {
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_local_games = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] > 0) {
                consecutive_local_games++;
                if (consecutive_local_games < l || consecutive_local_games > u) return 0;
            }
            else consecutive_local_games = 0;
        }
    }
    return 1;
}

// Function to verify that the number of consecutive away games for any team is between l and u
// Returns 1 if the condition is met, 0 otherwise
int Tournament::verifyConsecutiveAwayGamesBounds(int l, int u) {
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_away_games = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] < 0) {
                consecutive_away_games++;
                if (consecutive_away_games < l || consecutive_away_games > u) return 0;
            }
            else consecutive_away_games = 0;
        }
    }
    return 1;
}

// Function to verify that maximum number of consecutive games for any team is b
// Returns 1 if the condition is met, 0 otherwise
int Tournament::verifyConsecutiveMaxGames(int b) {
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_games = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] != 0) {
                consecutive_games++;
                if (consecutive_games > b) return 0;
            }
            else consecutive_games = 0;
        }
    }
    return 1;
}

// Function to verify that maximum number of consecutive byes for any team is o
// Returns 1 if the condition is met, 0 otherwise
int Tournament::verifyConsecutiveMaxByes(int o) {
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_byes = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] == 0) {
                consecutive_byes++;
                if (consecutive_byes > o) return 0;
            }
            else consecutive_byes = 0;
        }
    }
    return 1;
}

// Function to verify that all constraints are met
// Returns 1 if all constraints are met, 0 otherwise
int Tournament::verifyAllConstraints(Instance instance) {
    if (verifyConsecutiveLocalGamesBounds(instance.getL(), instance.getU()) == 0) return 0;
    if (verifyConsecutiveAwayGamesBounds(instance.getL(), instance.getU()) == 0) return 0;
    if (verifyConsecutiveMaxGames(instance.getB()) == 0) return 0;
    if (verifyConsecutiveMaxByes(instance.getO()) == 0) return 0;
    return 1;
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