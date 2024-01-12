//
// Created by Szef on 27.12.2023.
//

#include <ctime>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::runOlderVersion(int stopTime, int populationSize, double mutationRate, double crossoverRate) {
    srand ( time(NULL) );
//    std::vector<double> probabilityForEveryIndividual(populationSize);
    const double selectionProbability = 0.7; // Prawdopodobieństwo wyboru najlepszego osobnika
    Individual bestFound;
    bestFound.cost = INT_MAX;


    //czas start
    const std::clock_t start_time = std::clock();                                                                //rozpocznij odliczanie zegara

    //wygeneruj losowa populacje
    std::vector<Individual> population (populationSize);
    population = generateRandomPopulation(populationSize);

    int c = 0;
    //while( c < 100000){
    while ((std::clock() - start_time) / CLOCKS_PER_SEC < stopTime) {
        std::vector<Individual> newPopulation;

        std::vector<Individual> populationCopy;
        std::vector<double> probabilityForEveryIndividual(populationSize);

        // sortowanie wedlug przystosowania (rosnaco)
        std::sort(population.begin(), population.end(), compareIndividuals);
        std::cout << population[0].cost << std::endl;

        //selekcja
        probabilityForEveryIndividual = probabilityOfSelection(population, selectionProbability);

        for (int i = 0; i < populationSize; i += 2) {
            if (rand() < crossoverRate * RAND_MAX) {
                populationCopy = population;
                Individual parent1 = tournamentSelection(populationCopy, probabilityForEveryIndividual);
                Individual parent2 = tournamentSelection(populationCopy, probabilityForEveryIndividual);
                //Individual parent1 = tournamentSelectionV2(population);
                //Individual parent2 = tournamentSelectionV2(population);

                //krzyzowanie
                Individual child1;
                Individual child2;
                //parent1.path = std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8};
                //parent2.path = std::vector<int> {0, 3, 7, 8, 2, 6, 5, 1, 4};

                int iD1 = rand() % parent1.path.size();
                int iD2;
                do{
                    iD2= rand() % parent1.path.size();
                }while (iD2 == iD1);

                if(iD1 < iD2) OXCrossover(parent1, parent2, child1, child2, iD1, iD2);
                else OXCrossover(parent1, parent2, child1, child2, iD2, iD1);

                //OXCrossover(parent1, parent2, child1, child2, 3, 6);

                newPopulation.push_back(child1);
                newPopulation.push_back(child2);

            }else{
                newPopulation.push_back(population[i]);
                newPopulation.push_back(population[i+1]);
            }

        }

        for(Individual individual: newPopulation){
            if (rand() < mutationRate * RAND_MAX){
                //mutacja
                inversionMutation(individual);
            }
        }

        population = newPopulation;
        c++;
    }


    std::sort(population.begin(), population.end(), compareIndividuals);

    std::cout << "c: " << c << std::endl;
    return population[0];
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

