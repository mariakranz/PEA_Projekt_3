//
// Created by Szef on 12.01.2024.
//

#include <iostream>
#include <fstream>
#include "Tests.h"
#include "../data/DataReader.h"

void
Tests::generateFile_BestSolutionInTime_ftv47(int numberOfTestInstances, int time, int populationSize,
                                             double mutationRate,
                                             double crossoverRate, const char *filename, Mutation mutationType) {

    std::string popSize = std::to_string(populationSize);
    std::string mutRate = std::to_string(mutationRate);
    std::string crossRate = std::to_string(crossoverRate);
    std::string mutationToString = GeneticAlgorithm::getMutationTypeToString(mutationType);


    std::cout << "------Test ftv47.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;

    TSPGraph *graph;
    //ftv47.xml
    graph = DataReader::createGraphFromFile(filename);
    auto geneticAlgorithm = new GeneticAlgorithm(graph);

    if(graph) {
        //OXCross i inversionMutation
        for (int i = 0; i < numberOfTestInstances; i++) {
            std::cout << "OXCrossing i inversion mutation" << i << std::endl;
            auto res = geneticAlgorithm->run(time, populationSize, mutationRate, crossoverRate, mutationType);
            auto solutions = geneticAlgorithm->getBestSolutionFoundInTime();

            std::string filenameToWrite = "ftv47_pop-";
            filenameToWrite += popSize;
            filenameToWrite += "_mutRate-";
            filenameToWrite += mutRate;
            filenameToWrite += "_crossRate-";
            filenameToWrite += crossRate;
            filenameToWrite += "_mutation-";
            filenameToWrite += mutationToString;
            filenameToWrite += "_";
            filenameToWrite += std::to_string(i);
            filenameToWrite += ".txt";
            std::ofstream file(filenameToWrite);
            if (!file.is_open()) return;
            file << "time[s];value" << std::endl;

            for (const auto& pair : solutions) {
                file << pair.first << ';' << pair.second << '\n';
            }

            file.close();

            std::cout << std::endl;
        }
        delete graph;
    }
}

void
Tests::generateFile_BestSolutionInTime_ftv170(int numberOfTestInstances, int time, int populationSize,
                                              double mutationRate,
                                              double crossoverRate, const char *filename, Mutation mutationType) {

    std::string popSize = std::to_string(populationSize);
    std::string mutRate = std::to_string(mutationRate);
    std::string crossRate = std::to_string(crossoverRate);
    std::string mutationToString = GeneticAlgorithm::getMutationTypeToString(mutationType);

    std::cout << "------Test ftv170.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;
    //ftv170.xml
    graph = DataReader::createGraphFromFile(filename);
    auto geneticAlgorithm = new GeneticAlgorithm(graph);

    if(graph) {
        //OXCross i inversionMutation
        for (int i = 0; i < numberOfTestInstances; i++) {
            std::cout << "OXCrossing i inversion mutation" << i << std::endl;
            auto res = geneticAlgorithm->run(time, populationSize, mutationRate, crossoverRate, mutationType);
            auto solutions = geneticAlgorithm->getBestSolutionFoundInTime();

            std::string filenameToWrite = "ftv170_pop-";
            filenameToWrite += popSize;
            filenameToWrite += "_mutRate-";
            filenameToWrite += mutRate;
            filenameToWrite += "_crossRate-";
            filenameToWrite += crossRate;
            filenameToWrite += "_mutation-";
            filenameToWrite += mutationToString;
            filenameToWrite += "_";
            filenameToWrite += std::to_string(i);
            filenameToWrite += ".txt";
            std::ofstream file(filenameToWrite);
            if (!file.is_open()) return;
            file << "time[s];value" << std::endl;

            for (const auto& pair : solutions) {
                file << pair.first << ';' << pair.second << '\n';
            }

            file.close();
            std::cout << std::endl;
        }
        delete graph;
    }
}

void
Tests::generateFile_BestSolutionInTime_rbg403(int numberOfTestInstances, int time, int populationSize,
                                              double mutationRate,
                                              double crossoverRate, const char *filename, Mutation mutationType) {

    std::string popSize = std::to_string(populationSize);
    std::string mutRate = std::to_string(mutationRate);
    std::string crossRate = std::to_string(crossoverRate);
    std::string mutationToString = GeneticAlgorithm::getMutationTypeToString(mutationType);

    std::cout << "------Test rbg403.xml------" << std::endl;
    std::cout << "Czas wykonania algorytmu: " << time << "s." << std::endl;


    TSPGraph *graph;
    //rbg403.xml
    graph = DataReader::createGraphFromFile(filename);
    auto geneticAlgorithm = new GeneticAlgorithm(graph);

    if(graph) {
        //OXCross i inversionMutation
        for (int i = 0; i < numberOfTestInstances; i++) {
            std::cout << "OXCrossing i inversion mutation" << i << std::endl;
            auto res = geneticAlgorithm->run(time, populationSize, mutationRate, crossoverRate, mutationType);
            auto solutions = geneticAlgorithm->getBestSolutionFoundInTime();

            std::string filenameToWrite = "rbg403_pop-";
            filenameToWrite += popSize;
            filenameToWrite += "_mutRate-";
            filenameToWrite += mutRate;
            filenameToWrite += "_crossRate-";
            filenameToWrite += crossRate;
            filenameToWrite += "_mutation-";
            filenameToWrite += mutationToString;
            filenameToWrite += "_";
            filenameToWrite += std::to_string(i);
            filenameToWrite += ".txt";
            std::ofstream file(filenameToWrite);
            if (!file.is_open()) return;
            file << "time[s];value" << std::endl;

            for (const auto& pair : solutions) {
                file << pair.first << ';' << pair.second << '\n';
            }

            file.close();
            std::cout << std::endl;
        }
        delete graph;
    }
}
