//
// Created by Szef on 12.01.2024.
//

#ifndef PEA_PROJEKT2_TEST_H
#define PEA_PROJEKT2_TEST_H


class Tests {
public:
    //rozmiar tabu zalezny od rozmiaru instancji (100*graph.size)
    static void
    generateFile_BestSolutionInTime_ftv47(int numberOfInstances, int time, int populationSize, double mutationRate,
                                          double crossoverRate);
    static void
    generateFile_BestSolutionInTime_ftv170(int numberOfInstances, int time, int populationSize, double mutationRate,
                                           double crossoverRate);
    static void
    generateFile_BestSolutionInTime_rbg403(int numberOfInstances, int time, int populationSize, double mutationRate,
                                           double crossoverRate);
};


#endif //PEA_PROJEKT2_TEST_H
