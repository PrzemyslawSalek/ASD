/*
Treść zadania
Problemy z przekazaniem dokumentów od eksperta sprawiły, że Partycja postanowiła obsadzić stacje kolejowe współpracującymi z nią wolontariuszami w taki sposób, żeby każdy pociąg musiał przejeżdżać przez co najmniej jedną stację, na której wolontariusz mógłby odebrać dokumenty od kuriera. Oznacza to, że na co najmniej jednym końcu każdego odcina torów łączącego dwie stacje musi być wolontariusz. Oczywiście do obsadzenia wszystkich końców znajdujących się na jednej stacji wystarczy jeden wolontariusz. Niestety liczba wolontariuszy współpracujących z Partycją jest mocno ograniczona. Partycja zastanawia się czy ich liczba jest wystarczająca do obsadzenia końców wszystkich odcinków linii kolejowych.

Wejście:
Pierwsza linia wejścia zawiera liczbę całkowitą t - liczbę zestawów danych, których opisy występują kolejno po sobie. W pierwszej linii zestawu danych podane są trzy liczby naturalne n, m i r - odpowiednio liczba stacji kolejowych , liczba odcinków kolejowych bezpośrednio łączących ze sobą dwie stacje kolejowe oraz liczba wolontariuszy. Każda z kolejnych m linii zawiera dwie liczby naturalne a i b - numery stacji kolejowych połączonych bezpośrednim odcinkiem torów.

1 ≤ t ≤ 150
1 ≤ n ≤ 30
1 ≤ m ≤ 100
1 ≤ r ≤ 20
1 ≤ a, b ≤ n
Wyjście:
Dla każdego zestawu danych program powinien wypisać jedną linię zawierającą napis

TAK
, jeśli liczba wolontariuszy jest wystarczająca albo
NIE
w przeciwnym przypadku.
Przykładowe wejście:
3
2 1 1
1 2
4 6 2
1 2
1 3
1 4
2 3
2 4
3 4
6 1 1
4 5

Przykładowe wyjście:
TAK
NIE
TAK
Zadanie należy rozwiązać za pomocą przeszukiwania z nawrotami.
*/

#include <iostream>
#include <utility>      //biblioteka dla pary

using namespace std;
                                                                            //stacja - tablica stacji, odcinek - tablica par odcinkow
bool jazda(int *stacja, pair<int, int> *odcinek, int r, int m, int k) {     //r - liczba wolontariuszy, m - liczba odcinkow, k - poziom rekurencji
    if(stacja[odcinek[k].first] == 0 && stacja[odcinek[k].second] == 0) {   //jezeli nie bedzie ustawiony na zadnej stacji z pary
        if(r > 0) r--;                                                      //czy mamy dostepnych wolontariuszy
        else return false;                                                  //nie mamy wiec rzucamy false
        if(k==m-1) return true;                                             //sprawdzamy czy nie jest to ostatni poziom rekurencji
        stacja[odcinek[k].first] = 1;                                       //ustawiamy wolontariusza na pierwszej stacji z paty 
        if(jazda(stacja, odcinek, r, m, k+1)) return true;                  //sprawdzamy czy rekurencja wykonała się poprawnie
        
        stacja[odcinek[k].first] = 0;                                       //zabieramy wolontariusza z pierwszej stacji
        stacja[odcinek[k].second] = 1;                                      //i ustawiamy go na drugiej stacji
        if(jazda(stacja, odcinek, r, m, k+1)) return true;                  //sprawdzamy czy rekurencja wykonała się poprawnie
        
        stacja[odcinek[k].first] = 0;                                       //zabieramy wolontariusza z obu stacji
        stacja[odcinek[k].second] = 0;                                      //aby ustawic go w poprzednim poziomie rekurencji na innym miejscu
    } else {                                                                //gdy bedzie ustawiony na jakiejs stacji z pary
        if(k==m-1) return true;                                             //sprawdzamy czy nie mamy ostatniego poziomu rekurencji
        if(jazda(stacja, odcinek, r, m, k+1)) return true;                  //sprawdzamy czy rekurencja wykonała się poprawnie
    }
    return false;                                                           //jezeli przejrzymy wszystko i nie znajdziemy rozwiazania
}

int main() {
    ios_base::sync_with_stdio(false);                                       //magiczna linijka

    int t;                                                                  //iczba zestawow danych 1 <= t <= 150
    cin >> t;                                                               //pobieramy liczbe zestawow

    int n, m, r;                                                            //liczba stacji kolejowych, liczba odcinków kolejowych, liczba wolontariuszy
    int a, b;                                                               //wartosci pary

    for(int i = 0; i < t; ++i) {                                            //wczytujemy zestawy t razy
        cin >> n >> m >> r;

        int stacja[n];                                                      //tworzymy tablice dla stacji o wilekosci n
        for(int k = 0; k < n; ++k) stacja[k] = 0;                           //zerujemy ją

        pair<int, int> odcinek[m];                                          //tworzymy tablice par dla odcinkow kolejowych miedzy stacjami
        for(int j = 0; j < m; ++j) {                                        //wczytujemy do niej wartosci
            cin >> a >> b;
            odcinek[j] = make_pair(a-1,b-1);                                //indeksuje stacje od 0 dlatego -1
        }

        if(jazda(stacja, odcinek, r, m, 0)) cout << "TAK" << endl;          //wyswietlam TAK gdy funkcja zwroci TRUE
        else cout << "NIE" << endl;                                         //w przeciwnym wypadku wyswietlam NIE
    }
    
    return 0;
}