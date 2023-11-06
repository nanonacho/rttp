# include "headers.h"
# include "iostream"

Tournament hillClimbing(Tournament initial_solution, Instance instance, int iter) {
    Tournament best_solution = initial_solution;

    vector<Tournament> neighborhood = generateNeighborhoodSR(initial_solution);

    for (int i = 0; i < iter; i++) {
        int best_fitness = best_solution.calculateFitness(instance);
        int best_index = -1;

        for (int j = 0; j < int(neighborhood.size()); j++) {
            int fitness_j = neighborhood[j].calculateFitness(instance);
            if (fitness_j < best_fitness) {
                best_fitness = fitness_j;
                best_index = j;
            }
        }

        if (best_index == -1) {
            break;
        }

        best_solution = neighborhood[best_index];
        neighborhood = generateNeighborhoodSR(best_solution);
    }

    return best_solution;
}

Tournament hillClimbingFI(Tournament initial_solution, Instance instance, int iter) {
    Tournament best_solution = initial_solution;

    int count = 0;
    for (int i = 0; i < iter; i++) {
        Tournament neighbor = hyperMove(best_solution, instance);
        if (neighbor.calculateFitness(instance) < best_solution.calculateFitness(instance)) {
            best_solution = neighbor;
            count++;
        }
        else {
            break;
        }
        cout << "Iteration: " << i << endl;
        cout << "Fitness: " << best_solution.calculateFitness(instance) << endl;
        best_solution.print();
    }

    cout << "Number of improvements: " << count << endl;

    return best_solution;
}