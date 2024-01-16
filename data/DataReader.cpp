//
// Created by Szef on 25.11.2023.
//

#include <iostream>
#include <list>
#include "DataReader.h"
#include "../xmlParser/tinyxml2.h"


TSPGraph *DataReader::createGraphFromFile(const char* filePath) {
    tinyxml2::XMLDocument xmlDoc;

    if (xmlDoc.LoadFile(filePath) == tinyxml2::XML_SUCCESS) {                       //ladowanie pliku XML
        tinyxml2::XMLElement* root = xmlDoc.RootElement();                                  //pobieranie korzenia dokumentu

        if (root && strcmp(root->Name(), "travellingSalesmanProblemInstance") == 0) {        //sprawdzanie, czy korzeń jest poprawny
            const char* name = root->FirstChildElement("name")->GetText();
            const char* source = root->FirstChildElement("source")->GetText();
            const char* description = root->FirstChildElement("description")->GetText();
            int doublePrecision = 0;
            root->FirstChildElement("doublePrecision")->QueryIntText(&doublePrecision);
            int ignoredDigits = 0;
            root->FirstChildElement("ignoredDigits")->QueryIntText(&ignoredDigits);

            tinyxml2::XMLElement* vertexElement = root->FirstChildElement("graph")->FirstChildElement("vertex"); //przechodzenie przez elementy "vertex"
            int row = 0;
            int vertCount = 0;
            std::list<int> data;                                                                                              //wpisanie najpierw do listy, aby otrzymac liste elementow
            int** matrix;

            while (vertexElement) {
                tinyxml2::XMLElement* edgeElement = vertexElement->FirstChildElement("edge");
                while (edgeElement) {
                    const char* costAttribute = edgeElement->Attribute("cost");
                    int cost = (int)std::stod(costAttribute);
                    const char* edgeValue = edgeElement->GetText();
                    int column = std::stoi(edgeValue);
                    if (row == 0 ){
                        if(column != 0){                                                                    //jesli jest to pierwszy rzad macierzy to zliczaj ile ma wierzcholkow
                            vertCount++;
                            data.push_back(cost);
                        }

                    }else{                                                                                  //w przeciwnym wypadku wpisz wartosc w macierz
                        if(row != column) matrix[row][column] = cost;
                    }

                    edgeElement = edgeElement->NextSiblingElement("edge");
                }
                if(row == 0){
                    vertCount++;
                    std::cout << vertCount << std::endl;
                    matrix = new int * [vertCount];                     //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
                    for (int i = 0; i < vertCount; i++)
                    {
                        matrix[i] = new int [vertCount];
                        matrix[i][i] = (double)INT_MAX;                    //wypełnianie wartosci po przekatnej jako nieskonczonosc
                        if(i != 0)
                        {
                            matrix[0][i] = data.front();                //wpisywanie wartosci z listy (czyli pierwszego rzedu) do macierzy sasiedztwa
                            data.pop_front();
                        }

                    }
                }
                vertexElement = vertexElement->NextSiblingElement("vertex");

                row++;
            }

            return new TSPGraph(vertCount, matrix);
        } else {
            std::cerr << "Blad: Nieprawidlowy format pliku XML." << std::endl;
        }
    } else {
        std::cerr << "Blad: Nie mozna zaladowac pliku XML." << std::endl;
    }

    return nullptr;
}
