/*
Treść zadania
Jak wiadomo w Lublinie często odbywają się spotkania kulinarne, degustacyjne i różne festiwale smaku. Jedna z koleżanek Partycji (z grupy społecznej, której nie wykluczyła:) ) zajmuje się organizacją festiwalu degustacji tradycyjnych polskich potraw. Chciałaby, aby to wydarzenie było jednym z najlepszych. Zależy jej na tym, aby każdy zjadł to, na co ma ochotę.

W związku z tym Jagoda, bo tak ma na imię koleżanka naszej bohaterki, poprosiła wszystkich zaproszonych na festiwal o wypełnienie ankiety. Ankieta polega na tym, że każdy uczestnik wydarzenia musi wybrać potrawy, które chciałby skosztować. Oczywiście taka osoba może zaznaczyć dowolną ilość potraw z listy, które chętnie by zjadła. Uczestnik może zaznaczyć wszystkie potrawy, ale równie dobrze może nie zaznaczyć żadnej - wtedy wiemy, że nie będzie on zadowolony. Ponieważ są to bardzo ekskluzywne potrawy i kunsztowne, ekskluzywne wydarzenie na każdego uczestnika przypada tylko jedna degustacja. Niestety dobranie odpowiednich posiłków dla każdego z gości, jest ogromnym wyzwaniem organizacyjnym. Wynika to przede wszystkim z tego, że każdej potrawy zostanie przygotowana taka sama, ograniczona ilość. Dodatkowo Jagoda chce aby, jak najwięcej osób wyszło z wydarzenia zadowolonych. To zadowolenie gwarantuje jedynie to, że przybysze zjedzą potrawę, która była na ich liście życzeń.

WEJŚCIE
W pierwszej linii wejścia znajdują się liczby naturalne n m l, n - to liczba uczestników wydarzenia, m - to ilość dostępnych potraw, zaś l - to ilość zestawów degustacyjnych każdej z potraw. Następnie program powinien wczytać wyniki ankiety, które są podane w macierzy o wymiarach n x m. Gdy uczestnik chce spróbować potrawy wprowadził ‘x’, a w przeciwnym wypadku ‘o’.

0 <= n, m, l <= 2000000000

WYJŚCIE
Na wyjściu algorytm powinien wypisać jedną liczbę całkowitą, która jest największą możliwą liczbą osób zadowolonych z uczestnictwa w wydarzeniu.

PRZYKŁADOWE DANE WEJŚCIOWE
6 3 2
o o x
x x x
o o x
x o o
x o x
x o o
PRZYKŁADOWE DANE WYJŚCIOWE
5
UWAGI
Rozwiązane zadania powinno być implementacją metody wyszukiwania maksymalnego skojarzenia w grafie dwudzielnym.
*/

#include <iostream>

using namespace std;

//funkcja szukająca połączenia miedzy osobą a daniem//
bool search_path(int **matrix, int n, int m, int l, int *visited, int **linked, int *size, int step){
    for(int i = 0; i < m; i++) {                        //pętla po wszystkich daniach
        if(matrix[step][i] == 1 && visited[i] > 0) {    //sprawdzamy czy osoba jest zainteresowana danym daniem i czy już nie sprawdzalismy tego dania
            visited[i]--;                               //odejmujemy licznik visited (visited rowne ilosci zestawów dania)
            if(linked[i][size[i]] < 0) {                //jeżeli mamy dostępny jakiś zestaw tego dania
                linked[i][size[i]] = step;              //to przypisujemy daniu osobe
                size[i]++;                              //zwiekszamy licznik zajetych zestawow danego dania
                return true;                            //zwracamy prawde poniewaz znalezlismy polaczenie
            }
            for(int j = 0; j < l; j++) {                //jezeli nie mamy dostepnego zestawu
                if(search_path(matrix, n, m, l, visited, linked, size, linked[i][j])) {     //to wywolujemy rekurencje na elemencie ktory zaja juz danie
                    linked[i][j] = step;                //jezeli rekurencja zwrocila prawde to tamta osoba ma juz inne danie
                    return true;                        //a naszej mozemy przypisac aktualne danie i zwrocic prawde
                }
            }
        }
    }
    return false;       //jezeli nie znajdziemy dania dla naszej osoby to zwracamy fałsz
}

int main() {
    ios_base::sync_with_stdio(false);               //magiczna linijka

    int n, m, l;                                    //n - liczba uczestnikow, m - ilosc potraw, l - ilosc zestawow
    cin >> n >> m >> l;                             //wczytujemy dane

    int** matrix = new int*[n];                     //tworzymy macierz grafu dwudzielnego
    for(int i = 0; i < n; i++) {
        matrix[i] = new int[m];                     
    }

    char curr;                                      //zmienna na 'x' i 'o'

    for(int i = 0; i < n; i++) {                    //wczytujemy osoby
        for(int j = 0; j < m; j++) {                //i ich preferencje
            cin >> curr;                            //'x' lub 'o'
            if(curr == 'x') matrix[i][j] = 1;       //jezeli 'x' to wstawiamy 1
            else matrix[i][j] = 0;                  //jezeli 'o' to wstawiamy 0
        }
    }
    
    int** linked = new int*[m];                     //tablica skojarzen zestawów dań 
    for(int i = 0; i < m; i++) {                    //inicujemy ją
        linked[i] = new int[l];
        for(int j = 0; j < l; j++)
            linked[i][j] = -1;                      //wypełniamy -1
    }   

    int sum = 0;                                    //nasz wynik
    int *visited = new int[m];                      //tablica odwiedzonych dan

    int *size = new int[m];                         //tablica indeksu najmniejszego dostepnego zestawu
    for(int i = 0; i < m; i++) {    
        size[i] = 0;                                //wypelniamy ja 0
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            visited[j] = l;                         //visited wypelniamy iloscia zestawow
        }
        if(search_path(matrix, n, m, l, visited, linked, size, i)) //wywolujemy funkcja szukania dla kazdej osoby
            sum++;                                  //jezeli zwroci true to zwiekszamy wynik
    }

    cout << sum << endl;                            //wyswietlamy wynik funkcji glownej

    return 0;
}