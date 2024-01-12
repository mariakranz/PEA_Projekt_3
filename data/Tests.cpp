//
// Created by Szef on 12.01.2024.
//

#include <iostream>
#include "Tests.h"
#include "../data/DataReader.h"
#include "../algorithms/GeneticAlgorithm.h"

void Tests::generateFile_BestSolutionInTime_ftv47(int numberOfInstances, int time, int populationSize, double mutationRate,
                                             double crossoverRate) {
    std::cout << "------Test ftv47.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;
    //ftv47.xml
    graph = DataReader::createGraphFromFile("..\\data_files\\ftv47.xml");
    auto geneticAlgorithm = new GeneticAlgorithm(graph);

    if(graph) {
        //OXCross i inversionMutation
        for (int i = 0; i < numberOfInstances; i++) {
            std::cout << "OXCrossing i inversion mutation" << i << std::endl;

            std::string filename = "ftv47_pop:" + std::to_string(populationSize) +
                                   "_mutRate:"+ std::to_string(mutationRate) +
                                   "_crossRate:" + std::to_string(crossoverRate) +
                                   "_" + std::to_string(i) + ".txt";
            auto res = geneticAlgorithm->runTest(time, populationSize, mutationRate, crossoverRate, filename.c_str());

            std::string pathFilename = "ftv47_path_pop:" + std::to_string(populationSize) +
                                       "_mutRate:"+ std::to_string(mutationRate) +
                                       "_crossRate:" + std::to_string(crossoverRate) +
                                       "_" + std::to_string(i) + ".txt";
            DataReader::savePathToFile(res.path, pathFilename.c_str());

            std::cout << std::endl;
        }
        delete graph;
    }
}

void Tests::generateFile_BestSolutionInTime_ftv170(int numberOfInstances, int time, int populationSize, double mutationRate,
                                              double crossoverRate) {
    std::cout << "------Test ftv170.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;
    //ftv170.xml
    graph = DataReader::createGraphFromFile("..\\data_files\\ftv170.xml");
    auto geneticAlgorithm = new GeneticAlgorithm(graph);

    if(graph) {
        //OXCross i inversionMutation
        for (int i = 0; i < numberOfInstances; i++) {
            std::cout << "OXCrossing i inversion mutation" << i << std::endl;

            std::string filename = "ftv170_pop:" + std::to_string(populationSize) +
                                   "_mutRate:"+ std::to_string(mutationRate) +
                                   "_crossRate:" + std::to_string(crossoverRate) +
                                   "_" + std::to_string(i) + ".txt";auto res = geneticAlgorithm->runTest(time, populationSize, mutationRate, crossoverRate, filename.c_str());

//            std::string pathFilename = "ftv170_path_OXCrossover_invMutation_5000_" + std::to_string(i) + ".txt";
//            DataReader::savePathToFile(res.path, pathFilename.c_str());

            std::cout << std::endl;
        }
        delete graph;
    }
}

void Tests::generateFile_BestSolutionInTime_rbg403(int numberOfInstances, int time, int populationSize, double mutationRate,
                                              double crossoverRate) {
    std::cout << "------Test rbg403.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;
    //rbg403.xml
    graph = DataReader::createGraphFromFile("..\\data_files\\rbg403.xml");
    auto geneticAlgorithm = new GeneticAlgorithm(graph);

    if(graph) {
        //OXCross i inversionMutation
        for (int i = 0; i < numberOfInstances; i++) {
            std::cout << "OXCrossing i inversion mutation" << i << std::endl;

            std::string filename = "rbg403_pop:" + std::to_string(populationSize) +
                    "_mutRate:"+ std::to_string(mutationRate) +
                    "_crossRate:" + std::to_string(crossoverRate) +
                    "_" + std::to_string(i) + ".txt";
            auto res = geneticAlgorithm->runTest(time, populationSize, mutationRate, crossoverRate, filename.c_str());

//            std::string pathFilename = "rbg403_path_OXCrossover_invMutation_5000_" + std::to_string(i) + ".txt";
//            DataReader::savePathToFile(res.path, pathFilename.c_str());

            std::cout << std::endl;
        }
        delete graph;
    }
}
