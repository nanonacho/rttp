# include "headers.h"
# include "iostream"
# include "iomanip"
# include "cmath"

Tournament::Tournament(vector<vector<int>> schedule) {
    this->schedule = schedule;
}

vector<vector<int>> Tournament::getSchedule() {
    return schedule;
}

// Function to calculate the total distance traveled by each team 
// Returns a vector<int> that contains total distance traveled by each team 
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

// Function to calculate the total distance traveled by all teams
// Returns the total distance traveled by all teams
int Tournament::calculateTotalDistance(vector<vector<int>> distances) {
    vector<int> total_distance_by_team = calculateTotalDistanceByTeam(distances);
    int total_distance = 0;

    for (int i = 0; i < int(total_distance_by_team.size()); i++) {
        total_distance += total_distance_by_team[i];
    }

    return total_distance;
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
            else if (schedule[e][r] < 0) consecutive_local_games = 0;
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
            else if (schedule[e][r] > 0) consecutive_away_games = 0;
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

// Function to count the number of consecutive local games violations
// Returns the number of violations
int Tournament::countViolationsConsecutiveLocalGamesBounds(int l, int u) {
    int count = 0;
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_local_games = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] > 0) {
                consecutive_local_games++;
                if (consecutive_local_games < l || consecutive_local_games > u) count++;
            }
            else if (schedule[e][r] < 0) consecutive_local_games = 0;
        }
    }
    return count;
}

// Function to count the number of consecutive away games violations
// Returns the number of violations
int Tournament::countViolationsConsecutiveAwayGamesBounds(int l, int u) {
    int count = 0;
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_away_games = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] < 0) {
                consecutive_away_games++;
                if (consecutive_away_games < l || consecutive_away_games > u) count++;
            }
            else if (schedule[e][r] > 0) consecutive_away_games = 0;
        }
    }
    return count;
}

// Function to count the number of consecutive games violations
// Returns the number of violations
int Tournament::countViolationsConsecutiveMaxGames(int b) {
    int count = 0;
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_games = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] != 0) {
                consecutive_games++;
                if (consecutive_games > b) count++;
            }
            else consecutive_games = 0;
        }
    }
    return count;
}

// Function to count the number of consecutive byes violations
// Returns the number of violations
int Tournament::countViolationsConsecutiveMaxByes(int o) {
    int count = 0;
    for (int e = 0; e < int(schedule.size()); e++) {
        int consecutive_byes = 0;

        for (int r = 0; r < int(schedule[e].size()); r++) {
            if (schedule[e][r] == 0) {
                consecutive_byes++;
                if (consecutive_byes > o) count++;
            }
            else consecutive_byes = 0;
        }
    }
    return count;
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

// Function to calculate the number of constraints violated
// Returns the number of constraints violated
int Tournament::calculateConstraintsViolated(Instance instance) {
    int constraints_violated = 0;

    if (verifyConsecutiveLocalGamesBounds(instance.getL(), instance.getU()) == 0) constraints_violated++;
    if (verifyConsecutiveAwayGamesBounds(instance.getL(), instance.getU()) == 0) constraints_violated++;
    if (verifyConsecutiveMaxGames(instance.getB()) == 0) constraints_violated++;
    if (verifyConsecutiveMaxByes(instance.getO()) == 0) constraints_violated++;

    return constraints_violated;
}

// Function to count the number of total constraints violations
// Returns the number of total constraints violations
int Tournament::countAllViolations(Instance instance) {
    int l = instance.getL();
    int u = instance.getU();
    int b = instance.getB();
    int o = instance.getO();  
    return 
    countViolationsConsecutiveAwayGamesBounds(l, u) +
    countViolationsConsecutiveLocalGamesBounds(l, u) +
    countViolationsConsecutiveMaxByes(o) +
    countViolationsConsecutiveMaxGames(b);
}

// Function to calculate the average distance between teams
// Returns the average distance
int Tournament::calculateAverageDistance(vector<vector<int>> distances) {
    int total_distance = 0;
    int average_distance = 0;

    for (int i = 0; i < int(distances.size()); i++) {
        for (int j = 0; j < int(distances[i].size()); j++) {
            total_distance += distances[i][j];
        }
    }

    average_distance = total_distance / (int(distances.size()) * int(distances[0].size()));

    return average_distance;
}

// Function to calculate the fitness
// Returns the fitness 
int Tournament::calculateFitness(Instance instance) {
    int total_distance = calculateTotalDistance(instance.getDistances());
    // Penalizations
    int constraints_violated = countAllViolations(instance);
    int average_distance = calculateAverageDistance(instance.getDistances());

    /*
    if (constraints_violated == 0) return total_distance;
    else return sqrt(pow(total_distance, 2) + pow(average_distance * (1 + sqrt(constraints_violated) * log(constraints_violated) / 2), 2));
    */
   return total_distance + average_distance * constraints_violated;
}

void Tournament::print() {
    int i = 1;
    for (vector<int> row : schedule) {
        cout << setw(2) << i++ << ": ";
        for (int element : row) {
            cout << setw(3) << element << " ";
        }
        cout << endl;
    }
    cout << endl;
}
