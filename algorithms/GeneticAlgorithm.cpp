//
// Created by Szef on 27.12.2023.
//

#include <ctime>
#include <algorithm>
#include <random>
#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::run(int stopTime, int populationSize, double mutationRate, double crossoverRate, TSPGraph *&graph) {

    //czas start
    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    //wygeneruj losowa populacje
    std::vector<Individual> population (populationSize);
    population = generateRandomPopulation(populationSize, graph);


    while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {}

    return Individual();
}

std::vector<Individual> GeneticAlgorithm::generateRandomPopulation(int populationSize, TSPGraph *&graph) {
    int numberOfCities = graph->getVerticesNumber();
    std::vector<Individual> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population[i].path.resize(numberOfCities);
        for (int j = 0; j < numberOfCities; ++j) {
            population[i].path[j] = j;
        }
        std::shuffle(population[i].path.begin() + 1, population[i].path.end(), std::mt19937(std::random_device()()));


        population[i].cost = graph->calculateTour(population[i].path);
    }
    return population;
}
