//
// Created by Szef on 12.01.2024.
//

#include <iostream>
#include <fstream>
#include "Tests.h"
#include "../data/DataReader.h"
#include "../algorithms/GeneticAlgorithm.h"

void
Tests::generateFile_BestSolutionInTime_ftv47(int numberOfTestInstances, int time, int populationSize, double mutationRate,
                                             double crossoverRate, const char *filename) {

    std::string popSize = std::to_string(populationSize);
    std::string mutRate = std::to_string(mutationRate);
    std::string crossRate = std::to_string(crossoverRate);

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

            std::string filenameToWrite = "ftv47_pop-";
            filenameToWrite += popSize;
            filenameToWrite += "_mutRate-";
            filenameToWrite += mutRate;
            filenameToWrite += "_crossRate-";
            filenameToWrite += crossRate;
            filenameToWrite += "_";
            filenameToWrite += std::to_string(i);
            filenameToWrite += ".txt";

            std::ofstream file(filenameToWrite);
            if (!file.is_open()) return;
            file << "time[s];value" << std::endl;

//            auto res = geneticAlgorithm->runTest(time, populationSize, mutationRate, crossoverRate, filenameToWrite.c_str());
            auto res = geneticAlgorithm->runV2(time, populationSize, mutationRate, crossoverRate);

            auto solutions = geneticAlgorithm->getBestSolutionFoundInTime();

            for (const auto& pair : solutions) {
                file << pair.first << ';' << pair.second << '\n';
            }

            file.close();
//            std::string pathFilename = "ftv47_path_pop-";
//            pathFilename += popSize;
//            pathFilename += "_mutRate-";
//            pathFilename += mutRate;
//            pathFilename += "_crossRate-";
//            pathFilename += crossRate;
//            pathFilename += "_";
//            pathFilename += std::to_string(i);
//            pathFilename += ".txt";
//            DataReader::savePathToFile(res.path, pathFilename.c_str());

            std::cout << std::endl;
        }
        delete graph;
    }
}

void
Tests::generateFile_BestSolutionInTime_ftv170(int numberOfTestInstances, int time, int populationSize, double mutationRate,
                                              double crossoverRate, const char *filename) {

    std::string popSize = std::to_string(populationSize);
    std::string mutRate = std::to_string(mutationRate);
    std::string crossRate = std::to_string(crossoverRate);

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

            std::string filenameToWrite = "ftv170_pop-";
            filenameToWrite += popSize;
            filenameToWrite += "_mutRate-";
            filenameToWrite += mutRate;
            filenameToWrite += "_crossRate-";
            filenameToWrite += crossRate;
            filenameToWrite += "_";
            filenameToWrite += std::to_string(i);
            filenameToWrite += ".txt";

            std::ofstream file(filenameToWrite);
            if (!file.is_open()) return;
            file << "time[s];value" << std::endl;

//            auto res = geneticAlgorithm->runTest(time, populationSize, mutationRate, crossoverRate, filenameToWrite.c_str());
            auto res = geneticAlgorithm->runV2(time, populationSize, mutationRate, crossoverRate);

            auto solutions = geneticAlgorithm->getBestSolutionFoundInTime();

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
Tests::generateFile_BestSolutionInTime_rbg403(int numberOfTestInstances, int time, int populationSize, double mutationRate,
                                              double crossoverRate, const char *filename) {

    std::string popSize = std::to_string(populationSize);
    std::string mutRate = std::to_string(mutationRate);
    std::string crossRate = std::to_string(crossoverRate);

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

            std::string filenameToWrite = "rbg403_pop-";
            filenameToWrite += popSize;
            filenameToWrite += "_mutRate-";
            filenameToWrite += mutRate;
            filenameToWrite += "_crossRate-";
            filenameToWrite += crossRate;
            filenameToWrite += "_";
            filenameToWrite += std::to_string(i);
            filenameToWrite += ".txt";

            std::ofstream file(filenameToWrite);
            if (!file.is_open()) return;
            file << "time[s];value" << std::endl;

//            auto res = geneticAlgorithm->runTest(time, populationSize, mutationRate, crossoverRate, filenameToWrite.c_str());
            auto res = geneticAlgorithm->runV2(time, populationSize, mutationRate, crossoverRate);

            auto solutions = geneticAlgorithm->getBestSolutionFoundInTime();

            for (const auto& pair : solutions) {
                file << pair.first << ';' << pair.second << '\n';
            }

            file.close();
            std::cout << std::endl;
        }
        delete graph;
    }
}
