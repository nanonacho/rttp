# include "headers.h"
# include <iostream>
# include <ctime>
# include <chrono>

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

void testRestarts(Instance instance) {
    Tournament best_solution = HCFI(instance, 1000, 50, 1, 1);
    int best_n_restarts = 50;
    int best_fitness = best_solution.calculateFitness(instance);

    cout << "-------------------------------------------------"<< endl;
    cout << "Number of restarts " << best_n_restarts << endl;
    cout << "Total Distance:" << best_solution.calculateTotalDistance(instance.getDistances()) << endl;
    cout << "Fitness:" << best_solution.calculateFitness(instance) << endl;
    cout << "Number of violated constraints:" << best_solution.calculateConstraintsViolated(instance) << endl;
    cout << "-------------------------------------------------"<< endl;

    for (int i = 0; i < 3; i++) {
        Tournament solution = HCFI(instance, 1000, 50 * (i + 2), 1, (i + 1)*10);
        int fitness = solution.calculateFitness(instance);
        
        // Check if there is a better solution
        if (fitness < best_fitness) {
            best_solution = solution;
            best_fitness = fitness;
            best_n_restarts = 50 * (i + 2);
        }

        cout << "-------------------------------------------------"<< endl;
        cout << "Number of restarts " << 50 * (i + 2) << endl;
        cout << "Fitness:" << fitness << endl;
        cout << "Distance:" << solution.calculateTotalDistance(instance.getDistances()) << endl;
        cout << "Number of violated constraints:" << solution.calculateConstraintsViolated(instance) << endl;
        cout << "-------------------------------------------------"<< endl;
    }
    cout << "-------------------------------------------------"<< endl;
    cout << "Best Solution: " << endl;
    cout << "Number of restarts " << best_n_restarts << endl;
    cout << "Total Distance:" << best_solution.calculateTotalDistance(instance.getDistances()) << endl;
    cout << "Fitness:" << best_solution.calculateFitness(instance) << endl;
    cout << "Number of violated constraints:" << best_solution.calculateConstraintsViolated(instance) << endl;
    cout << "-------------------------------------------------"<< endl;
}

void testHCFI(Instance instance, int n_iter, int n_restarts, int n_exec) {
    auto start = chrono::high_resolution_clock::now();
    Tournament best_solution = HCFI(instance, n_iter, n_restarts, 1, time(0));
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    int best_fitness = best_solution.calculateFitness(instance);
    int best_time = duration.count();

    int avg_fitness = best_fitness;
    int avg_time = duration.count();

    for (int i = 0; i < n_exec - 1; i++) {
        auto start = chrono::high_resolution_clock::now();
        Tournament solution = HCFI(instance, n_iter, n_restarts, 1, time(0) ^ (i + 1));
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        int fitness = solution.calculateFitness(instance);
        
        // Check if there is a better solution
        if (fitness < best_fitness) {
            best_solution = solution;
            best_fitness = fitness;
            best_time = duration.count();
        }

        avg_fitness += fitness;
        avg_time += duration.count();
    }

    avg_fitness /= n_exec;
    avg_time /= n_exec;
    
    cout << "-------------------------------------------------"<< endl;
    cout << "Instance: " << instance.getN() << endl;
    cout << "Best Solution: " << best_fitness << endl;
    cout << "Best Time: " << best_time << " s" << endl;
    cout << "Average Solution: " << avg_fitness << endl;
    cout << "Average Time: " << avg_time << " s" << endl;
    cout << "-------------------------------------------------"<< endl;
}