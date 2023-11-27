# include "headers.h"
# include "iostream"
# include <ctime>
# include <chrono>
# include <unistd.h>

// Function to improve a initial solution of RTTP usign hill climbing first improvement
// Returns the best solution found
Tournament hillClimbingFI(Tournament initial_solution, Instance instance, int iter) {
    Tournament best_solution = initial_solution;
    
    int count = 0;
    // Hill climbing first improvement
    for (int i = 0; i < iter; i++) {
        Tournament neighbor = hyperMove(best_solution, instance);
        
        // Check if the local optimum has been reached
        if (neighbor.calculateFitness(instance) < best_solution.calculateFitness(instance)) {
            best_solution = neighbor;
            count++;
        }
        else {
            break;
        }
        
        // Print best solution
        cout << "Iteration: " << i + 1 << endl;
        cout << "Fitness: " << best_solution.calculateFitness(instance) << endl;
        best_solution.print();
    }

    cout << "Number of improvements: " << count << endl;

    return best_solution;
}

Tournament HCFI(Instance instance, int n_iter, int n_restarts, int seed) {
    // Generate initial solution
    Tournament best_solution = initialSolution(instance, seed);
    int fitness_best_solution = 1000000000;

    // Variable to store the max number of improvements of the best solution
    int iter_best_solution = 0;

    // Manage restarts
    for (int i = 0; i <= n_restarts; i++) {
        // Generate a new initial solution
        Tournament actual_solution = initialSolution(instance, 11 * (i + 1) + seed);
        // Variable to store the number of improvements
        int actual_iter = 0;

        // Apply hill climbing first improvement
        for (int i = 0; i < n_iter; i++) {
            Tournament next_solution = hyperMove(actual_solution, instance);
            
            // Check if the local optimum has been reached
            if (next_solution.calculateFitness(instance) < actual_solution.calculateFitness(instance)) {
                actual_solution = next_solution;
                actual_iter++;
            }
            else {
                break;
            }
        }

        int fitness_actual_solution = actual_solution.calculateFitness(instance);
        // Check if there is a better solution
        if (fitness_actual_solution < fitness_best_solution) {
            fitness_best_solution = fitness_actual_solution;
            best_solution = actual_solution;
            iter_best_solution = actual_iter;
        }
    }
    // Set the improvements number of the best solution
    best_solution.setImprovements(iter_best_solution);

    return best_solution;
}