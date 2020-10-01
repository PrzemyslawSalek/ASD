/*
Treść zadania
﻿
Partycja odkryła straszną prawdę. Światem od wieków rządzą tajne organizacje. Nasza bohaterka uwielbia demaskować ich tajemnice. Podobno na odwrocie deklaracji podległości spisanej przez samych ojców stworzycieli jest zapisany szyfr. Dotarcie do niego zajęło naszej bohaterce nieco czasu. Wykorzystując znajomości udało się jej otrzymać tajną fotografię dokumentu od konserwatorki. Oczom Partycji ukazał się jednak dziwny zestaw słów oraz cyfr. Postanowiła, że ze swoim problemem uda się do znanego historyka specjalizującego się w starych szyfrach. Specjalista przyjrzał się dokumentowi i rzekł:

- Widziałem już kiedyś taki szyfr. Używały go tajne organizacje wiele lat temu. Jak widzisz mamy dwa zestawy słów. Pierwszy składa się z par zbudowanych z jednego słowa oraz liczby. Dla ułatwienia liczbę z pary będziemy nazywać wartością słowa. Poruszamy się po liście słów przechodząc od jednego do następnego, dodając je do zdania wynikowego. Wartość w parze oznacza o ile słów od obecnego należy się przesunąć. Jeżeli jest ona dodatnia poruszamy się zgodnie z kierunkiem wprowadzania. Gdyby jednak wartość była ujemna poruszamy się w kierunku przeciwnym. Jeżeli dotrzesz do końca listy przeglądanie rozpoczynasz z drugiej strony. Pamiętaj jednak, że każde słowo może być użyte tylko raz. Przeglądanie powinno zostać rozpoczęte od ustalonego numerem słowa.

- Więc do czego jest ta druga lista słów?

- Jeżeli podczas przeglądania pierwszej listy trafisz na słowo którego wartość jest równa 0 to zamiast dodawać ją do wynikowego zdania należy dodać nowe słowo do listy jako poprzednik obecnie znalezionego zgodnie z kierunkiem wprowadzania. Pobiera się je właśnie z tej drugiej listy. Ponieważ nie zostało jeszcze wykorzystane nie powinno być usuwane. Musisz pamiętać, żeby zmodyfikować wartość znalezionego słowa. Jak widzisz lista słów oczekujących na dodanie oprócz pary ma dodatkową liczbę. To wartość która zastąpi znalezione 0. Na koniec wyszukujesz nowe słowo przemieszczając się właśnie o tą zmodyfikowaną wartość. Możesz być pewna, że ilość słów dodatkowych zawsze jest wystarczająca. Ba, zwykle jest ich nawet za dużo. Wyszukiwanie kończy się kiedy skończą się elementy w pierwszej liście.

Partycja miała już plan. Zostało zatem tylko odczytać szyfr …

Wejście:
Na wejściu program otrzymuje liczbę n oznaczającą rozmiar listy słów oraz s będącą numerem słowa startowego. Następnie w n liniach program otrzymuje parę składającą się z pojedynczego słowa s oraz liczby x. W kolejnym kroku podawana jest liczba p, która określa ilość słów oczekuje na dodanie. Następnie w p liniach program otrzymuję listę oczekujących par s oraz x oraz y, gdzie ostatnia wartość jest liczbą zastępującą 0 które spowodowało dodanie nowego elementu.

Wyjście:
Na wyjściu program powinien wypisać odtworzone zdanie. Działanie kończy się kiedy cała lista zostanie opróżniona.

1 ≤ n ≤ 30000
0 ≤ p ≤ 30000
-1000000 ≤ x, d ≤ 1000000
Przykładowe wejście:
7 5
spadaniem 5
czestym 0
kamien 7
drazy -2
sila 2
Kropla -2
nie -1
3
lecz 1 -5
tak 8 2
syzbko -9 6
Przykładowe wyjście:
Kropla drazy kamien nie sila lecz czestym spadaniem
Uwaga:
Rozwiązanie ma być samodzielną implementacją list bez wykorzystania bibliotek STL.
*/

#include <iostream>
#include <cmath>

using namespace std;

//cykliczna lista dwukierunkowa(wskaznikowa)//
class List {
public:
    //struktura elementu//
    struct Node {
        string word;
        int value;
        Node *next;
        Node *prev;
    };
private:
    Node *head, *curr;
    int counter; //licznik elementow

public:
    //konstruktor//
    List() {
        counter=0;
    }
    
    //metod sprawdzajaca czy lista jest pusta//
    bool empty() {
        return head==nullptr;
    }

    //metoda dodajaca na koniec//
    void push_back(string word, int value, int size) {
       Node *p= new Node{word, value, nullptr, nullptr};
       if(counter==0) {
           head = p; curr = p;
       } else {
           curr->next = p; p->prev = curr;
           curr = p;
       }
       ++counter;
       if(size == counter) {
            head->prev = curr;
            curr->next = head;
       }
    }

    //usuwa dany element i zwraca waertosc aktualnego wskaznika//
    int erase()
    {
        if(counter == 1) {
            head=nullptr;
            --counter;
        }
        int valuecurr = curr->value;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr = curr->prev;

        --counter;
        if(valuecurr > 0) return valuecurr;
        else return valuecurr+1;
    }

    //dodaje element przed aktualnym wskaznikiem//
    void insert(string str, int val, int newval) {
        Node *p1= new Node{str, val, nullptr, nullptr};
        curr->value = newval;
        p1->prev = curr->prev; p1->next = curr;
        curr->prev->next = p1;
        curr->prev = p1;
        ++counter;
    }

    //aktualny element//
    void index(int n) {
        int currn = abs(n%counter);     //przesuniecie % licznik
        if(counter-currn > counter/2) {
            while(currn-- > 0) {
                if(n<0)
                   curr = curr->prev;
                else
                    curr = curr->next;
            }
        }
        else {
            int curcurn = counter-currn;
            while(curcurn-- > 0) {
                if(n<0)
                   curr = curr->next;
                else
                    curr = curr->prev;
            }
        }
    }

    //wyswietlanie//
    void print() {
        cout << curr->word << " ";
    }

    //wartosc aktualnego wskaznika//
    int current() {
        return curr->value;
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    
    int n, s;               //n - rozmiar listy slow //s - numer slowa startowego
    List lista;             //nasza lista
    unsigned int p;         //ilosc slow oczekujacych
    string word; int num;   //zmienne dla slowa i wartosci
    cin >> n >> s;          
    for(int i = 0; i<n; i++) {
        cin >> word >> num;
        lista.push_back(word, num, n);
    }
    cin >> p;

    lista.index(s+1);       //indeks startowy

    while(!lista.empty()) { 
        if(lista.current() == 0) {
            cin >> word >> num >> n;
            lista.insert(word, num, n);     //wstawiamy nowy element
            lista.index(n);                 //aktualny element
        } else {
            lista.print();                  //wyswietlamy
            lista.index(lista.erase());     //ustawiamy na aktualny element i usuwamy
        }
    }
    
    return 0;
}