#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
#include "algorithms/GeneticAlgorithm.h"

using namespace std;

void menu();
void testsDialog();
void test();
void temp();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    //menu();
    temp();
    return 0;
}

void temp(){
    TSPGraph *graph = DataReader::createGraphFromFile("..\\data_files\\ftv47.xml");
    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
    GeneticAlgorithm::run(30, 10, 0.8, 0.1, graph);
}

void menu(){
    string filePath;
    TSPGraph *graph = nullptr;
    int time, populationSize, mutationRate, crossoverRate = 0;
    char choice;
    std::vector<int> solution;

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
                "9. Testy.\n"
                "0. Wyjdz z programu.\n"
                "Wprowadz numer: ";
        cin >> choice;
        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case '0': break;
            case '1':
                cout << "Podaj nazwe pliku: ";                                      //"..\\data_files\\ftv170.xml
                cin >> filePath;
                delete graph;                       //usun stary graf (jesli byl)
                graph = DataReader::createGraphFromFile(filePath.c_str());
                if (graph != nullptr){
                    //ts->setGraph(graph);
                    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVerticesNumber());
                }else{
                    cerr << "Bledy przy odczytywaniu danych." << endl;
                }
                break;
            case '2':
                cout << "Podaj czas [s]: ";
                cin >> time;
                //ts->setStopTime(time);
                break;
            case '3':
                cout << "Podaj wielkosc populacji: ";
                cin >> populationSize;
                break;
            case '4':
                cout << "Podaj wspolczynnik mutacji: ";
                cin >> mutationRate;
                break;
            case '5':
                cout << "Podaj wspolczynnik krzyzowania: ";
                cin >> crossoverRate;
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
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

                GeneticAlgorithm::run(time, populationSize, mutationRate, crossoverRate, graph);

                break;
            case '9':
                testsDialog();
                break;
        }
    }while (choice != '0');

    delete graph;
}

void testsDialog()
{
    cout << "Pliki: ftv55.xml, ftv170.xml, rbg380 musza znajdowac sie w tym samym folderze co plik wykonywany .exe\n"
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
}