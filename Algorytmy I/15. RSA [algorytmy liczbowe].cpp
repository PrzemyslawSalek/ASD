/*
Treść zadania
W pracy każdego dziennikarza śledczego bardzo ważna jest konspiracja. Szczególnie ważne jest to w przypadku dziennikarza prowadzącego śledztwo w sprawach w które zamieszane są agencje rządowe. Wiadomo, że państwo ma wiele narzędzi, żeby takiego dziennikarza zniszczyć. Władza za pośrednictwem osób trzecich (na przykład żony ministra) może zarządzać niepublikowania tekstów takiego dziennikarza w mediach pod groźbą wycofania reklam spółek skarbu państwa z tych mediów. Może też oczernić go w rządowej telewizji wykorzystując ,,przecieki'' z organów ścigania (na przykład o policyjnej notatce, że dziennikarz w młodości był widywany w stanie nietrzeźwym i co więcej mieszkał w tym samym akademiku co studenci filologii rosyjskiej). W skrajnym przypadku taki dziennikarz może być aresztowany i pod zarzutem przyjęcia korzyści o dużej wartości (na przykład zegarka produkcji japońskiej) w zamian za opublikowanie artykułów wychwalających zalety jednego nadmorskiego kurortu ponad zalety innego kurortu (na podstawie zeznań skruszonego burmistrza pierwszego kurortu).

Aby dochować zasad konspiracja Partycja postanowiła w korespondencji ze swoimi współpracownikami używać szyfru RSA. Partycja nie ufa jednak powszechnie używanym implementacjom tego szyfru gdyż za dobrze pamięta aferę z OpenSSL-em. W związku z tym potrzebuje między innymi programu, który na podstawie liczb pierwszych p i q, których iloczyn jest równy n (wszystkie obliczenia w wykonywane są modulo n) oraz klucza publicznego e wygeneruje klucz prywatny d i rozszyfruje zaszyfrowaną wiadomość c.

Wyjście
Na standardowym wyjściu program otrzyma liczbę zestawów danych t a następnie t zestawów zawierających liczby p, q, e oraz c.

1<=n<4294967296
p,g,e,c< n
Wyjście
Dla każdego zestawu danych wypisz rozszyfrowaną wiadomość.

Przykłady
Wejście
5
2 5 3 3
3 5 9 4
13 17 5 11
19 3 7 55
7 5 11 22
Wyjście
7
4
7
16
8
Uwaga program powinien używać własnych implementacji algorytmów Euklidesa i potęgowania metodą wielokrotnych kwadratów.
*/

#include <iostream>

using namespace std;

static long long x = 1;             //zmienne do Euklidesa//
static long long y = 0;             //zmienne do Euklidesa//

//Algorytm Euklidesa//
void Euklides(long long e, unsigned long long fi) {
    long long value;            //chwilowa wartosc do swapa

    if(!fi) return;             //gdy fi jest rowne 0 
    
    Euklides(fi, e%fi);         //wywolanie rekurencyjne Euklidesa
    
    value = y;                  //zapisujemy do swapa
    y = x - e/fi*y;             //nowa wartosc dla y
    x = value;                  //x to wczesniejszy y
}

//Potęgowanie metodą wielokrotnych kwadratów//
unsigned long long WielokrotneKwadraty(long long c, long long x, unsigned long long n) {
    unsigned long long wynik;                                   //wynik funkcji
    
    if(!x) return 1;                                            //jezeli x jest 0
    if(x%2) return (c * WielokrotneKwadraty(c, x-1, n))%n;      //jezeli liczba jest nieparzysta
    wynik = (WielokrotneKwadraty(c, x/2, n))%n;                 //gdy liczba jest parzysta
    return (wynik * wynik)%n;                                   //zwracamy wynik funkcji
}


int main() {
    ios_base::sync_with_stdio(false);                   //magiczna linijka

    int t = 0;
    cin >> t;                                           //ilosc zestawow

    long long e, c;                                     //klucz publiczyn, zaszyfrowana wiadomosc
    unsigned long long p, q, n, fi, wynik = 0;          //liczby pierwsze p i q

    for(int i = 0; i < t; i++) {
        cin >> p >> q >> e >> c;

        n = p*q;
        fi = (p-1)*(q-1);
        x = 1; y = 0;

        Euklides(e, fi);                                //wywolujemy euklidesa

        if(x < 0) x = fi + x;                           //gdy euklides zwroci wynik mniejszy od 0

        wynik = WielokrotneKwadraty(c, x, n);           //potegujemy klucz przez wynik

        cout << wynik << endl;                          //wyswietlamy wynik

        wynik = 0;
    }

    return 0;
}