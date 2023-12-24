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

std::vector<int> TSPGraph::greedyTSP() {
    std::vector<bool> visited(verticesNumber, false);
    std::vector<int> path(verticesNumber);
    std::vector<int> minPath(verticesNumber);
    int minCost = INT_MAX;

    for(int i = 0; i < verticesNumber; i++){                                //oblicza sciezke zachlannie dla kazdego wierzcholka
        int currentVertex = i;
        path[0] = currentVertex;
        visited[currentVertex] = true;

        for (int i = 1; i < verticesNumber; ++i) {
            int minDistance = INT_MAX;
            int nextVertex = -1;


            for (int j = 0; j < verticesNumber; ++j) {                          //szuka najblizszego nieodwiedzonego miasta
                if (!visited[j]) {
                    int distance = adjacencyMatrix[currentVertex][j];
                    if (distance < minDistance) {
                        minDistance = distance;
                        nextVertex = j;
                    }
                }
            }

            visited[nextVertex] = true;                                         //dodaje najblizsze miasto do sciezki
            path[i] = nextVertex;
            currentVertex = nextVertex;
        }

        int cost = calculateTour(path);                                     //oblicza sciezke i jesli mniejsza niz dotychczasowa znaleziona to ja zapamietaj
        if( cost < minCost){
            minPath.assign(path.begin(), path.end());
            minCost = cost;
        }
        for(auto && v : visited){
            v = false;
        }

    }
    return minPath;
}

int TSPGraph::calculateTour(std::vector<int> tour) {
    int res = 0;
    for(int i = 0; i < verticesNumber - 1; i++){
        res+= adjacencyMatrix[tour[i]][tour[i+1]];
    }
    res+= adjacencyMatrix[tour.back()][tour.front()];
    return res;
}



