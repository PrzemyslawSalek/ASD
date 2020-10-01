/*
Treść zadania
Partycja Logiczna przemyślała swoje plany i doszła do wniosku, że może obniżyć swój stres na niektórych postojach. W końcu uwielbia jeść, a to na pewno obniża kortyzol w jej organizmie. Przynajmniej będzie tak pomiędzy postojami. Nasza bohaterka rozbudowała opis postojów na siatce o dodatkową wartość v. Ta wartość to liczba, która reprezentuje ilość jednostek stresu, jaką może obniżyć dany postój.

Usprawnij poprzedni program tak by brał pod uwagę ewentualne przyjemności kulinarne na postojach.

WEJŚCIE
W pierwszej linii wejścia znajduje się liczba naturalna n, mówiąca o ilości postojów. Następnie program powinien wczytać n sekwencji danych: x y v, które są współrzędnymi postojów na naniesionej przez Partycje siatce. Na koniec program powinien wczytać dwie liczby naturalne s i d, które są odpowiednio postojem startowym i postojem docelowym, czyli siedzibą instytucji, do której zmierza nasza bohaterka. Każdy postój ma inne współrzędne.

0 <= n, v <= 32000
0 <= x, y, s, d <= 2000000000

WYJŚCIE
Na wyjściu algorytm powinien wypisać jedną liczbę całkowitą, która jest możliwie najmniejszą liczbą jednostek stresu, które przeżyje nasza bohaterka na trasie z punktu s do punktu d. Może dojść do sytuacji, gdy podróżowanie na pewnym odcinku będzie przynosiło Partycji ciągłe przyjemności. W takiej sytuacji należy zmusić naszą bohaterkę by szybko wróciła na trasę do Warszawy wyświetlając komunikat: NIE ZA DOBRZE?

PRZYKŁADOWE DANE WEJŚCIOWE
I

5
2 2 0
1 1 0
4 5 1
7 1 0
6 7 0
0 4
II

5
2 2 0
1 1 1
4 5 1
7 1 0
6 7 0
0 4
PRZYKŁADOWE DANE WYJŚCIOWE
I

2
II

NIE ZA DOBRZE?
*/

#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <climits>

using namespace std;

//struktura dla postoju
struct Node {
    bool visited;                                                           //flaga odwiedzony
    int index;                                                              //indeks postoju
    int x, y, v;                                                            //wspolrzedne postoju i ilosc jednostek stresu do obnizenia
    list<int> sasiedzi;                                                     //lista sasiadow (elementow najblizej wedlug x i wedlug y (maksymalnie 4))
};

bool comp_sorted_list_x(Node &a, Node &b) {                                 //komperator do sortowania po x rosnaco
    return a.x < b.x;
}

bool comp_sorted_list_y(Node &a, Node &b) {                                 //komperator do sortowania po y rosnaco
    return a.y < b.y;
}

int distance(Node a, Node b) {                                                  //funkcja liczaca dystans miedzy postojami
    if(abs(a.x-b.x) < abs(a.y-b.y)) return abs(a.x-b.x)-b.v;                    //zwroc roznice miedzy x jezeli jest mniejsza niz roznica miedzy y
    else return abs(a.y-b.y)-b.v;                                               //w przeciwnym wypadku zwroc roznice miedzy y
}

