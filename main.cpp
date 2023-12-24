#include <iostream>
#include <vector>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graph/TSPGraph.h"
using namespace std;

void menu();
void testsDialog();
void test();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    menu();
    return 0;
}

void menu(){
    string filePath;
    TSPGraph *graph = nullptr;
    int time;
    int neighborhood;
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
                break;
            case '4':
                if(graph){

                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
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