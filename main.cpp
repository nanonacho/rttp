# include "headers.h"
# include "iostream"
# include <ctime>
# include <chrono>

int main(int argc, char const *argv[]) {
    // Check arguments
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <instance.txt>" << " <iterations>" << " <restarts>" << endl;
        return 1;
    }

    // Read instance 
    Instance selectedInstance = readTxtInstance(argv[1]);

    cout << "-------------------------------------------------"<< endl;
    cout << "Solution: " << endl;

    // Apply hill climbing first improvement and measure execution time
    auto start = chrono::high_resolution_clock::now();
    Tournament best_solution = HCFI(selectedInstance, stoi(argv[2]), stoi(argv[3]), time(0));
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    
    // Print results
    cout << "Total Distance: " << best_solution.calculateTotalDistance(selectedInstance.getDistances()) << endl;
    cout << "Fitness: " << best_solution.calculateFitness(selectedInstance) << endl;
    cout << "Number of violated constraints: " << best_solution.calculateConstraintsViolated(selectedInstance) << endl;
    cout << "Execution time: " << duration.count() * 1e-3  << " s" << endl;
    cout << "Number of iterations achieved: " << best_solution.getImprovements() << endl;
    cout << "-------------------------------------------------"<< endl;
    
    // Write results to file
    best_solution.writeToTxt("results.txt", selectedInstance, duration.count());

    return 0;
}
