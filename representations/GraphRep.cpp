//
// Created by Szef on 25.11.2023.
//

#include <iostream>
#include "GraphRep.h"

void GraphRep::printAdjacencyMatrix(int **table, int verticesNum) {
    std::cout << "Macierz sasiedztwa:" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < verticesNum; i++){
        std::cout.width(10);
        std::cout << i;
    }
    std::cout << std::endl;

    for (int i = 0; i < verticesNum; i++) {
        std::cout.width(10);
        std::cout << i;
        for (int j = 0; j < verticesNum; j++){
            std::cout.width(10);
            double cost = table[i][j];
            if (cost == INT_MAX) std::cout << "-";
            else std::cout << cost;
        }
        std::cout << std::endl;
    }
}
