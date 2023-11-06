# include "headers.h"
# include <iostream>

void testHC(int restarts, int n_iter, Instance instance) {
    Tournament best_solution = initialSolution(instance);
    int best_fitness = best_solution.calculateFitness(instance);

    for (int i = 0; i < restarts; i++) {
        Tournament init = initialSolution(instance);
        Tournament solution = hillClimbingFI(init, instance, n_iter);
        int fitness = solution.calculateFitness(instance);
        if (fitness < best_fitness) {
            best_fitness = fitness;
            best_solution = solution;
        }
    }

    cout << "Best solution:" << endl;
    best_solution.print();
    cout << "Fitness:" << best_fitness << endl;
    cout << "Distance:" << best_solution.calculateTotalDistance(instance.getDistances()) << endl;
    cout << "Constraints violated:" << best_solution.calculateConstraintsViolated(instance) << endl;
}