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
};



class GeneticAlgorithm {
//    int stopTime;
//    int populationSize;
//    double mutationRate;
//    double crossoverRate;
    TSPGraph* graph;

    std::vector<Individual> generateRandomPopulation(int populationSize);
    // Funkcja selekcji turniejowej
    Individual tournamentSelection(std::vector<Individual>& population, const std::vector<double>& probabilityOfSelection);
    static bool compareIndividuals(const Individual& a, const Individual& b);
    std::vector<double> probabilityOfSelection(const std::vector<Individual>& population, const double& bestCandidateSelectionProbabilty);
    void PMXCrossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2);
    void OXCrossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2, int startPos, int endPos);
    bool valueInbetweenRange(const std::vector<int> tab, int startPos, int endPos, int valueToFind);
    void inversionMutation(Individual& individual);

public:

    explicit GeneticAlgorithm(TSPGraph*& graph);

    Individual run(int stopTime, int populationSize, double mutationRate, double crossoverRate);
    //Individual run(TSPGraph *&graph);

};


#endif //PEA_PROJEKT_3_GENETICALGORITHM_H
