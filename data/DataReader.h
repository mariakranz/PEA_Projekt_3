//
// Created by Szef on 25.11.2023.
//

#ifndef PEA_PROJEKT2_DATAREADER_H
#define PEA_PROJEKT2_DATAREADER_H


#include <string>
#include "../graph/TSPGraph.h"

class DataReader {
public:
    static TSPGraph* createGraphFromFile(const char* filePath);                 //wczytuje dane z pliku xml do macierzy
    static int savePathToFile(std::vector<int>& path, const char* filename);    //zapisuje sciezke do pliku
    static int calculatePathFromFile(const char* filename, TSPGraph*& graph);   //odczytuje sciezke z pliku i liczy jej koszt
};


#endif //PEA_PROJEKT2_DATAREADER_H
