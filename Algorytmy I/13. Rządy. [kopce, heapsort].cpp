/*
Treść zadania
Partycja ostatnio zastanawia się, które rządy wiedzą o zbliżającej się katastrofie. Postanowiła na podstawie zdobytych informacji zrobić zestawienie mające wytypować, które państwa wiedzą, a które nie wiedzą o katastrofie. Każdemu państwu przypisywany jest współczynnik będący liczbą całkowitą z zakresu od 0 do 1000000 mówiący o tym jak bardzo pewne jest, że rząd danego państwa wie o czekającej ziemię katastrofie. Partycja wraz ze współpracownikami z całego świata aktualizuje współczynniki przypisane poszczególnym państwom po uzyskaniu nowych informacji. Na przykład fakt, że jakiś rząd blokuje porozumienie klimatyczne albo składa nierealne obietnice socjalne jest dla niej argumentem za tym, że ten rząd wie iż od września 2020 roku żadne obietnice nie będą miały znaczenia (pojawienie się tego typu informacji powoduje zwiększenie współczynnika przypisanego danemu państwu). Z kolei jeżeli jakiś rząd prowadzi odpowiedzialną politykę, wprowadza oszczędności budżetowe itp. jest to dla Partycji poszlaką świadczącą o tym, że dany rząd nie wie nic o zbliżającej się katastrofie (co zmniejsza wartość współczynnika przypisanego danemu państwu).

Partycja uruchomiła działający w Darknecie serwer umożliwiający wolontariuszom z całego świata aktualizację współczynników na podstawie zdobytych przez nich dokumentów. Wraz ze wzrostem liczby wolontariuszy stary serwer zaczął się ,,zapychać''. Partycja postanowiła oszacować potrzeby przed zakupem nowego. W tym celu zaczęła zliczać operacje wykonywane na serwerze. Ponieważ lista państw jest przechowywana w kopcu binarnym posortowanym względem rozważanego współczynnika to Partycja postanowiła zliczać liczbę zamian ojca z synem w trakcie przesiewania w kopcu. Kopiec jest zaimplementowany w taki sposób, że w trakcie przesiewania w dół, w przypadku gdy obaj synowie przesiewanego wierzchołka mają równą wartość współczynnika, wierzchołek zamieniany jest z tym z synów, który znajduje się w komórce tablicy o mniejszym indeksie. Ze względów konspiracyjnych państwom przypisano liczby z przedziału od 0 do 1000, które są używane zamiast ich nazw.

Wejście
Na wejściu program otrzymuje liczbę n rozważanych państw a następnie n opisów państw w kolejności w jakiej odpowiadające tym państwom węzły znajdują się w tablicy przechowującej kopiec. Opisy poszczególnych państw składają się z par p, w liczb oznaczających kolejno numer przypisany do państwa oraz jego współczynnik. Następnie program otrzyma liczbę m oraz m opisów zmian rozważanego współczynnika. Każdy opis składa się z pary p, w oznaczającej, że współczynnik państwa p otrzymuje nową wartość w.

1<=n<=1000
1<=m<=2000000
Wyjście
Na standardowym wyjściu program powinien wypisać liczbę zamian wykonanych w trakcie przesiewania elementów kopca.

Przykłady
Wejście
4
48 1000
1 999
7 999
44 997
3
48 996
1 1001
7 995
Wyjście
2
Wejście
4
48 1000
1 999
7 999
44 997
2
7 995
48 1001
Wyjście
0
Wejście
4
48 1000
1 999
7 999
44 997
3
48 998
44 1000
1 1001
Wyjście
4
*/

#include <iostream>

using namespace std;

struct Panstwo{
    int num;                    //od 0 do 1000
    long long wspolczynnik;     //od 0 do 1000000
};

class Kopiec{
    int size;                       //rozmiar tablicy panstw
    short currSize = 0;             //aktualny rozmiar
    Panstwo **panstwa;              //tablica wskaznikow na panstwa
    short indx[1001];               //tablica indeksow panstw aby nie wyszkiwac przy zmianie
    unsigned long long sum = 0;     //wynik koncowy
public:

    Kopiec(int size) {                   //konstruktor kopca
        this->size = size;               //zapisujemy rozmiar
        panstwa = new Panstwo*[size];    //tworzymy tablice na panstwa

    }

    void insert(int num, long long value) {         //funkcja dodajaca nowe panstwa
        Panstwo *p1 = new Panstwo;                  //chwilowy wskaznik panstwa
        p1->num = num; p1->wspolczynnik = value;    //ustawiamy mu wartosci
        indx[num] = currSize;                       //zapisujemy indeks w tablicy
        panstwa[currSize] = p1;                     //dodajemy panstwo do tablicy
        currSize++;                                 //indeks dla kolejnego elementu
    }

