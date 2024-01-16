//
// Created by Szef on 25.11.2023.
//

#include <climits>
#include <iostream>
#include "TSPGraph.h"

TSPGraph::TSPGraph(int verticesNumber, int **&adjacencyMatrix) {
    this->verticesNumber = verticesNumber;
    this->adjacencyMatrix = adjacencyMatrix;
}

TSPGraph::TSPGraph() {
    verticesNumber = 0;
    adjacencyMatrix = nullptr;
}

TSPGraph::~TSPGraph() {
    if (adjacencyMatrix != nullptr) {
        for (int i = 0; i < verticesNumber; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
}

int **TSPGraph::getAdjMatrix() {
    return adjacencyMatrix;
}

int TSPGraph::getVerticesNumber(){
    return verticesNumber;
}

int TSPGraph::calculateTour(std::vector<int> tour) {
    int res = 0;
    for(int i = 0; i < verticesNumber - 1; i++){
        res+= adjacencyMatrix[tour[i]][tour[i+1]];
    }
    res+= adjacencyMatrix[tour.back()][tour.front()];
    return res;
}



