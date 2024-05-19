#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

int* processNodes(int tab[][6], int nodes) {
    //lista wykazu co sie dzieje z nodami
    // -1 -> noda nie ruszona
    // 0 -> noda niepokorolowana
    // 1 -> noda pokolorowana
    int* Array = new int[nodes];

    for(int i=0; i<nodes; i++) {
        Array[i] = -1;
    }

    //losowe wybranie noda
    srand(time(NULL));
    int chosen_node = rand () % nodes;
    cout<<"Losowo wybrany pierwszy node: "<<chosen_node<<endl;


    int number_of_unsolved_nodes = nodes;

    while (any_of(Array, Array + nodes, [](int val) { return val == -1; })) {

        Array[chosen_node] = 1;
        number_of_unsolved_nodes--;

        cout << "niezmienione nody na poczatku petli: " << number_of_unsolved_nodes << endl;


        //niekolorowanie node polaczonych z chosen_node
        for (int j = 0; j < nodes; j++) {
            if (tab[chosen_node][j] == 0) {
                continue;
            } else if (tab[chosen_node][j] == 1 &&
                       Array[j] == -1) {
                Array[j] = 0;
                number_of_unsolved_nodes--;
            }
        }

        //test czy dziala
        cout << "array po zmianie ";
        for (int i = 0; i < nodes; i++) {
            cout << Array[i] << " ";
        }
        cout << "\n";


        cout << "ilosc niezmienionych nodow: " << number_of_unsolved_nodes << endl;

        //jezeli number_of_unsolved_nodes jest rowny zero to koniec analizy, wszystko jest skonczone
        if(number_of_unsolved_nodes == 0) break;

        //zmieniamy wartosc chosen_node na ta dla ktorej w tablicy jest -1, czyli nie jest jeszcze sprawdzona
        int array_with_only_negatives[number_of_unsolved_nodes];
        int k = 0;

        //tworze liste z indeksami miejsc na jakich w liscie Array stoja "-1"
        for (int i = 0; i < nodes; i++) {
            if (Array[i] == -1) {
                array_with_only_negatives[k] = i;
                k++;
            }
        }

        //drukowanie tej listy
        cout<<"Lista indeksow gdzie w array stoja -1 : ";
        for (int i = 0; i < k; i++) {
            cout << array_with_only_negatives[i] << " ";
        }
        cout << endl;

        //wybieranie randomowej pozycji z listy array_with_only_negatives
        int randomIndex = rand() % number_of_unsolved_nodes;

        cout<< "random index: " << randomIndex <<endl;

        //zczytanie wartosci w tablicy number_of_unsolved_nodes na miejscu randomIndex
        //przypisanie nowego chosen_node
        chosen_node = array_with_only_negatives[randomIndex];

        cout<< "nowo wybrany node: " << chosen_node <<endl;

    };

    return Array;
}

int main() {
    int tab[6][6] = {0,1, 0,0,0,1,
                     1,0,0,1,0,0,
                     0,0,0,1,1,1,
                     0,1,1,0,0,0,
                     0,0,1,0,0,0,
                     1,0,1,0,0,0};
    int nodes = 6;

    //show matrix
    for(int i=0; i<nodes; i++) {
        for(int j=0; j<nodes; j++) {
            cout<< tab[i][j] << " ";
        }
        cout<<"\n";
    } cout<<"\n";

    int* Array = processNodes(tab, nodes);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < nodes; i++) {
        if(Array[i] == 1) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout << Array[i] << " ";
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset koloru
        } else {
            cout << Array[i] << " ";
        }
    }
    cout << endl;

    //zwolnienie pamieci
    delete[] Array;

    return 0;
}