    void print() {                          //funkcja wyswietlajaca tablice
        for(int i = 0; i < size; i++) {
            cout << panstwa[i]->num << " " << panstwa[i]->wspolczynnik << endl;
        }
    }

    void change(int num, long long value) {         //funkcja zamieniajaca wartosc panstwa
        Panstwo *p2 = new Panstwo;                  //tymczasowy wskaznik panstwa
        p2->num = num; p2->wspolczynnik = value;    //nadajemy mu wartosci
        int currI = indx[num];                      //zapisujemy sobie jego wskaznik (zaczynamy od niego petle)
        panstwa[currI] = p2;                        //zamieniamy wspolczynnik panstwa

        while(currI < size) {                                                                                               //przesiewanie w gore
            if(currI != 0 && (currI-1)/2 >= 0 && panstwa[(currI-1)/2]->wspolczynnik < panstwa[currI]->wspolczynnik) {       //sprawdzamy czy nie jestesmy na pierwszy miejscu && czy nie wyjdziemy za tablice && czy element wyzej jest mniejszy
                swap(panstwa[(currI-1)/2],panstwa[currI]);                                                                  //jezeli tak to zamieniamy wartosci
                swap(indx[panstwa[(currI-1)/2]->num],indx[panstwa[currI]->num]);                                            //zamieniamy indeksy
                currI = (currI-1)/2;                                                                                        //zmieniamy aktualna pozycje
                sum++;                                                                                                      //zwiekszamy wynik o 1
             } else break;                                                                                                  //jezeli nie to koniec petli
        }

        while(currI < size) {                                                                   //przesiewanie w dol
            if(2*currI+1 < size && 2*currI+2 < size &&  panstwa[2*currI+1]->wspolczynnik >= panstwa[2*currI+2]->wspolczynnik &&  panstwa[currI]->wspolczynnik < panstwa[2*currI+1]->wspolczynnik) {     //czy miescimy sie w tablicy && czy element z lewej jest wiekszy lub rowny && czy jest nasz mniejszy od kolejnego
                swap(panstwa[2*currI+1],panstwa[currI]);                                        //zamieniamy panstwa miejscami
                swap(indx[panstwa[2*currI+1]->num],indx[panstwa[currI]->num]);                  //zamieniamy indeksy
                currI = 2*currI+1;                                                              //zmieniamy aktualna pozycje
                sum++;                                                                          //zwiekszamy wynik o 1
            } else if(2*currI+1 < size && 2*currI+2 < size &&  panstwa[2*currI+1]->wspolczynnik < panstwa[2*currI+2]->wspolczynnik &&  panstwa[currI]->wspolczynnik < panstwa[2*currI+2]->wspolczynnik) { //czy miescimy sie w tablicy && czy element z prawej jest wiekszy && czy nasz jest mniejszy od kolejnego
                swap(panstwa[2*currI+2],panstwa[currI]);                                        //zamieniamy panstwa miejscami
                swap(indx[panstwa[2*currI+2]->num],indx[panstwa[currI]->num]);                  //zamieniamy indeksy
                currI = 2*currI+2;                                                              //zmieniamy aktualna pozycje
                sum++;                                                                          //zwiekszamy wynik o 1
            } else if(2*currI+1 < size && panstwa[currI]->wspolczynnik < panstwa[2*currI+1]->wspolczynnik) {    //czy miescimy sie w tablicy && czy naszj jest mniejszy od nastepnego 1 brata
                swap(panstwa[2*currI+1],panstwa[currI]);
                swap(indx[panstwa[2*currI+1]->num],indx[panstwa[currI]->num]);
                currI = 2*currI+1;
                sum++;
            } else break;           //jezeli nic z tego to wychodzimy
        }


    }

    unsigned long long suma() {         //funkcja zwracajaca wynik
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);           //magiczna linijka

    int n;
    cin >> n;                                   //1<=n<=1000

    Kopiec kopiec(n);                           //tworzymy kopiec
    int mainNum; long long mainWspol;           //tymczasowe zmienne na numer i wspolczynnik panstwa

    for(int i = 0; i < n; ++i) {                //pobieramy kolejne panstwa podane w odpowiedniej kolejnosci
        cin >> mainNum >> mainWspol;
        kopiec.insert(mainNum, mainWspol);      //dodajemy do naszego kopca
    }

    //kopiec.print();

    int m;
    cin >> m;                                   //ilosc opisow zmian wspolczynnika danego panstwa 1<=m<=2000000

    for(int i = 0; i < m; ++i) {                //pobieramy zmiany
        cin >> mainNum >> mainWspol;
        kopiec.change(mainNum, mainWspol);      //zmieniamy w kopcu
    }

    cout << kopiec.suma() << endl;              //wyswietlamy wynik


    return 0;
}