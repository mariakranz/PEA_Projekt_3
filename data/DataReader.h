//
// Created by Szef on 25.11.2023.
//

#ifndef PEA_PROJEKT_3_DATAREADER_H
#define PEA_PROJEKT_3_DATAREADER_H


#include <string>
#include "../graph/TSPGraph.h"

class DataReader {
public:
    static TSPGraph* createGraphFromFile(const char* filePath);                 //wczytuje dane z pliku xml do macierzy
};


#endif //PEA_PROJEKT_3_DATAREADER_H
