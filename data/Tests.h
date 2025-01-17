//
// Created by Szef on 12.01.2024.
//

#ifndef PEA_PROJEKT_3_TESTS_H
#define PEA_PROJEKT_3_TESTS_H


#include "../algorithms/GeneticAlgorithm.h"

class Tests {
public:
    //rozmiar tabu zalezny od rozmiaru instancji (100*graph.size)
    static void
    generateFile_BestSolutionInTime_ftv47(int numberOfTestInstances, int time, int populationSize, double mutationRate,
                                          double crossoverRate, const char *filename, Mutation mutationType);
    static void
    generateFile_BestSolutionInTime_ftv170(int numberOfTestInstances, int time, int populationSize, double mutationRate,
                                           double crossoverRate, const char *filename, Mutation mutationType);
    static void
    generateFile_BestSolutionInTime_rbg403(int numberOfTestInstances, int time, int populationSize, double mutationRate,
                                           double crossoverRate, const char *filename, Mutation mutationType);
};


#endif //PEA_PROJEKT_3_TESTS_H
