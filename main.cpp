#include <iostream>
#include <algorithm>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
#include "algorithms/GeneticAlgorithm.h"
#include "data/Tests.h"

using namespace std;

void menu();
void testsDialog();
void testInverseMutation();
void testSwapMutation();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    menu();
    return 0;
}


void menu(){
    string filePath;
    GeneticAlgorithm* ga = nullptr;
    TSPGraph* graph = nullptr;
    int time, populationSize = 0;
    double mutationRate, crossoverRate = 0.0;
    int mutationType = 0;
    string summary;

    int choice;
    Individual solution;

    do{
        cout << "\n----MENU----\n"
                "1. Wczytanie danych z pliku (xml).\n"
                "2. Wprowadzenie kryterium stopu.\n"
                "3. Ustawienie wielkosci populacji.\n"
                "4. Ustawienie wspolczynnika mutacji.\n"
                "5. Ustawienia wspolczynnika krzyzowania.\n"
                "6. Wybor metody metody mutacji.\n"
                "7. Uruchomianie algorytmu dla wczytanych danych i ustawionych parametrow i wyswietlenie wynikow.\n"
                "8. Testy.\n"
                "0. Wyjdz z programu.\n"
                "Wprowadz numer: ";
        cin >> choice;
        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case 0: break;
            case 1:
                cout << "Podaj nazwe pliku: ";                                      //"..\\data_files\\ftv170.xml
                cin >> filePath;
                delete graph;                       //usun stary graf (jesli byl)
                graph = DataReader::createGraphFromFile(filePath.c_str());
                if (graph != nullptr){
                    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
                }else{
                    cerr << "Bledy przy odczytywaniu danych." << endl;
                }
                break;
            case 2:
                cout << "Podaj czas [s]: ";
                cin >> time;
                break;
            case 3:
                cout << "Podaj wielkosc populacji: ";
                cin >> populationSize;
                break;
            case 4:
                cout << "Podaj wspolczynnik mutacji: ";
                cin >> mutationRate;
                break;
            case 5:
                cout << "Podaj wspolczynnik krzyzowania: ";
                cin >> crossoverRate;
                break;
            case 6:
                cout << "Wybierz metode mutacji: \n"
                        "1. Inversion mutation.\n"
                        "2. Swap mutation.\n"
                        "Twoj wybor:";
                cin >> mutationType;
                break;
            case 7:
                if(graph == nullptr) {
                    cout << "Nie zaladowano grafu." << endl;
                    break;
                }
                if(time == 0){
                    cout << "Nie ustawiono warunku stopu." << endl;
                    break;
                }
                if(populationSize == 0){
                    cout << "Nie ustawiono wielkosci populacji." << endl;
                    break;
                }
                if(mutationRate == 0){
                    cout << "Nie ustawiono wspolczynnika mutacji." << endl;
                    break;
                }
                if(crossoverRate == 0){
                    cout << "NIe ustawiono wspolczynnika krzyzowania." << endl;
                    break;
                }
                if(mutationType == 0){
                    cout << "Nie wybrano metody mutacji." << endl;
                    break;
                }

                delete ga;
                ga = new GeneticAlgorithm(graph);

                Mutation type;
                switch (mutationType) {
                    case 1:
                        type = inverseMut;
                        break;
                    case 2:
                        type = swapMut;
                        break;
                }

                summary = "Rozwiazanie problemu komiwojazera - Algorytm genetyczny. Parametry:\n";
                summary += "Kryterium stopu: " + to_string(time) + "\n";
                summary += "Rozmiar populacji: " + to_string(populationSize) + "\n";
                summary += "Wspolczynnik mutacji: " + to_string(mutationRate) + "\n";
                summary += "Wspolczynnik krzyzowania: " + to_string(crossoverRate) + "\n";
                summary += "Metoda mutacji: " + GeneticAlgorithm::getMutationTypeToString(type) + "\n";
                summary += "Generowanie rozwiazania...\n";

                cout << summary;

                solution = ga->run(time, populationSize, mutationRate, crossoverRate, type);

                cout << "Koszt: " << solution.cost << endl;
                cout << "Sciezka: ";

                for (int i : solution.path){
                    cout << i << " ";
                }
                cout << endl;
                break;
            case 8:
                testsDialog();
                break;
        }
    }while (choice != 0);

    delete graph;
}

void testsDialog()
{
    cout << "Pliki: ftv47.xml, ftv170.xml, rbg403 musza znajdowac sie w tym samym folderze co plik wykonywalny .exe\n"
            "Przewidywany czas testu: 4h +\n"
            "Kontynuowac? 'T' - tak, 'N' - nie\n";
    char ans = 'N';
    cin >> ans;
    switch(ans)
    {
        default:
            cout << "Nie ma takiej opcji." << endl;
        case 'N':
            break;
        case 'T':
            testInverseMutation();
            testSwapMutation();
            break;
    }
}


void testInverseMutation()
{
    const int numberOfTestInstances = 10;
    const double mutationRate = 0.01;
    const double crossoverRate = 0.8;
    const int populationSize[3] = {500, 2000, 5000};
    Mutation mutationType = inverseMut;

    string data47 = "ftv47.xml";
    const int time47 = 120;
    string data170 = "ftv170.xml";
    const int time170 = 240;
    string data403 = "rbg403.xml";
    const int time403 = 360;
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[0], 0.01, 0.8,
                                                 data47.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[1], 0.01, 0.8,
                                                 data47.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[2], 0.01, 0.8,
                                                 data47.c_str(), mutationType);

    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[0], mutationRate,
                                                  crossoverRate, data170.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[1], mutationRate,
                                                  crossoverRate, data170.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[2], mutationRate,
                                                  crossoverRate, data170.c_str(), mutationType);

    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[0], mutationRate,
                                                  crossoverRate, data403.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[1], mutationRate,
                                                  crossoverRate, data403.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[2], mutationRate,
                                                  crossoverRate, data403.c_str(), mutationType);
}

void testSwapMutation(){
    const int numberOfTestInstances = 10;
    const double mutationRate = 0.01;
    const double crossoverRate = 0.8;
    const int populationSize[3] = {500, 2000, 5000};
    Mutation mutationType = swapMut;

    string data47 = "ftv47.xml";
    const int time47 = 120;
    string data170 = "ftv170.xml";
    const int time170 = 240;
    string data403 = "rbg403.xml";
    const int time403 = 360;
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[0], 0.01, 0.8,
                                                 data47.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[1], 0.01, 0.8,
                                                 data47.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[2], 0.01, 0.8,
                                                 data47.c_str(), mutationType);

    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[0], mutationRate,
                                                  crossoverRate, data170.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[1], mutationRate,
                                                  crossoverRate, data170.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[2], mutationRate,
                                                  crossoverRate, data170.c_str(), mutationType);

    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[0], mutationRate,
                                                  crossoverRate, data403.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[1], mutationRate,
                                                  crossoverRate, data403.c_str(), mutationType);
    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[2], mutationRate,
                                                  crossoverRate, data403.c_str(), mutationType);
}

