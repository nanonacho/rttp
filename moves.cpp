# include "headers.h"
# include "iostream"

// Function to apply swapRounds move to a tournament
// Returns a new tournament with the move applied
Tournament swapRounds(Tournament tournament, int round1, int round2) {
    vector<vector<int>> schedule = tournament.getSchedule();
    int n = int(schedule.size());

    vector<int> aux;
    for (int i = 0; i < n; i++) {
        aux.push_back(schedule[i][round1]);
        schedule[i][round1] = schedule[i][round2];
        schedule[i][round2] = aux[i];
    }
    Tournament new_tournament = Tournament(schedule);
    return new_tournament;
}

// Function to apply swapHomes move to a tournament
// Returns a new tournament with the move applied
Tournament swapHomes(Tournament tournament, int team1, int team2) {
    vector<vector<int>> schedule = tournament.getSchedule();
    int n = int(schedule.size());

    for (int i = 0; i < 4 * (n - 1); i++) {
        if (abs(schedule[team1][i]) == team2 + 1) {
            schedule[team1][i] *= -1;
            schedule[team2][i] *= -1;
        }
    }
    Tournament new_tournament = Tournament(schedule);
    return new_tournament;
}

// Function to apply swapTeams move to a tournament 
// Returns a new tournament with the move applied
Tournament swapTeams(Tournament tournament, int team1, int team2) {
    vector<vector<int>> schedule = tournament.getSchedule();
    int n = int(schedule.size());
    
    for (int i = 0; i < 4 * (n - 1); i++) {
        if (abs(schedule[team1][i]) != team2 + 1) {
            int aux = schedule[team1][i];
            schedule[team1][i] = schedule[team2][i];
            schedule[team2][i] = aux;

            if (schedule[team1][i] > 0) schedule[abs(schedule[team1][i]) - 1][i] = -1 * (team1 + 1);
            else if (schedule[team1][i] < 0) schedule[abs(schedule[team1][i]) - 1][i] = team1 + 1;

            if (schedule[team2][i] > 0) schedule[abs(schedule[team2][i]) - 1][i] = -1 * (team2 + 1);
            else if (schedule[team2][i] < 0) schedule[abs(schedule[team2][i]) - 1][i] = team2 + 1;
        }
    }
    
    Tournament new_tournament = Tournament(schedule);
    return new_tournament;
}

/*
Tournament partialSwapRounds(Tournament tournament, int round1, int round2, int team) {
    vector<vector<int>> schedule = tournament.getSchedule();
    int n = int(schedule.size());

    // Swap the teams for the specified rounds
    int temp = schedule[team][round1];
    schedule[team][round1] = schedule[team][round2];
    schedule[team][round2] = temp;

    // Update the corresponding opponent teams
    for (int i = 0; i < n; i++) {
        if (i != team) {
            if (schedule[i][round1] == team + 1) {
                schedule[i][round1] = schedule[team][round2];
            } else if (schedule[i][round1] == schedule[team][round2]) {
                schedule[i][round1] = team + 1;
            }

            if (schedule[i][round2] == team + 1) {
                schedule[i][round2] = schedule[team][round1];
            } else if (schedule[i][round2] == schedule[team][round1]) {
                schedule[i][round2] = team + 1;
            }
        }
    }

    Tournament new_tournament = Tournament(schedule);
    return new_tournament;
}
*/

// Function to get first improvement applying each move to a tournament and returning the best one
// Returns a new tournament with the move applied
Tournament hyperMove(Tournament tournament, Instance instance) {

    vector<vector<int>> schedule = tournament.getSchedule();
    int tournament_fitness = tournament.calculateFitness(instance);
    int n = instance.getN();

    Tournament best = tournament;

    Tournament best_1 = tournament;
    int best_1_fitness = 1000000000;
    for (int i = 0; i < 4 * (n - 1); i++) {
        for (int j = i + 1; j < 4 * (n - 1); j++) {
            best_1 = swapRounds(tournament, i, j);
            best_1_fitness = best_1.calculateFitness(instance);
            best = best_1;
            if (best_1_fitness < tournament_fitness) break;
        }
        if (best_1_fitness < tournament_fitness) break;
    }

    Tournament best_2 = tournament;
    int best_2_fitness = 1000000000;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            best_2 = swapHomes(tournament, i, j);
            best_2_fitness = best_2.calculateFitness(instance);
            if (best_2_fitness < tournament_fitness) break;
        }
        if (best_2_fitness < tournament_fitness) break;
    }

    if (best_2_fitness < best.calculateFitness(instance)) best = best_2;

    Tournament best_3 = tournament;
    int best_3_fitness = 1000000000;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            best_3 = swapTeams(tournament, i, j);
            best_3_fitness = best_3.calculateFitness(instance);
            if (best_3_fitness < tournament_fitness) break;
        }
        if (best_3_fitness < tournament_fitness) break;
    }

    if (best_3_fitness < best.calculateFitness(instance)) best = best_3;

    /*
    Tournament best_4 = tournament;
    int best_4_fitness = 1000000000;
    for (int i = 0; i < 4 * (n - 1); i++) {
        for (int j = i + 1; j < 4 * (n - 1); j++) {
            for (int k = 0; k < n; k++) {
                best_4 = partialSwapRounds(tournament, i, j, k);
                best_4_fitness = best_4.calculateFitness(instance);
                if (best_4_fitness < tournament_fitness) break;
            }
            if (best_4_fitness < tournament_fitness) break;
        }
        if (best_4_fitness < tournament_fitness) break;
    }

    if (best_4_fitness < best.calculateFitness(instance)) best = best_4;
    */

    return best;
}