//
// Created by Szef on 25.11.2023.
//

#ifndef PEA_PROJEKT2_TSPGRAPH_H
#define PEA_PROJEKT2_TSPGRAPH_H


#include <vector>


class TSPGraph {
private:
    int verticesNumber;
    int** adjacencyMatrix;                              //macierz sąsiedztwa - tablica dwuwymiarowa

public:
    TSPGraph();
    TSPGraph(int verticesNumber, int**& adjacencyMatrix);
    ~TSPGraph();
    int** getAdjMatrix();
    int getVerticesNumber();

    std::vector<int> greedyTSP();                       //zwraca sciezke uzyskana za pomoca metody zachlannej

    int calculateTour(std::vector<int> tour);           //oblicza koszt sciezki
};


#endif //PEA_PROJEKT2_TSPGRAPH_H
