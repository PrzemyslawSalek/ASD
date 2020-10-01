/*
Treść zadania
W głowie Partycji Logicznej wszystko zaczęło się układać w całość. Wiedza ta jednak była mocno zatrważająca. Według najnowszych obserwacji wkrótce do naszego Układu Słonecznego dotrze niezbyt przyjazna ludzkości asteroida i jedyne czego możemy być pewni to nieuchronna eksterminacja naszego rodzaju. Wszystko wskazywało na to, że władze wiedzą o bardzo poważnej katastrofie, która wkrótce ma się wydarzyć, ale najwyraźniej nie mają zamiaru dzielić się tą informacją ze światem.

Partycja przy okazji swoich ostatnich badań sporządziła listę n nazwisk osób, które mogłyby pomóc jej ujawnić międzynarodowy spisek i przerwać milczenie. Jednak przekonanie każdej z nich będzie wymagać xi minut. Tak się składa że pierwsza z osób, do której uda się Partycja zgodzi się współpracować prawie od razu (po 1 minucie), miło połechatana, że to właśnie ona została poproszona o pomoc na początku. Każda kolejna wymaga zawsze 1 minuty i dodatkowych xi minut przemnożonych przez liczbę osób przekonanych do tej pory. Partycja musi tak dobrać kolejność odwiedzin, by proces werbowania pomocników zajął jej jak najmniej czasu. W przypadku tego samego czasu przekonywania Partycja decyduje się pójść najpierw do osoby z nazwiskiem wcześniejszym leksykograficznie.

Wejście
W pierwszej linii wejścia znajduje się liczba naturalna t, czyli liczba zestawów danych. Każdy zestaw danych składa się z dwóch liczb naturalnych n - liczba nazwisk oraz p - liczba nazwisk, jakie należy wyświetlić na wyjściu. W kolejnych liniach znajdują się opisy osób. Na opis osoby składają się: nazwisko jako jednowyrazowy ciąg znaków oraz liczba naturalna x, oznaczająca liczbę minut potrzebnych standardowo do przekonania tej osoby do współpracy.

1 ≤ t ≤ 10
1 ≤ p ≤ n ≤ 50000
1 ≤ x ≤ 1000
Wyjście
Na wyjściu program dla każdego zestawu danych ma wypisać pierwszych p osób, jakie powinna odwiedzić Partycja oraz minimalny czas w minutach, jaki należy poświęcić na werbowanie pomocników. Wynik powinien być resztą z dzielenia przez 10^6+3.

UWAGA! W zadaniu nie można używać bibliotek STL.

Przykład
Wejście:
3
5 5
Adamczyk 3
Sikora 4
Szewczyk 1 
Pietrzak 1
Mazur 3
6 3
Wisniewski 5 
Wojcik 4 
Wojciechowska 5 
Wozniak 4 
Wrobel 4 
Walczak 5
4 4
Nowak 10 
Malinowski 10 
Duda 10 
Kowalska 10
Wyjście:

Sikora Adamczyk Mazur Pietrzak Szewczyk
21
Walczak Wisniewski Wojciechowska
69
Duda Kowalska Malinowski Nowak
64
*/

#include <iostream>

using namespace std;

struct Person {
    string name;
    int x; //liczba minut
};

//sortowanie przez wstawianie rosnąco
void InsertSort(Person tab [], int n) {
    Person mom;
    int j;
    for(int i=1; i < n; i++)
        if(tab[i].x < tab[i-1].x || (tab[i].x == tab[i-1].x && tab[i].name > tab[i-1].name)) {
            mom.x = tab[i].x;
            mom.name = tab[i].name;
            for(j=i-1; ((j>=0) && (tab[j].x > mom.x)) || ((j>=0) && (tab[j].x == mom.x) && (tab[j].name < mom.name)); j--)
                tab[j+1] = tab[j];
            tab[j+1].x = mom.x;
            tab[j+1].name = mom.name;
    }
}


int main()
{
    ios_base::sync_with_stdio(false);

    int t;      //od 1 do 10
    int n, p;   //liczba nazwisk i liczba nazwisk do wyswietlenia 1<=p<=n<=50000
    int d = 0;  //zmienna
    long long wynik = 0;

    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n >> p;
        Person arr[n];  //tworzenie tablicy
        for(int i = 0; i < n; i++) {
           cin >> arr[i].name >> arr[i].x;  //wczytywanie danych
        }
        InsertSort(arr, n);     //sortowanie
        for(int m = n-1; m >= 0; m--) {
            wynik += (d++*arr[m].x)+1;  //rownanie
            if(m >= n-p)    //wyswietlanie danej ilosci imion
                cout <<  arr[m].name << ' ';
        }
        cout << endl << wynik%1000003 << endl;  //wynik przez modulo
        wynik = 0;
        d = 0;
    }

    return 0;
}