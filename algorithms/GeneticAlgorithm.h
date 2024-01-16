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



class GeneticAlgorithm {
    TSPGraph* graph;
    std::list<std::pair<double, int>> bestSolutionFoundInTime;

private:

    std::vector<Individual> generateRandomPopulation(int populationSize);
    // Funkcja selekcji turniejowej
    Individual tournamentSelection(std::vector<Individual>& population,  std::vector<double>& probabilityOfSelection);
    Individual tournamentSelectionV2(std::vector<Individual>& population);
    static bool compareIndividuals(const Individual& a, const Individual& b);
    std::vector<double> probabilityOfSelection(const std::vector<Individual>& population, const double& bestCandidateSelectionProbabilty);

    void PMXCrossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2);
    void OXCrossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2, int startPos, int endPos);

    void inversionMutation(Individual& individual);

public:


    explicit GeneticAlgorithm(TSPGraph*& graph);


    Individual runV2(int stopTime, int populationSize, double mutationRate, double crossoverRate);
    void testOX();

    const std::list<std::pair< double, int>> &getBestSolutionFoundInTime() const;
    Individual runTest(int stopTime, int populationSize, double mutationRate, double crossoverRate, const char* filePath);

    //Individual runOlderVersion(TSPGraph *&graph);

};


#endif //PEA_PROJEKT_3_GENETICALGORITHM_H