Individual GeneticAlgorithm::tournamentSelection(std::vector<Individual>& population, std::vector<double>& probabilityOfSelection ) {
//    srand ( time(NULL) );
    const int tournamentSize = 3; // Rozmiar turnieju

    std::vector<int> tournamentParticipants(tournamentSize, -1);
    // Kopiowanie wektora do innego wektora, ponieważ sortowanie zmodyfikuje jego kolejność
    //std::vector<Individual> sortedPopulation = population;
    // Sortowanie nowego wektora
    //std::sort(sortedPopulation.begin(), sortedPopulation.end(), compareIndividuals);




    // Wybieranie uczestników turnieju z określonymi prawdopodobieństwami
    for (int i = 0; i < tournamentSize; ++i) {
        int selectedIdx = -1;

        while(selectedIdx == -1 || std::find(tournamentParticipants.begin(), tournamentParticipants.end(), selectedIdx) != tournamentParticipants.end()){
            //srand ( time(NULL) );
            int randomIdx = rand()% population.size();

            //srand ( time(NULL) );
            //float randValue = ((float) (rand()%10)) /10;
            double randValue = (double)rand() / RAND_MAX;

            if (randValue < probabilityOfSelection[randomIdx]) selectedIdx = randomIdx;

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

    // Usun z populacji zwycięzce (żeby nie byl wybrany ponownie w drugiej selekcji turniejowej)
    probabilityOfSelection.erase(probabilityOfSelection.begin() + tournamentParticipants[0]);
    Individual winner = population[tournamentParticipants[0]];
    population.erase(population.begin() + tournamentParticipants[0]);

    return winner;
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

// krzyzowanie OX, wybiera geny na przedziale [startPos, endPos] i modyfikuje dzieci zmodyfikowanymi genomami

void GeneticAlgorithm::OXCrossover(const Individual &parent1, const Individual &parent2, Individual &child1,
                                   Individual &child2, int startPos, int endPos) {
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

bool GeneticAlgorithm::valueInbetweenRange(const std::vector<int> tab, int startPos, int endPos, int valueToFind) {
    for(int i = startPos; i < endPos; i++){
        if (tab[i] == valueToFind) return true;
    }
    return false;
}

void GeneticAlgorithm::inversionMutation(Individual &individual) {
    // generowanie dwoch losowych punktow
    int iD1 = rand() % individual.path.size();
    int iD2 = rand() % individual.path.size();

    while(iD1 == iD2){
        iD2 = rand() % individual.path.size();
    }

    if(iD1 < iD2){
        reverse(individual.path.begin() + iD1, individual.path.begin() + iD2 + 1);
        individual.cost = graph->calculateTour(individual.path);
        return;
    }

    reverse(individual.path.begin() + iD2, individual.path.begin() + iD1 + 1);

    //oblicz koszt sciezki
    individual.cost = graph->calculateTour(individual.path);
}

GeneticAlgorithm::GeneticAlgorithm(TSPGraph *&graph) {
    this->graph = graph;

}

// ------------------------------------------gotowiec
Individual GeneticAlgorithm::tournamentSelectionV2(std::vector<Individual> &population) {

    Individual individual1 = population[std::rand() % population.size()]; // losuje pierwszego osobnika
    Individual individual2 = population[std::rand() % population.size()]; // losuje drugiego osobnika

    return compareIndividuals(individual1, individual2) ? individual1 : individual2; // zwracam tego osobnika, ktory jest lepszy
}

void GeneticAlgorithm::testOX() {
    Individual parent1, parent2, child1, child2;
//    parent1.path = std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8};
//    parent2.path = std::vector<int> {0, 3, 7, 8, 2, 6, 5, 1, 4};
    parent1.path = std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9};
    parent2.path = std::vector<int> {9, 3, 7, 8, 2, 6, 5, 1, 4};


    OXCrossover(parent1, parent2, child1, child2, 3, 6);

    std::cout << "Sciezka: ";
    for (int i  = 0; i < child1.path.size(); i++){
        std::cout << child1.path[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Sciezka: ";
    for (int i  = 0; i < child2.path.size(); i++){
        std::cout << child2.path[i] << " ";
    }
    std::cout << std::endl;
}

Individual GeneticAlgorithm::runV2(int stopTime, int populationSize, double mutationRate, double crossoverRate) {
    srand ( time(NULL) );

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
        std::cout << population[0].cost << std::endl;
        for(; iteratorInPopulation < 10; iteratorInPopulation++){                    //elitaryzm - zachowujemy 10 najlepszych wynikow z poprzedniej populacji
            newPopulation[iteratorInPopulation] = population[iteratorInPopulation];
        }
        iteratorInPopulation--;

        while ( iteratorInPopulation != populationSize - 1) {

            //selekcja
            Individual parent1 = tournamentSelectionV2(population);
            Individual parent2 = tournamentSelectionV2(population);

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
                //mutacja
                inversionMutation(child1);
            }

            if (rand() < mutationRate * RAND_MAX){
                //mutacja
                inversionMutation(child2);
            }

            newPopulation[++iteratorInPopulation] = child1;
            newPopulation[++iteratorInPopulation] = child2;
        }

        population = newPopulation;
    }

    std::sort(population.begin(), population.end(), compareIndividuals);
    return population[0];
}

Individual GeneticAlgorithm::runTest(int stopTime, int populationSize, double mutationRate, double crossoverRate,
                                     const char *filePath) {

    std::ofstream file(filePath);
    if (!file.is_open()) return {};
    file << "time[s];value" << std::endl;

    double bestSolutionFoundTime;
    srand ( time(NULL) );

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
        bestSolutionFoundTime = (std::clock() - (double)start_time) / CLOCKS_PER_SEC;
        file << bestSolutionFoundTime << ";" << population[0].cost  << std::endl;
        //std::cout << "Rozw: " << bestCandidateCost << " Czas:" << bestSolutionFoundTime << std::endl;

        for(; iteratorInPopulation < 10; iteratorInPopulation++){                    //elitaryzm - zachowujemy 10 najlepszych wynikow z poprzedniej populacji
            newPopulation[iteratorInPopulation] = population[iteratorInPopulation];
        }
        iteratorInPopulation--;

        while ( iteratorInPopulation != populationSize - 1) {

            //selekcja
            Individual parent1 = tournamentSelectionV2(population);
            Individual parent2 = tournamentSelectionV2(population);

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
                //mutacja
                inversionMutation(child1);
            }

            if (rand() < mutationRate * RAND_MAX){
                //mutacja
                inversionMutation(child2);
            }

            newPopulation[++iteratorInPopulation] = child1;
            newPopulation[++iteratorInPopulation] = child2;
        }

        population = newPopulation;
    }

    file.close();
    std::sort(population.begin(), population.end(), compareIndividuals);
    return population[0];
}
