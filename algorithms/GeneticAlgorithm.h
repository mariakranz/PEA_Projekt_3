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
    //int cost = INT_MAX;

    //Individual(std::vector<int>& p, int& c) : path(p), cost(c) {}
};

struct compare{
    inline bool operator() (const Individual& a, const Individual& b)
    {
        return (a.cost < b.cost);
    }
};


class GeneticAlgorithm {

    std::vector<Individual> generateRandomPopulation(int populationSize, TSPGraph *&graph);
    // Funkcja selekcji turniejowej
    Individual tournamentSelection(std::vector<Individual> population);
    static bool compareIndividuals(const Individual& a, const Individual& b);
    std::vector<double> probabilityOfSelection(const std::vector<Individual>& population, const double& bestCandidateSelectionProbabilty);

public:
    GeneticAlgorithm();

    Individual run(int stopTime, int populationSize, double mutationRate, double crossoverRate, TSPGraph *&graph);
};


#endif //PEA_PROJEKT_3_GENETICALGORITHM_H
