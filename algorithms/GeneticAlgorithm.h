//
// Created by Szef on 27.12.2023.
//

#ifndef PEA_PROJEKT_3_GENETICALGORITHM_H
#define PEA_PROJEKT_3_GENETICALGORITHM_H

#include <vector>
#include "../graph/TSPGraph.h"

//struktura reprezentujaca osobnika
struct Individual {
    std::vector<int> path;
    int cost;
};


class GeneticAlgorithm {

    static std::vector<Individual> generateRandomPopulation(int populationSize, TSPGraph *&graph);

public:
    GeneticAlgorithm();

    static Individual run(int stopTime, int populationSize, double mutationRate, double crossoverRate, TSPGraph *&graph);
};


#endif //PEA_PROJEKT_3_GENETICALGORITHM_H
