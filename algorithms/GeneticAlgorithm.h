//
// Created by Szef on 27.12.2023.
//

#ifndef PEA_PROJEKT_3_GENETICALGORITHM_H
#define PEA_PROJEKT_3_GENETICALGORITHM_H

#include <vector>
#include <list>
#include "../graph/TSPGraph.h"

//struktura reprezentujaca osobnika
struct Individual {
    std::vector<int> path;
    int cost;
    //int cost = INT_MAX;
};

enum Mutation{
    swapMut,
    inverseMut
};


class GeneticAlgorithm {
    TSPGraph* graph;
    std::list<std::pair<double, int>> bestSolutionFoundInTime;

private:

    std::vector<Individual> generateRandomPopulation(int populationSize);

    Individual tournamentSelection(std::vector<Individual>& population);
    static bool compareIndividuals(const Individual& a, const Individual& b);

    void OXCrossover(const Individual &parent1, const Individual &parent2, Individual &child1, Individual &child2,
                     int startPos,
                     int endPos);

    void inversionMutation(Individual& individual);
    void swapMutation(Individual& individual);

public:

    explicit GeneticAlgorithm(TSPGraph*& graph);

    Individual
    run(int stopTime, int populationSize, double mutationRate, double crossoverRate, Mutation mutationType);

    const std::list<std::pair< double, int>> &getBestSolutionFoundInTime() const;

    static std::string getMutationTypeToString(Mutation mutationType);

};


#endif //PEA_PROJEKT_3_GENETICALGORITHM_H
