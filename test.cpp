# include "headers.h"
# include <iostream>
# include <ctime>

// Function to apply hillClimbingFI with restarts, in each restart the initial solution is different
// Returns the best solution found 
void testHC(int restarts, int n_iter, Instance instance) {
    // Generate initial solution
    Tournament best_solution = initialSolution(instance, time(0));
    int best_fitness = best_solution.calculateFitness(instance);

    // Hill climbing first improvement with restarts
    for (int i = 0; i < restarts; i++) {
        // Generate a new initial solution
        Tournament init = initialSolution(instance, i + 1 + time(0));
        
        // Apply hill climbing first improvement
        Tournament solution = hillClimbingFI(init, instance, n_iter);
        int fitness = solution.calculateFitness(instance);
        
        // Check if there is a better solution
        if (fitness < best_fitness) {
            best_fitness = fitness;
            best_solution = solution;
        }
    }

    // Print best solution
    cout << "Best solution:" << endl;
    best_solution.print();
    cout << "Fitness:" << best_fitness << endl;
    cout << "Distance:" << best_solution.calculateTotalDistance(instance.getDistances()) << endl;
    cout << "Constraints violated:" << best_solution.calculateConstraintsViolated(instance) << endl;
}