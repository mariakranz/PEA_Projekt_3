#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
#include "algorithms/GeneticAlgorithm.h"
#include "data/Tests.h"

using namespace std;

void menu();
void testsDialog();
void test();
void test47();
void test170();
void test403();
void temp();
void temt2();
void test1();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    //test();
    //test1();
    menu();
    //temp();
 //   test47();
    //test170();
    //test403();
    return 0;
}

void temp(){
    TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\ftv47.xml");

    //TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\ftv170.xml");

    //TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\rbg403.xml");

    //GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
    auto ga = new GeneticAlgorithm(graph);
    auto result = ga->runV2(120, 5000, 0.01, 0.8);
//    auto result = ga->runV2(240, 5000, 0.01, 0.8);
//    auto result = ga->runV2(360, 5000, 0.01, 0.8);


    cout << "Koszt: " << result.cost << endl;
    cout << "Sciezka: ";

    for (int i  = 0; i < result.path.size(); i++){
        cout << result.path[i] << " ";
    }

    cout << endl;
    //GeneticAlgorithm::runOlderVersion(30, 10, 0.8, 0.1, graph);
}

void test47(){
    TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\ftv47.xml");
    auto ga = new GeneticAlgorithm(graph);
    auto result = ga->runV2(120, 5000, 0.01, 0.8);
    cout << "Koszt: " << result.cost << endl;
    cout << "Sciezka: ";

    for (int i  = 0; i < result.path.size(); i++){
        cout << result.path[i] << " ";
    }

    cout << endl;
}

void test170(){
    TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\ftv170.xml");
    auto ga = new GeneticAlgorithm(graph);
    auto result = ga->runV2(60, 5000, 0.01, 0.8);
    cout << "Koszt: " << result.cost << endl;
    cout << "Sciezka: ";

    for (int i  = 0; i < result.path.size(); i++){
        cout << result.path[i] << " ";
    }

    cout << endl;
}

void test403(){
    TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\rbg403.xml");
    auto ga = new GeneticAlgorithm(graph);
    auto result = ga->runV2(360, 5000, 0.01, 0.8);
    cout << "Koszt: " << result.cost << endl;
    cout << "Sciezka: ";

    for (int i  = 0; i < result.path.size(); i++){
        cout << result.path[i] << " ";
    }

    cout << endl;
}


void menu(){
    string filePath;
    GeneticAlgorithm* ga = nullptr;
    TSPGraph* graph = nullptr;
    int time, populationSize = 0;
    double mutationRate, crossoverRate = 0.0;
    int choice;
    Individual solution;

    do{
        cout << "\n----MENU----\n"
                "1. Wczytanie danych z pliku (xml).\n"
                "2. Wprowadzenie kryterium stopu.\n"
                "3. Ustawienie wielkosci populacji poczatkowej.\n"
                "4. Ustawienie wspolczynnika mutacji.\n"
                "5. Ustawienia wspolczynnika krzyzowania.\n"
                "6. Wybor metody krzyzowania (opcjonalnie).\n"
                "7. Wybor metody metody mutacji (opcjonalnie).\n"
                "8. Uruchomianie algorytmu dla wczytanych danych i ustawionych parametrow i wyswietlenie wynikow.\n"
                "9. Zapis sciezki rozwiazania do pliku (txt).\n"
                "10. Obliczenie wartosci sciezki z pliku (txt).\n"
                "11. Testy.\n"
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
                if(solution.cost){
                    cout << "Podaj nazwe pliku: ";
                    cin >> filePath;
                    if(DataReader::savePathToFile(solution.path, filePath.c_str()) == -1){
                        cout << "Blad przy zapisie do pliku." << endl;
                    }else{
                        cout << "Zapisano w pliku " << filePath << "." << endl;
                    }
                }else{
                    cout << "Nie wygenerowano rozwiazania" << endl;
                }
                break;
            case 7:
                if(graph){
                    cout << "Podaj nazwe pliku: ";
                    cin >> filePath;
                    int result = -1;
                    result = DataReader::calculatePathFromFile(filePath.c_str(), graph);
                    if(result == - 1){
                        cout << "Blad przy odczytywaniu pliku." << endl;
                    }else{
                        cout << "Koszt: " << result << endl;
                    }
                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case 8:
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
                    cout << "NIe ustawiono wspolczynnika krzyzowania" << endl;
                    break;
                }

                delete ga;
                ga = new GeneticAlgorithm(graph);
                solution = ga->runV2(time, populationSize, mutationRate, crossoverRate);

                cout << "Koszt: " << solution.cost << endl;
                cout << "Sciezka: ";

                for (int i : solution.path){
                    cout << i << " ";
                }

                cout << endl;
                break;
            case 9:
                if(solution.cost != 0){
                    cout << "Podaj nazwe pliku: ";
                    cin >> filePath;
                    if(DataReader::savePathToFile(solution.path, filePath.c_str()) == -1){
                        cout << "Blad przy zapisie do pliku." << endl;
                    }else{
                        cout << "Zapisano w pliku " << filePath << "." << endl;
                    }
                }else{
                    cout << "Nie wygenerowano rozwiazania" << endl;
                }
                break;
            case 10:
                if(graph){
                    cout << "Podaj nazwe pliku: ";
                    cin >> filePath;
                    int result = -1;
                    result = DataReader::calculatePathFromFile(filePath.c_str(), graph);
                    if(result == - 1){
                        cout << "Blad przy odczytywaniu pliku." << endl;
                    }else{
                        cout << "Koszt: " << result << endl;
                    }
                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case 11:
                testsDialog();
                break;
        }
    }while (choice != 0);

    delete graph;
}

void testsDialog()
{
    cout << "Pliki: ftv47.xml, ftv170.xml, rbg403 musza znajdowac sie w tym samym folderze co plik wykonywany .exe\n"
            "Przewidywany czas testu: 6h\n"
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
            test();
            break;
    }
}


void test()
{
    const int numberOfTestInstances = 10;
    const double mutationRate = 0.01;
    const double crossoverRate = 0.8;
    const int populationSize[3] = {500, 2000, 5000};

    string data47 = "ftv47.xml";
    const int time47 = 120;
    string data170 = "ftv170.xml";
    const int time170 = 240;
    string data403 = "rbg403.xml";
    const int time403 = 360;
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[0], 0.01, 0.8,data47.c_str());
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[1], 0.01, 0.8, data47.c_str());
    Tests::generateFile_BestSolutionInTime_ftv47(numberOfTestInstances, time47, populationSize[2], 0.01, 0.8, data47.c_str());

    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[0], mutationRate, crossoverRate, data170.c_str());
    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[1], mutationRate, crossoverRate, data170.c_str());
    Tests::generateFile_BestSolutionInTime_ftv170(numberOfTestInstances, time170, populationSize[2], mutationRate, crossoverRate, data170.c_str());

    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[0], mutationRate, crossoverRate, data403.c_str());
    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[1], mutationRate, crossoverRate, data403.c_str());
    Tests::generateFile_BestSolutionInTime_rbg403(numberOfTestInstances, time403, populationSize[2], mutationRate, crossoverRate, data403.c_str());
}

void test1(){
    Tests::generateFile_BestSolutionInTime_ftv47(10, 10, 500, 0.01, 0.8,"ftv170.xml");
}