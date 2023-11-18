# include "headers.h"
# include "iostream"

// Function to improve a initial solution of RTTP usign hill climbing first improvement
// Returns the best solution found
Tournament hillClimbingFI(Tournament initial_solution, Instance instance, int iter) {
    Tournament best_solution = initial_solution;
    
    // Print initial solution
    cout << "Iteration: " << 0 << endl;
    cout << "Fitness: " << best_solution.calculateFitness(instance) << endl;
    best_solution.print();


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