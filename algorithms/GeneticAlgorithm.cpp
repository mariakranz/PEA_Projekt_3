//
// Created by Szef on 27.12.2023.
//

#include <ctime>
#include <algorithm>
#include <random>
#include <iostream>
#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::run(int stopTime, int populationSize, double mutationRate, double crossoverRate, TSPGraph *&graph) {

    //czas start
    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    //wygeneruj losowa populacje
    std::vector<Individual> population (populationSize);
    population = generateRandomPopulation(populationSize, graph);


    //selekcja
    std::vector<Individual> newPopulation;

    srand ( time(NULL) );
    Individual parent1 = tournamentSelection(population);
    Individual parent2 = tournamentSelection(population);
    double time = (std::clock() - (double)start_time) / CLOCKS_PER_SEC;
    std::cout << "Czas:" << time << std::endl;




    //while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {}

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

Individual GeneticAlgorithm::tournamentSelection(std::vector<Individual> population) {
//    srand ( time(NULL) );
    const int tournamentSize = 3; // Rozmiar turnieju
    const double selectionProbability = 0.7; // Prawdopodobieństwo wyboru najlepszego osobnika

    std::vector<int> tournamentParticipants(tournamentSize);
    std::vector<double> probabilityForEveryIndividual(population.size());

    // Kopiowanie wektora do innego wektora, ponieważ sortowanie zmodyfikuje jego kolejność
    //std::vector<Individual> sortedPopulation = population;
    // Sortowanie nowego wektora
    //std::sort(sortedPopulation.begin(), sortedPopulation.end(), compareIndividuals);

    std::sort(population.begin(), population.end(), compareIndividuals);
    probabilityForEveryIndividual = probabilityOfSelection(population, selectionProbability);



    // Wybieranie uczestników turnieju z określonymi prawdopodobieństwami
    for (int i = 0; i < tournamentSize; ++i) {
        int selectedIdx = -1;

        while(selectedIdx == -1){
            //srand ( time(NULL) );
            int randomIdx = rand()%population.size();

            //srand ( time(NULL) );
            //float randValue = ((float) (rand()%10)) /10;
            double randValue = (double)rand() / RAND_MAX;

            if (randValue < probabilityForEveryIndividual[randomIdx]) selectedIdx = randomIdx;

        }
        tournamentParticipants[i] = selectedIdx;
    }

//    for (int i = 0; i < tournamentSize; ++i) {
//        // Wybór indeksu z populacji zgodnie z prawdopodobieństwem
//        double randValue = (double)rand() / RAND_MAX;
//        int selectedIdx = -1;
//
//        for (int j = 0; j < population.size(); ++j) {
//            if (randValue < probabilityForEveryIndividual[j]) {
//                selectedIdx = j;
//                break;
//            }
//        }
//
//        tournamentParticipants[i] = selectedIdx;
//    }


    // Wybór zwycięzcy turnieju spośród uczestników
    sort(tournamentParticipants.begin(), tournamentParticipants.end(), [&](int a, int b) {
        return population[a].cost < population[b].cost;
    });

    return population[tournamentParticipants[0]];
}


// Funkcja do porównywania dwóch osobników na podstawie ich przystosowania
bool GeneticAlgorithm::compareIndividuals(const Individual& a, const Individual& b) {
    return a.cost < b.cost;
}

//population musi byc posortowana
std::vector<double> GeneticAlgorithm::probabilityOfSelection(const std::vector<Individual> &population, const double& bestCandidateSelectionProbabilty) {
    double cumulativeProbability = 1.0;
    std::vector<double> probability(population.size());

    for(int i = 0; i < population.size(); i++){
        if (i == 0){
            cumulativeProbability *= bestCandidateSelectionProbabilty;

        }else{
          if( population[i].cost != population[i-1].cost){
              cumulativeProbability *= (1.0 - bestCandidateSelectionProbabilty);
              //cumulativeProbability -= cumulativeProbability/population.size();
          }
        }

        probability[i] = cumulativeProbability;
        //cumulativeProbability *= (i == 0) ? bestCandidateSelectionProbabilty : (1.0 - bestCandidateSelectionProbabilty);
    }
    return probability;
}

GeneticAlgorithm::GeneticAlgorithm() = default;
