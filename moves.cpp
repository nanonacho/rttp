# include "headers.h"
# include "iostream"

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
    /*
    
    */
    
    Tournament new_tournament = Tournament(schedule);
    return new_tournament;
}

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
    
    
    return best;
}


vector<Tournament> generateNeighborhoodSR(Tournament tournament) {
    vector<Tournament> neighborhood;
    vector<vector<int>> schedule = tournament.getSchedule();
    int n = int(schedule.size());
    
    for (int i = 0; i < 4 * (n - 1); i++) {
        for (int j = i + 1; j < 4 * (n - 1); j++) {
            Tournament new_tournament = swapRounds(tournament, i, j);
            neighborhood.push_back(new_tournament);
        }
    }
    return neighborhood;
}