int main() {
    ios_base::sync_with_stdio(false);                       //magiczna linijka

    int n;                                                  //ilosc postojow 0 <= n <= 32000
    cin >> n;                                               //pobieramy ilosc postojow  0 <= x, y, s, d <= 2000000000

    Node *arr;                                              //tablica na punkty postojow (wspolrzedne x, y)
    arr = new Node[n];                                      //allokowanie tablicy postojow (wspolrzednych x, y)

    Node *sorted_arr;                                       //kopia tablicy ktora bedziemy sortowac wedlug x a potem y
    sorted_arr = new Node[n];                               //allokowanie tablicy

    int x, y, v;                                            //tymczasowe zmienne na x i y
    int s, d;                                               //postoj startowy, postoj docelowy

    for(int i = 0; i < n; i++) {
        cin >> x >> y >> v;                                 //wczytujemy pary wspolrzednych
        Node new_n;                                         //chwilowa zmienna dla postoju
        new_n.index = i; new_n.x = x; new_n.y = y;          //przypisujemy jej dane
        new_n.v = v; new_n.visited = false;                 //przypisujemy wspolczynnik przyjemnosci i flage visited ustawiamy na nieodwiedzona
        arr[i] = new_n;                                     //zapisujemy do podstawowej tablicy
        sorted_arr[i] = new_n;                              //zapisujemy do kopii tablicy
    }

    sort(sorted_arr, sorted_arr+n, comp_sorted_list_x);                                             //sortujemy wedlug x rosnaco

    for(int i = 0; i < n; i++) {
        if(i == 0)                                                                                  //jezeli jest rowne zero
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //to bierzemy sasiada tylko dalszego
        else if(i == n-1)                                                                           //jezeli jest ostatnim elemenetem
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //to bierzemy tylko wczesniejszego
        else {                                                                                      //w innym przypadku
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //bierzemy wczesniejszego
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //i dalszego
        }
    }

    sort(sorted_arr, sorted_arr+n, comp_sorted_list_y);                                             //sortujemy wedlug y rosnaco

    for(int i = 0; i < n; i++) {
        if(i == 0)                                                                                  //jezeli jest rowne zero
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //to bierzemy sasiada tylko dalszego
        else if(i == n-1)                                                                           //jezeli jest ostatnim elemenetem
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //to bierzemy tylko wczesniejszego
        else {                                                                                      //w innym przypadku
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //bierzemy wczesniejszego
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //i dalszego
        }
    }

    cin >> s >> d;                                  //wczytujemy postoj startowy oraz docelowy

    int *stress;                                    //tablica do algorytmu Dijkstry
    stress = new int[n];                            //(do szukania drogi z najmniejszym stresem)

    queue<int> que;                                 //kolejka  na indeksy zmienionych elementów

    for(int i = 0; i < n; i++) {
        if(i != s) stress[i] = INT_MAX;             //element wypelniamy "nieskonczonoscia"
        else stress[i] = 0;                         //natomiast elementowi startowy ustawiamy 0
    }

    bool lastChange = false;                        //gdy w ostanim obrocie wprowadzimy jakas zmiane to wyrzucamy napis (cykl ujemny)
    bool change = false;                            //gdy nic sie nie zmieni w obrocie to mozemy skonczy bo nic sie juz nie zmieni w kolejnych
    bool dsmall = false;                            //gdy suma odlegosci miedzy A-B i B-A jest mniejsza od 0 to mamy cykl ujemny i wyswietlamy napis

    for(int i = 0; i < n; i++) {                                    //petla dla n obrotow do algorytmu Forda-Bellmana
        que.push(s);                                                //pushujemy zawsze wierzcholek startowy bo musimy od czegos zaczac
        change = false;                                             //ustawiamy change na false dla kolejnego obrotu
        while(!que.empty()) {                                       //dopoki kolejka nie jest pusta
            int top_val = que.front(); que.pop();                   //sciagamy najmniejszy wierzcholek
            for(auto x : arr[top_val].sasiedzi) {                   //przegladamy jego wszystkich sasiadow
                if(arr[x].visited == false) {                       //jezeli sasiad jest nieodwiedzony
                    que.push(x);                                    //dodajemy go do kolejki

                    int d1 = distance(arr[top_val], arr[x]);        //obliczamy dystans miedzy wierzcholkiem z kolejki a jego sasiadem
                    int diA = d1+stress[top_val];                   //dystan + wartosc z tablicy
                    if(diA < stress[x]) {                           //jezelu aktualna wartosc jest lepsza (mniejsza) niz ta z tablicy
                        change = true;                              //to flage zmiany ustawiamy na true
                        stress[x] = diA;                            //podmieniamy wartosc w tablicy na nowa
                        if(i == n-1) {                              //kiedy jest to ostatni obrot petli glownej
                            lastChange = true;                      //to ustawiamy flage ostatniej zmiany na true i wyrzucamy napis
                            break;                                  //wychodzimy ze wszystkich petli
                        }
                    }

                    int d2 = distance(arr[x], arr[top_val]);        //wszystko tak samo tylko sprawdzamy odleglosc w druga strone
                    int diB = d2+stress[x];                         //od sasiada do wierzcholka z kolejki
                    if(diB < stress[top_val]) {
                        change = true;
                        stress[top_val] = diB;
                        if(i == n-1) {
                            lastChange = true;
                            break;
                        }
                    }

                    if(d1+d2 < 0) {                                 //gdy suma odleglosci AB i BA jest mniejsza od 0
                        dsmall = true;                              //ustawiamy flage na true i zwracamy napis bo cykl jest ujemny
                        break;                                      //wychodzimy ze wszystkich petli
                    }
                }
            }
            arr[top_val].visited = true;                            //ustawiamy wierzcholek jako odwiedzony
            if(dsmall || lastChange) break;                         //wyrzucamy petle while z powodu jakiejs flagi
        }
        if(!change || dsmall || lastChange) break;                  //wyrzucamy petle glowna z powodu jakiejs flagi

        for(int i = 0; i < n; i++) arr[i].visited = false;          //ustawiamy wszystkim nieodwiedzony dla kolejnego obrotu petli glownej
    }

    if(lastChange || dsmall) cout << "NIE ZA DOBRZE?" << endl;      //wyswietlamy napis bo cykl jest ujemny
    else cout << stress[d] << endl;                                 //wyswietlamy wynik bo cykl jest nieujemny


    return 0;
}