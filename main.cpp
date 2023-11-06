# include "headers.h"
# include "iostream"

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <instance.txt>" << " <iterations>" << " <restarts>" << endl;
        return 1;
    }

    Instance selectedInstance = readTxtInstance(argv[1]);
    cout << "-------------------------------------------------"<< endl;
    cout << "Instance: " << endl;
    selectedInstance.print();
    cout << "-------------------------------------------------"<< endl;
    cout << endl;
    
    Tournament initial_solution = initialSolution(selectedInstance);
    cout << "-------------------------------------------------"<< endl;
    cout << "Initial Solution: " << endl;
    initial_solution.print();
    

    cout << "Total Distance:" << initial_solution.calculateTotalDistance(selectedInstance.getDistances()) << endl;
    cout << "Fitness:" << initial_solution.calculateFitness(selectedInstance) << endl;
    cout << "-------------------------------------------------"<< endl;
    return 0;
}
