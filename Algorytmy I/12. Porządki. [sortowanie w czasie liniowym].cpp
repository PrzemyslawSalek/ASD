/*
Treść zadania
Sylwestra Partycja spędziła w domu. Nie miała ochoty iść tego dnia na jakąkolwiek imprezę. No bo czego miałby życzyć innym o północy? Szczęśliwych ostatnich dziewięciu miesięcy ludzkiej cywilizacji? Nie, Partycja zdecydowanie nie miała na to ochoty. Postanowiła posegregować zebrane do tej pory akta prowadzonego przez nią śledztwa.

Wszystkie dokumenty zebrane przez Partycję mają swoj unikalne numery (od 1 do n, gdzie n jest liczbą dokumentów), priorytety (liczba całkowita z zakresu od 0 do 10), losowe kody z zakresu od 0 do 10000000 (niekoniecznie unikalne) oraz zostały oznaczone symbolami tematyki dokumentu (maksymalnie 4 liczby z zakresu od 0 do 255 uporządkowane od symbolu najbardziej istotnego do najmniej istotnego, czasami przez pomyłkę ten sam symbol może wystąpić wielokrotnie, ale Partycji nie chce się tego poprawiać). Partycja chce móc sortować dokumenty:

rosnąco po numerach,
rosnąco po priorytetach,
rosnąco po kodach,
leksykograficznie względem listy kodów tematów (w pierwszej kolejności porównuje symbole najbardziej istotne na poszczególnych listach, potem drugie itd., jeżeli jakiś ciąg symboli jest początowym podciągiem innego, to jest wcześniej w kolejności lekykograficznej)
Partycja, chciałaby móc sortować po wszystkich wyżej wymienionych parametrach, ale przy różnym uszeregowaniu ważności poszczególnych prametrów (na przykład w pierwszej kolejności po priotytetach, w drugiej po kodach itd.).

Wejście
Na wejściu program otrzymuje liczbę n, a następnie n opisów dokumentów. Opis każdego z dokumentów składa się z unikalnego numeru, priorytetu, losowego kodu, liczby m kodów tematów dotyczących danego dokumentu (z zakresu od 1 do 4) a następnie m liczb z zakreso do 0 do 255. Na końcu program otrzyma liczby 1, 2, 3 i 4 odpowiadające kolejno numerom, priorytetom, kodom dokumentów oraz kodom tematów uporządkowane względem ich wagi przy sortowaniu.

1<=n<=2000000
Wyjście
Na standardowym wyjściu program powinien wypisać sumę losowych kodów poszczególnych dokumentow pomnożonych przez finalny indeks elementu w posortowanej tablicy. Wynik powinien zostać wypisany modulo 100000007.

Przykłady
Wejście
5
2 10 145 2 0 1
4 2 1119 4 255 0 1 2
1 10 0 2 0 1
3 5 2 4 255 0 1 2
5 10 99999 1 24
4 2 3 1
Wyjście
203508
Wejście
5
2 10 145 2 0 1
4 2 1119 4 255 0 1 2
1 10 0 2 0 1
3 5 2 4 255 0 1 2
5 10 99999 1 24 
4 3 2 1
Wyjście
204625
Wejście
1
1 10 0 2 0 1
1 2 3 4
Wyjście
0
UWAGA rozwiąż problem przy pomocy samodzielnie zaimplementowanych algorytmów sortujących w czasie liniowym.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//struktura na opis dokumentu//
struct Document {
    int num;                            //unikalny numer
    int priority;                       //priorytet
    long long code;                     //losowy kod
    int topics[4] = {-1, -1, -1, -1};   //tematy (moga byc od 1 do 4 wiec puste wypelniam -1)
};

//funkcja licząca wynik końcowy//
long long result(Document *arr[],int n) {

    long long suma = 0;

    for(int i = 0; i < n; ++i) {
        suma += (arr[i]->code*i);
        suma = suma%100000007;
    }

    return suma%100000007;
}

int main() {
    ios_base::sync_with_stdio(false);   //magiczna linijka

    int n;                              //liczba opisow dokumentow
    cin >> n;

    Document *documents[n];             //tablica na wskazniki dokumentów
    int m;                              //ilosc tematow

    int prio[4];                        //tablica na priorytety sortowania

    for(int i = 0; i < n; ++i) {        //pobieramy dokumenty
        Document *doc = new Document;
        cin >> doc->num >> doc->priority >> doc->code >> m;
        for(int j = 0; j < m; ++j) cin >> doc->topics[j];
        doc->num -= 1;
        documents[doc->num] = doc;  //wrzucamy do tablicy po unikalnym numerze (sortowanie po 1 kolumnie)
    }

    int start = 3;

    for(int d = 0; d < 4; d++) {        //pobieramy priorytety sortowania
        cin >> prio[d];
        if(prio[d] == 1) {              //ustawiamy wartosc od ktorej sortujemy
            if(d == 0) start = 0;
            else start = d-1;
        }
    }

    for(int i = start; i >= 0; --i) {       //glowna petla do sortowania kubelkowego
            if(prio[i] == 2) {              //gdy piorytet rowny jest 2 (sortowanie po 2 kolumnie)
                int k = 0;
                vector<Document*> vectora[11];  //tworzymy kubełki
                for(int j = 0; j < n; j++) {
                    vectora[documents[j]->priority].push_back(documents[j]);    //wrzucamy elementy do poszczegolnych kubelkow
                }
                for(int i = 0; i < 11; ++i) {       //wyciagamy spowrotem z kubelkow w dobrej kolejnosci
                    for(Document *o: vectora[i]) {
                        documents[k] = o;
                        k++;
                    }
                }
            } else if(prio[i] == 3) {       //sortowanie po 3 kolumnie
                int k = 0;
                vector<Document*> vectora[1000];    //losowa ilosc kubelkow
                for(int j = 0; j < n; j++) {
                    long long ind = 1000*(documents[j]->code/10000001); //liczymy indeksy dla poszczegolnych dokumentow
                    vectora[ind].push_back(documents[j]);   //wsadzamy dokumenty do odpowiednich kubelkow
                }
                for(int i = 0; i < 1000; ++i) {
                    stable_sort(vectora[i].begin(), vectora[i].end(), [](Document* a, Document* b){return a->code<b->code;});  //stablinie sortujemy kubelki
                    for(Document *o: vectora[i]) {      //wyciagamy w dobrej kolejnosci
                        documents[k] = o;
                        k++;
                    }
                }
            } else if(prio[i] == 4) {       //sortowanie po 4 kolumnie
                for(int l = 3; l >= 0; l--) {   //iteracja po kolumnach
                    int k = 0;
                    vector<Document*> vectora[256];     //kubelki na wartosci
                    vector<Document*> empty;            //kubelki na puste wartosci w kolumnie
                    for(int j = 0; j < n; j++) {
                        if(documents[j]->topics[l] == -1) { //gdy jest pusta wrzucamy do vectora empty
                            empty.push_back(documents[j]);
                        } else {
                        vectora[documents[j]->topics[l]].push_back(documents[j]);   //gdy nie to do odpowiedniego kubelka
                        }
                    }
                    for(Document *o: empty) {   //wyciagamy najpierw puste wartosci
                        documents[k] = o;
                        k++;
                    }
                    for(int i = 0; i < 256; ++i) {  //nastepnie reszte w odpowiedniej kolejnosci
                        for(Document *o: vectora[i]) {
                            documents[k] = o;
                            k++;
                        }
                    }
                }
            }
    }

    cout << result(documents, n) << endl;       //wyswietlamy wynik

    return 0;
}