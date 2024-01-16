//
// Created by Szef on 27.12.2023.
//

#include <ctime>
#include <algorithm>
#include <random>
#include <iostream>
#include <list>
#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(TSPGraph *&graph) {
    this->graph = graph;
}

std::vector<Individual> GeneticAlgorithm::generateRandomPopulation(int populationSize) {
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


// funkcja do porównywania dwóch osobników na podstawie ich przystosowania
bool GeneticAlgorithm::compareIndividuals(const Individual& a, const Individual& b) {
    return a.cost < b.cost;
}

Individual GeneticAlgorithm::tournamentSelection(std::vector<Individual> &population) {

    Individual individual1 = population[std::rand() % population.size()]; // losuje pierwszego osobnika
    Individual individual2 = population[std::rand() % population.size()]; // losuje drugiego osobnika

    return compareIndividuals(individual1, individual2) ? individual1 : individual2; // zwracam tego osobnika, ktory jest lepszy
}

// krzyzowanie OX, wybiera geny na przedziale [startPos, endPos] i modyfikuje dzieci zmodyfikowanymi genomami

void GeneticAlgorithm::OXCrossover(const Individual &parent1, const Individual &parent2, Individual &child1,
                                   Individual &child2, int startPos,
                                   int endPos) {
    child1.path.resize(parent1.path.size());
    child2.path.resize(parent2.path.size());

    //ustawianie wszystkich elementow na '-1', poniewaz w vectorze bedzie znajdowalo sie 0 (wierzcholki sa numerowane od 0)
    for(int i = 0; i < child1.path.size(); i++){
        child1.path[i] = -1;
        child2.path[i] = -1;
    }

    // kopiowanie fragmentow rodzicow do potomkow
    for(int i = startPos; i <= endPos; i++){
        child1.path[i] = parent1.path[i];
        child2.path[i] = parent2.path[i];
    }

    // kopiowanie reszty genow do potomkow

    int iDP1 = endPos + 1;
    int iDP2 = endPos + 1;
    if(endPos+1 > child1.path.size() - 1){
        iDP1 = 0;
        iDP2 = 0;
    }
    int newPos = iDP1;
    for(int i = newPos ; i != startPos; ){
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

    // obicz koszt sciezek
    child1.cost = graph->calculateTour(child1.path);
    child2.cost = graph->calculateTour(child2.path);
}

void GeneticAlgorithm::inversionMutation(Individual &individual) {
    // generowanie dwoch losowych punktow
    int iD1 = rand() % individual.path.size();
    int iD2;

    do{
        iD2 = rand() % individual.path.size();
    }while(iD1 == iD2);

    if(iD1 < iD2){
        reverse(individual.path.begin() + iD1, individual.path.begin() + iD2 + 1);
        individual.cost = graph->calculateTour(individual.path);
        return;
    }

    reverse(individual.path.begin() + iD2, individual.path.begin() + iD1 + 1);

    //oblicz koszt sciezki
    individual.cost = graph->calculateTour(individual.path);
}

void GeneticAlgorithm::swapMutation(Individual &individual) {
    // generowanie dwoch losowych punktow
    int iD1 = rand() % individual.path.size();
    int iD2;
    do{
        iD2 = rand() % individual.path.size();
    }while (iD1 == iD2);
    std::swap(individual.path[iD1], individual.path[iD2]);
    individual.cost = graph->calculateTour(individual.path);
}

Individual GeneticAlgorithm::run(int stopTime, int populationSize, double mutationRate, double crossoverRate,
                                 Mutation mutationType) {
    bestSolutionFoundInTime.clear();
    srand ( time(nullptr) );
    int bestSolutionFound = INT_MAX;


    //czas start
    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    //wygeneruj losowa populacje
    std::vector<Individual> population (populationSize);
    population = generateRandomPopulation(populationSize);

    while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {
        std::vector<Individual> newPopulation(populationSize);
        int iteratorInPopulation = 0;

        // sortowanie wedlug przystosowania (rosnaco)
        std::sort(population.begin(), population.end(), compareIndividuals);

        if (population[0].cost < bestSolutionFound) {                           //jesli najnowsze rozwiązanie jest inne niz stare, to zapisujemy czas i jego wartosc do listy
            bestSolutionFound = population[0].cost;
            double currentTime = (std::clock() - (double) start_time) / CLOCKS_PER_SEC;

            bestSolutionFoundInTime.emplace_back(currentTime, bestSolutionFound);
        }

        for(; iteratorInPopulation < 10; iteratorInPopulation++){                    //elitaryzm - zachowujemy 10 najlepszych wynikow z poprzedniej populacji
            newPopulation[iteratorInPopulation] = population[iteratorInPopulation];
        }
        iteratorInPopulation--;

        while ( iteratorInPopulation != populationSize - 1) {

            //selekcja
            Individual parent1 = tournamentSelection(population);
            Individual parent2 = tournamentSelection(population);

            Individual child1 = parent1;
            Individual child2 = parent2;

            // krzyżowanie
            if (rand() < crossoverRate * RAND_MAX) {
                //krzyzowanie
                int iD1 = rand() % parent1.path.size();
                int iD2;
                do{
                    iD2= rand() % parent1.path.size();
                }while (iD2 == iD1);

                if(iD1 < iD2) OXCrossover(parent1, parent2, child1, child2, iD1, iD2);
                else OXCrossover(parent1, parent2, child1, child2, iD2, iD1);
            }

            //mutacja
            if (rand() < mutationRate * RAND_MAX){
                switch (mutationType) {
                    case swapMut:
                        swapMutation(child1);
                        break;
                    case inverseMut:
                        inversionMutation(child1);
                        break;
                }
            }

            if (rand() < mutationRate * RAND_MAX){
                switch (mutationType) {
                    case swapMut:
                        swapMutation(child2);
                        break;
                    case inverseMut:
                        inversionMutation(child2);
                        break;
                }
            }

            newPopulation[++iteratorInPopulation] = child1;
            newPopulation[++iteratorInPopulation] = child2;
        }

        population = newPopulation;
    }

    std::sort(population.begin(), population.end(), compareIndividuals);

    if (population[0].cost < bestSolutionFound) {                           //jesli najnowsze rozwiązanie jest inne niz stare, to zapisujemy czas i jego wartosc do listy
        bestSolutionFound = population[0].cost;
        double currentTime = (std::clock() - (double) start_time) / CLOCKS_PER_SEC;

        bestSolutionFoundInTime.emplace_back(currentTime, bestSolutionFound);
    }

    return population[0];
}

const std::list<std::pair<double, int>> &GeneticAlgorithm::getBestSolutionFoundInTime() const {
    return bestSolutionFoundInTime;
}

std::string GeneticAlgorithm::getMutationTypeToString(Mutation mutationType) {
    switch (mutationType) {
        case swapMut:
           return "swapMut";
        case inverseMut:
            return "inverseMut";
    }
    return "";
}
