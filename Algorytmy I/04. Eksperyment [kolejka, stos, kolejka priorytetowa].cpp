/*
Treść zadania
﻿
Partycja postanowiła włączyć się do pewnej akcji. Grupa jej przyjaciół prowadzi eksperyment nad wydajnością badań grupy naukowców. Obecnie pracują nad nowymi metodami walki z globalnym ociepleniem. Ponieważ katastrofa może nastąpić lada moment trzeba działać szybko. Badacze muszą zostać rozdzieleni na dwie grupy pracujące równolegle. Okazuje się, że właśnie to jest kluczową sprawą dla wydajności. Partycja otrzymała listę naukowców składającą się z imienia, nazwiska oraz punktów zdolności badawczych. Im punktacja jest wyższa tym zdolniejszy jest dany naukowiec. Badacze są jednak niezwykle przywiązani do swoich miejsc. Siedzą przy okrągłym stole zawsze w takiej samej kolejności jaki prezentuje lista. Partycja musi ich podzielić na dwie równe grupy. Należy jednak pamiętać, że różnica między najzdolniejszym oraz najmniej zdolnym naukowcem powinna być jak najmniejsza i absolutnie nie może przekraczać ściśle określonej wartości. Mogłoby to spowodować konflikty w zespole. Ważniejsze są jednak średnie zdolności każdego zespołu która powinny być możliwie najrówniejsze. Zawsze może się zdarzyć sytuacja w której zespół można podzielić na więcej niż jeden sposób dlatego nasza bohaterka musi wykonać swoją pracę zgodnie ze ściśle określoną procedurą. Podzieli stół na dwie równe połowy względem otrzymanej listy. Następnie będzie przesuwała się o jedną osobę zgodnie z kierunkiem ruchu zegara. Pierwsze najlepsze rozwiązanie zostaje uznane za właściwy podział. Co ważne liczba naukowców zawsze jest parzysta. Ponieważ pracę należy wykonywać codziennie bo pracownicy często się zmieniają Partycji przydałby się program który zautomatyzuje pracę.

Wejście:
W pierwszej linii wejścia program otrzymuje liczbę n oznaczającą ilość naukowców oraz v będącą maksymalną różnicą zdolności naukowców w zespole. Następnie w n liniach program otrzymuje dane naukowców zgodnie z ruchem wskazówek zegara, składające się z dwóch ciągu znaków f oraz s będących imieniem i nazwiskiem naukowca oraz liczbę naturalną i oznaczającą zdolność.

Wyjście:
Na wyjściu program powinien wyświetlić dwie listy naukowców oddzielone spacją. Listy powinny być wyświetlone w kierunku zgodnym z kierunkiem wprowadzania. Jeżeli naukowców nie da się podzielić zgodnie z wytycznymi należy wyświetlić słowo „NIE”.

1 ≤ n ≤ 100000

1 ≤ i ≤ 1000

Przykładowe wejście:
6 5
Jan Nowak 12
Wojciech Kowalski 11
Irena Krawiec 1
Marcin Janowski 3
Krystian Król 2
Joanna Malinowska 10
Przykładowe wyjście:
Irena Krawiec
Marcin Janowski
Krystian Król

Joanna Malinowska
Jan Nowak
Wojciech Kowalski
Uwaga:
Rozwiązanie ma wykorzystywać samodzielną implementację kolejki bez wykorzystania bibliotek STL.
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//struktura naukowca//
struct Naukowiec {
    string imie;
    string nazwisko;
    //bez inteligencji bo jej nie wyswietlamy
};

class Kolejka {
    Naukowiec *tab;
     int pierw, ost, roz_tab;
public :
    Kolejka(int n) {
        pierw = ost = 0;
        roz_tab = n;
        tab = new Naukowiec[roz_tab];
    }
    ~Kolejka() {
        delete [] tab;
    }
    bool empty() {
        return pierw == ost;
    }
    Naukowiec front() {
        return tab[pierw];
    }
    void push(string im, string na) {
        tab[ost].imie = im;
        tab[ost].nazwisko = na;
        ost = ost+1;
    }
    void pop() {
        pierw = pierw+1;
    }
    void print(int st1, int k1, int st2, int k2) {
        //wyswietl nie jesli nie ma zadnego wyniku
        if(k1 == 0) {
            cout << "NIE" << endl;
        //w innym wypadku wyswietl kolejke od indeksu do indeksu
        } else {
        for(int i = st1; i <= k1 ; i++) {
            cout << tab[i].imie << " " << tab[i].nazwisko << endl;
        }
        cout << endl;
        if(k2 > st2) {
            for(int i = st2; i <= k2; i++) {
                cout << tab[i].imie << " " << tab[i].nazwisko << endl;
            }
        }
        else {
        for(int i = st2; i < roz_tab; i++) {
            cout << tab[i].imie << " " << tab[i].nazwisko << endl;
        }
        for(int i = 0; i < k2; i++)
            cout << tab[i].imie << " " << tab[i].nazwisko << endl;
        }
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    
    int n;  //ilosc naukowcow
    int v;  //maksymalna roznica umiejetnosci

    string f;       //imie
    string s;       //nazwisko
    int i;          //zdolnosci

    cin >> n >> v;

    Kolejka kolejka1(n);       //kolejka
    int *tab = new int[n];      //tablica na inteligencje
    int counter1[1001] = {0};   //licznik punktow inteligencji do max i min
    int counter2[1001] = {0};   //drugi licznik
    
    //indeksy startowe//
    int start1 = 0;
    int start2 = n/2;
    int koniec1 = (n/2)-1;
    int koniec2 = n-1;

    //min i max startowy dla 1 kolejki//
    int min1 = 1001;
    int max1 = 0;

    //dla drugiej kolejki//
    int min2 = 1001;
    int max2 = 0;

    //suma dla 1 i 2 kolejki
    int suma1 = 0;
    int suma2 = 0;

    //srednia dla 1 i 2 kolejki
    double avg1;
    double avg2;

    //pobieranie pierwszej kolejki//
    for(int k = 0; k < n/2; ++k) {
        cin >> f >> s >> i;
        kolejka1.push(f,s);
        tab[k] = i;
        counter1[i]++;
        if(i < min1) min1 = i;
        if(i > max1) max1 = i;
        suma1 += i;
    }
    
    //pobieranie drugiej kolejki//
    for(int k = n/2; k < n; ++k) {
        cin >> f >> s >> i;
        kolejka1.push(f,s);
        tab[k] = i;
        counter2[i]++;
        if(i < min2) min2 = i;
        if(i > max2) max2 = i;
        suma2 += i;
    }

    //obliczamy pierwsza srednia//
    avg1 = suma1*1.0/(n/2);
    avg2 = suma2*1.0/(n/2);

    //najlepsza srednia i indeksy na start//
    double bavg = 10000;
    int nstart1 = 0;
    int nstart2 = 0;
    int nkoniec1 = 0;
    int nkoniec2 = 0;

    //gdyby pierwszy przypadek byl dobry...//
    if(max1-min1 <= v && max2-min2 <= v) {
        if(abs(avg1 - avg2) < bavg) {
            bavg = abs(avg1 - avg2);
            nstart1 = start1;
            nstart2 = start2;
            nkoniec1 = koniec1;
            nkoniec2 = koniec2;
        }
    }


    //zmieniamy indeks na 0 dla latwiejszej iteracji//
    koniec2 = 0;
    //glowna petla//
    while(start2 < n-1) {
        suma1 -= tab[start1];    //suma, odejmujemy element "usuwany"
        counter1[tab[start1]]--;        //licznik odejmujemy bo "usuwamy" element
        counter1[tab[koniec1+1]]++;     //dodajemy ...
        //pierwsza kolejka//
        if(max1 < tab[koniec1+1]) {     //gdy nowy element jest naszym nowym max
            max1 = tab[koniec1+1];
        }
        else if(max1 == tab[start1] && counter1[max1] == 0) {   //kiedy juz nie mamy wiecej naszego maksa i usuniemy go
            max1 = tab[start1+1];
            for(int i = start1+2; i <= koniec1+1; i++) {
                if(tab[i] > max1) max1 = tab[i];
            }
        }
        if(min1 > tab[koniec1+1]) {
            min1 = tab[koniec1+1];
        } else if(min1 == tab[start1] && counter1[min1] == 0) {
            min1 = tab[start1+1];
            for(int i = start1+2; i <= koniec1+1; i++) {
                if(tab[i] < min1) min1 = tab[i];
            }
        }
        start1++; koniec1++;        //indeksy przesuwamy
        suma1 += tab[koniec1];     //dodajemy nowy element

        //druga kolejka//           //analogicznie do pierwszej uwzgledniajac przesuniecie konca przed glowna petla
        suma2 -= tab[start2];
        counter2[tab[start2]]--;
        counter2[tab[koniec2]]++;
        if(max2 < tab[koniec2]) {
            max2 = tab[koniec2];
        } else if(max2 == tab[start2] && counter2[max2] == 0) {
            max2 = tab[start2+1];
            for(int i = start2+2; i < n; i++) {
                if(tab[i] > max2) max2 = tab[i];
            }
            for(int j = 0; j <= koniec2; j++)
                if(tab[j] > max2) max2 = tab[j];
        }
        if(min1 > tab[koniec2]) {
            min1 = tab[koniec2];
        } else if(min2 == tab[start2] && counter2[min2] == 0) {
            min2 = tab[start2+1];
            for(int i = start2+2; i < n; i++) {
                if(tab[i] < min2) min2 = tab[i];
            }
            for(int j = 0; j <= koniec2; j++)
                if(tab[j] < min2) min2 = tab[j];
        }
         suma2 += tab[koniec2];
         start2++; koniec2++;

         //sprawdzamy warunki naszego zadania//
        if(max1-min1 <= v && max2-min2 <= v) {
            avg1 = suma1*1.0/(n/2); avg2 = suma2*1.0/(n/2);
            if(abs(avg1 - avg2) < bavg) {
                bavg = abs(avg1 - avg2);
                nstart1 = start1;
                nstart2 = start2;
                nkoniec1 = koniec1;
                nkoniec2 = koniec2;
            }
        }
    }

    //wyswietlanie najlepiej dopasowanej kolejki//
    kolejka1.print(nstart1, nkoniec1, nstart2, nkoniec2);

    return 0;
}