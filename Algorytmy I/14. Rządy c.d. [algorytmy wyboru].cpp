/*
Treść zadania
Partycja od kilku tygodni nie robi nic innego tylko porządkuje, sortuje itp. Powoli zaczyna mieć tego dość. Dobrze, że chociaż analiza planów różnych rządów bywa zabawna (choć to słowo wydaje się być nie do końca na miejscu w obecnej sytuacji), gdy pamięta się, że świat jaki znamy skończy się we wrześniu 2020. Partycja zapisuje co lepsze przykłady działań rządów. Przykładowo niedawno jeden z rządów zaproponował swoim obywatelom wykup stuletnich nieoprocentowanych obligacji. W zamian posiadacze obligacji mieliby brać udział w losowaniach cennych nagród. Pierwsze losowanie w październiku 2020 - dopowiedziała w myślach Partycja. Także dopiero teraz dotarło do Partycji dlaczego przyznano Katarowi mistrzostwa świata w piłce nożnej, które mają się odbyć w 2022 roku. Równie dobrze można by je zorganizować na Antarktydzie - pomyślała Partycja.

Znudzona porządkowaniem dokumentów Partycja postanowiła poprosić znajomego informatyka o dodanie do serwisu monitorującego działalność rządów poszczególnych krajów jeszcze jednej funkcjonalności. Chodzi o wyszukiwanie dla podanego k państwa o k-tej wartości współczynnika określającego stopień pewności, że rząd danego państwa wie o nadchodzącej katastrofie.

Wejście
Na wejściu program otrzymuje liczbę n rozważanych państw a następnie n opisów państw w losowej kolejności. Opisy poszczególnych państw składają się z par p, w liczb oznaczających kolejno numer przypisany do państwa oraz jego współczynnik (numer państwa jest unikalną liczbą z zakresu od 0 do 10000000). Następnie program otrzyma liczbę m oraz m zapytań. Każde zapytanie składa się z liczby z zakresu od 1 do n.

1<=n<=500000
1<=m<=200
Wyjście
Na standardowym wyjściu program powinien wypisać odpowiedzi dla wszystkich zapytań. Dla zapytania k powinien wypisać numer kraju o k-tej wartości badanego współczynnika. Zakładamy, że przy takich samych wartościach współczynnika wypisywany jest najmniejszy spośród numerów państw o tym współczynniku.

Przykłady
Wejście
4
7 999
48 1000
1 999
44 997
4
1
2
3
4
Wyjście
44
1
1
48
Wejście
4
48 1000
1 1000 
7 1000
44 1000
3
4
1
2
Wyjście
1
1
1
Wejście
1
48 1000
1
1
Wyjście
48
Uwaga program powinien działać w oczekiwanym czasie liniowym.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//struktura panstwo//
struct Panstwo {
    int p;          //numer panstwa
    int w;          //wspolczynnik panstwa
};


//algorytm wyboru Hoare'a//   //przedzial A - (elementy mniejsze od b) B - (rowne b) C - (wieksze od b)
int Hoare(Panstwo *panstwa, int start, int end, int m) {   //przyjmuje tablice panstw, pierwszy i ostatni indeks oraz pozycje szukanego elementu
    
    //start to iterator po tablicy            
    //old_start to poczatek przedzialu A      //equal_start to koniec przedzialu A/poczatek B
    //end to koniec przedzialu B/poczatek C   //old_end to koniec przedzialu C
    
    int old_start = start;                                  //zapisujemy pierwszy indeks aby wiedziec gdzie zaczyna sie fragment naszej tablicy             
    int old_end = end;                                      //zapisujemy ostatni indeks aby wiedziec gdzie konczy sie fragment naszej tablicy  
    
    int equal_start = start;                                //nasza zmienna pokazujaca gdzie zaczyna sie fragment z rownymi elementami

    int indx = rand()%(end-start+1)+start;                  //losujemy indeks elementu wedlug ktorego bedziemy dzielic tablice
    
    int value = panstwa[indx].w;                            //zapiusjemy sobie jego wartosc
    int min_p = panstwa[indx].p;                            //oraz numer aby sprawdzac czy nie ma elementu o takim samym w i mniejszym numerze

    while(start <= end) {                                   //dopoki wskaznik ktory idzie od poczatku nie spotka tego co idzie od konca
        if(panstwa[start].w > value) {                      //jezeli sprawdzana wartosc jest wieksza od naszego elementu
            swap(panstwa[start], panstwa[end]);             //to wyrzucamy ja na koniec (do czesci z elementami wiekszymi od B)
            end--;                                          //przesuwamy wskaznik ktory ma nam pokazywac koniec przedcialu B (rownych)
        } else if(panstwa[start].w < value) {               //jezeli sprawdzana wartosc jest mniejsza od naszego elementu
            swap(panstwa[start], panstwa[equal_start]);     //to wyrzucamy ja przed przedzial B do wartosci mniejszych od B 
            start++;                                        //przesuwamy wskaznik ktory porusza sie po calej tablicy
            equal_start++;                                  //przesuwamy nasz wskaznik pokazujacy gdzie zaczyna sie przedzial B
        } else {                                            //gdy elementy sa rowne
            if(min_p > panstwa[start].p)                    //sprawdzamy czy numer panstwa jest mniejszy od naszego min_p
                min_p = panstwa[start].p;                   //jezeli tak to mamy nowe min_p
            start++;                                        //przesuwamy nasz wskaznik/iterator
        }
    }

    int p = 0;
    
    if(m-1 < equal_start)                                   //sprawdzamy czy szukana wartosc jest w przedziale A
        p = Hoare(panstwa, old_start, equal_start-1, m);    //jezeli tak to wywolujemy rekurencje na tym przedziale
    else if(m-1 > end)                                      //sprawdzamy czy nalezy do przedzialu C
        p = Hoare(panstwa, start, old_end, m);              //jezeli tak to wywolujemy rekurencje na tym przedziale
    else if(m-1 >= equal_start && m-1 <= end)              //sprawdzamy czy nalezy do przedzialu B
        p = min_p;                                          //jezeli tak to przypisujemy do wartosci nasze min_p
    
    return p;                                               //zwracamy wynik
}


int main() {
    ios_base::sync_with_stdio(false);                       //magiczna linijka

    int n;
    cin >> n;

    Panstwo panstwa[n];                                     //tablica panstw

    for(int i = 0; i < n; ++ i) {                           //pobieramy panstwa
        Panstwo p1;
        cin >> p1.p >> p1.w;
        panstwa[i] = p1;
    }

    int m, currM;                                           //liczba zapytan, zapytanie
    cin >> m;                                               //pobieramy ilosc zapytan

    srand(time(NULL));                                      //ziarno do losowania wartosci

    for(int i =  0; i < m; ++i) {                           //pobieramy dana ilosc zapytan
       cin >> currM;
       cout << Hoare(panstwa, 0, n-1, currM) <<  endl;      //wywolujemy funkcje i wyswietlamy wynik      
    }

    return 0;
}