//
// Created by Szef on 27.12.2023.
//

#include <ctime>
#include <algorithm>
#include <random>
#include <iostream>
#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::run(int stopTime, int populationSize, double mutationRate, double crossoverRate, TSPGraph *&graph) {
    srand ( time(NULL) );

    //czas start
    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    //wygeneruj losowa populacje
    std::vector<Individual> population (populationSize);
    population = generateRandomPopulation(populationSize, graph);


    //selekcja
    std::vector<Individual> newPopulation;


    Individual parent1 = tournamentSelection(population);
    Individual parent2 = tournamentSelection(population);
    double time = (std::clock() - (double)start_time) / CLOCKS_PER_SEC;
    std::cout << "Czas:" << time << std::endl;

    //krzyzowanie
    Individual child1;
    Individual child2;
    parent1.path = std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9};
    parent2.path = std::vector<int> {9, 3, 7, 8, 2, 6, 5, 1, 4};
    OXCrossover(parent1, parent2, child1, child2, 3, 7);




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

void GeneticAlgorithm::PMXCrossover(const Individual &parent1, const Individual &parent2, Individual &child1,
                                    Individual &child2) {

    int firstRandomIDx = rand() % (parent1.path.size() / 2);
    int secondRandomIDx = rand();

}

void GeneticAlgorithm::OXCrossover(const Individual &parent1, const Individual &parent2, Individual &child1,
                                   Individual &child2, int startPos, int endPos) {
    child1.path.resize(parent1.path.size());
    child2.path.resize(parent2.path.size());

    // kopiowanie fragmentow rodzicow do potomkow
    for(int i = startPos; i < endPos; i++){
        child1.path[i] = parent1.path[i];
        child2.path[i] = parent2.path[i];
    }

    // kopiowanie reszty genow do potomkow

    int iDP1 = endPos;
    int iDP2 = endPos;
    for(int i = endPos ; i != startPos; ){
        //znajdz nastepny element do skopiowania z drugiego rodzica
        while(std::find(child1.path.begin(), child1.path.end(), parent2.path[iDP2]) != child1.path.end()){
            iDP2++;
            if(iDP2 == parent2.path.size()) iDP2 = 0;
        }
        child1.path[i] = parent2.path[iDP2];

        while(std::find(child2.path.begin(), child2.path.end(), parent1.path[iDP1]) != child2.path.end()){
            iDP1++;
            if(iDP1 == parent1.path.size()) iDP1 = 0;
        }
        child2.path[i] = parent1.path[iDP1];


        // inkrementacja na nastepny indeks dziecka
        if(i == parent1.path.size() - 1){
            i = 0;
        }else{
            i++;
        }
    }
}

bool GeneticAlgorithm::valueInbetweenRange(const std::vector<int> tab, int startPos, int endPos, int valueToFind) {
    for(int i = startPos; i < endPos; i++){
        if (tab[i] == valueToFind) return true;
    }
    return false;
}

//GeneticAlgorithm::GeneticAlgorithm(int stopTime, int populationSize, double mutationRate, double crossoverRate) {
//    this->stopTime = stopTime;
//    this->populationSize = populationSize;
//    mutationRate, double crossoverRate
//}

GeneticAlgorithm::GeneticAlgorithm() = default;
