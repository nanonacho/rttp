# include "headers.h"
# include "iostream"

using namespace std;

int main(int argc, char const *argv[]) {
    Instance selectedInstance = readTxtInstance(argv[1]);
    selectedInstance.print();

    vector<vector<int>> schedule = {
        {-2, 0, 0, 4, 0, 3, 0, 0, 2, 0, -4, 0, -3},
        {1, 0, -4, 0, -3, 0, 0, 0, -1, 3, 0, 0, 4},
        {-4, 0, 0, 0, 2, -1, 0, 0, 4, -2, 0, 0, 1},
        {3, 0, 2, -1, 0, 0, 0, 0, -3, 0, 1, 0, -2}
    };

    Tournament tournament = Tournament(schedule);
    
    vector<int> total_distance_by_team = tournament.calculateTotalDistanceByTeam(selectedInstance.getDistances());
    for (int i = 0; i < int(total_distance_by_team.size()); i++) {
        cout << total_distance_by_team[i] << " ";
    }
    cout << endl;

    cout << tournament.verifyConsecutiveMaxByes(selectedInstance.getO()) << endl;   
    cout << tournament.verifyConsecutiveMaxGames(selectedInstance.getB()) << endl;
    cout << tournament.verifyConsecutiveLocalGamesBounds(selectedInstance.getL(), selectedInstance.getU()) << endl;
    cout << tournament.verifyConsecutiveAwayGamesBounds(selectedInstance.getL(), selectedInstance.getU()) << endl;
    cout << tournament.verifyAllConstraints(selectedInstance) << endl;
    
    tournament.print();
    /*greedy(instance4);*/
    return 0;
}