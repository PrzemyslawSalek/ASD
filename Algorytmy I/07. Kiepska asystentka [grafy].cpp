/*
Treść zadania
Spotkanie z informatorem zaowocowało dalszym planem działań. Partycja dostała namiary na ludzi, którzy mogli wiele wnieść do śledztwa. Zauważyła jednak, że czasem daną osobę warto jest odwiedzić wcześniej niż inne, bo może mieć informacje przydatne w kolejnych rozmowach. Poprosiła swoją główną asystentkę, by sporządziła jej propozycje planów wizyt na podstawie ustawionych przez Partycję priorytetów. Nasz bohaterka otrzymała już plany, ale ma podejrzenie, że asystentka nie zrobiła tego jak należy. Woli więc sprawdzić, czy jej lista zgadza się z ustalonymi wcześniej priorytetami.

Wejście
W pierwszej linii wejścia znajduje się liczba naturalna t, czyli liczba zestawów danych. Każdy zestaw danych składa się z dwóch liczb naturalnych n oznaczającej liczbę nazwisk i m oznaczającej liczbę par nazwisk. W kolejnych n liniach znajduje się lista wszystkich nazwisk jako jednowyrazowe łańcuchy znaków. W dalszych m liniach znajdują się pary nazwisk. Każda para oznacza, że pierwszą osobę z pary należy odwiedzić wcześniej niż drugą osobę z pary.

W ostatniej linii zestawu znajduje się lista nazwisk, oznaczająca proponowaną przez asystentkę kolejność.

1 ≤ t ≤ 10
1 ≤ n ≤ 1000000
Wyjście
Na wyjściu dla każdego zestawu danych należy wypisać słowo TAK, jeżeli proponowana kolejność jest zgodna z założeniami lub NIE w przeciwnym wypadku.

Przykład
Wejście:
2
6 5
Abramczyk 
Bednarski
Cajzer
Dzik
Elert
Frackowiak
Abramczyk Bednarski
Abramczyk Cajzer
Bednarski Dzik
Elert Frackowiak
Cajzer Dzik
Elert Abramczyk Frackowiak Cajzer Bednarski Dzik
6 5
Abramczyk 
Bednarski
Cajzer
Dzik
Elert
Frackowiak
Abramczyk Bednarski
Abramczyk Cajzer
Bednarski Dzik
Elert Frackowiak
Cajzer Dzik
Elert Frackowiak Bednarski Cajzer Abramczyk Dzik
Wyjście:
TAK
NIE
*/

#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

struct Node{
    list<Node*> next;       //lista sasiadow
    int counter = 0;        //licznik ile elemntow w niego wchodzi
};

int main() {
    ios_base::sync_with_stdio(false);

    int t;      //liczba zestawow danych
    cin >> t;   //wczytujemy liczbe zestawow

    int n;      //liczba nazwisk
    int m;      //liczba par nazwisk

    string name;    //nazwisko
    string secName; //drugie nazwisko

    string empty;   //smietnik na linie

    bool yesOrNot = true;   //wyswietlic tak czy nie?

    for(int i = 0; i < t; ++i) {
        map<string, Node*> ourMap;    //nasza mapa nazwisk
        cin >> n >> m;                  //pobieramy ilosc nazwisk i par nazwisk
        for(int j = 0; j < n; ++j) {    
            cin >> name;
            ourMap[name] = new Node;    //dodajemy elementy mapy
        }
        for(int k = 0; k < m; ++k) {
            cin >> name >> secName;     //pobieramy pierwsze i drugie imie
            ourMap[name]->next.push_back(ourMap[secName]);  //dodajemy elementy do listy sasiadow
            ourMap[secName]->counter++;     //podnosimy liczniki sasiadom (ile do nich wchodzi)
        }
        for(int l = 0; l < n; l++) {
            cin >> name;            //pobieramy ostatnia linie
            if(ourMap[name]->counter == 0) {    //jezeli licznik jest 0 to mozemy sprawdzic sasiadow
                for(auto it = ourMap[name]->next.begin(); it != ourMap[name]->next.end(); ++it) {   //iterujemy po sasiadach
                    ((*it)->counter)--;     //odejmujemy ich liczniki
                }
            }
            else {      //jezeli licznik nie jest 0
                yesOrNot = false;   //to mozemy od razu zakonczyc sprawdzanie
                getline(cin, empty);    //pobieramy reszte nazwisk w proznie
                break;  //wychodzimy z petli
            }
        }
        if(!yesOrNot) {     //wyswietlenie nie 
            cout << "NIE" << endl;
            yesOrNot = true;    //ustawiamy flage dla nastepnego zestawu
        }           
        else cout << "TAK" << endl;     //wyswietlnie tak
    }


    return 0;
}