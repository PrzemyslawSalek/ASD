/*
Treść zadania
﻿﻿
Od pewnego czasu Partycja miała wrażenie, że ktoś ją śledzi. Kiedy przechadzała się po mieście wręcz czuła spojrzenia tajnych agentów. Nawet we własnym mieszkaniu czuła się nieswojo. Zaczęła się zastanawiać czy przypadkiem ktoś nie umieścił urządzeń podsłuchujących w jej lokum. Udała się do swojego przyjaciela który wręczył jej detektor pluskiew. Urządzenie jest w stanie określić ilość podsłuchów w pokoju oraz wskazać kierunek do każdego z nich z dowolnego punktu w formie kierunków geograficznych. Partycja obawia się, że jeżeli rozpocznie poszukiwania osobiście, wzbudzi tym czujność agentów. Postanowiła zatem wykorzystać do tego celu robota jednak potrzebuje odpowiedniego oprogramowania.

Wejście:
Na wejściu program otrzymuje trzy liczby naturalne. Pierwsze dwie opisują rozmiary mieszkania Partycji w postaci dwóch liczb x oraz y. Ostatnia liczba to ilość poszukiwanych pluskiew t. Do lokalizacji należy wykorzystać funkcję wbudowaną std::string test(unsigned &x, unsigned &y, unsigned &id). Dwie pierwsze zmienne to współrzędne robota w pokoju natomiast ostatnia to numer poszukiwanej pluskwy numerowana od 0 do t-1. Funkcja zwraca jeden z ośmiu kierunków geograficznych (N, NE, E, SE, S, SW, W, NW) określające w którą stronę należy się poruszyć, żeby znaleźć poszukiwany punkt. Jeżeli podsłuch znajduje się w testowanym punkcie, funkcja zwróci pusty ciąg znaków.

Wyjście:
Na wyjściu program powinien wyświetlić lokalizację wszystkich pluskiew zgodnie z rosnącą numeracją id funkcji test.

0 < x ≤ 2000000000

0 < y ≤ 2000000000

0 < t ≤ 100000

Przykładowe wejście:
20 20 2
Przykładowe wyjście:
5 5
14 16
Program przesyłany na sprawdzarkę nie może zawierać funkcji test! Zostanie ona automatycznie dołączona przez system do rozwiązania i jest charakterystyczna dla każdego z testów.
Funkcja w przykładzie jest zdefiniowana następująco:
std::string test(unsigned &x, unsigned &y, unsigned &id) {
    unsigned xTest, yTest;
    std::string direction = "";
    switch( id ) {
    case 0:
        xTest = 5;
        yTest = 5;
        break;
    case 1:
        xTest = 14;
        yTest = 16;
        break;
    default:
        xTest = 0;
        yTest = 0;
        break;
    }
    if(yTest < y)
        direction = "S";
    else if(yTest > y)
        direction = "N";
    if(xTest < x)
        direction += "W";
    else if(xTest > x)
        direction += "E";
    return direction;
}
*/

#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);   //magiczna linijka
    
    unsigned x, y, id;                  //rozmiar mieszkania, ilosc poszukiwanych pluskiew
    cin >> x >> y >> id;                //wczytujemy dane

    string strTest;                     //string na test

    unsigned xMin=0, xMax=0, yMin=0, yMax=0, xSr=0, ySr=0;  //krawedzie badanego obszaru oraz punkt srodkowy

    for(unsigned i = 0; i < id; i++) {      //petla ilosci pluskiew
        xMin = 0; xMax = x; yMin = 0; yMax = y;     //ustawiamy krawedzie
        xSr = x/2; ySr = y/2;               //punkt srodkowy
        strTest = test(xSr, ySr, i);        //pierwszy test
        while(true) {                       //dopoki true bo wyjdzie nam w warunku znalezienia pluskwy
            if(strTest == "") {             //znaleziono pluske
                cout << xSr << " " << ySr << endl;
                break;
            } else if(strTest == "N") {     //polnoc
                yMin = ySr;
                ySr = (yMin+yMax)/2;
            } else if(strTest == "NE") {    //poln-wsch
                xMin = xSr;
                yMin = ySr;
                xSr = (xMin+xMax)/2;
                ySr = (yMin+yMax)/2;
            } else if(strTest == "E") {     //wsch
                xMin = xSr;
                xSr = (xMin+xMax)/2;
            } else if(strTest == "SE") {    //polu-wsch
                yMax = ySr;
                xMin = xSr;
                xSr = (xMin+xMax)/2;
                ySr = (yMin+yMax)/2;
            } else if(strTest == "S") {     //poludnie
                yMax = ySr;
                ySr = (yMin+yMax)/2;
            } else if(strTest == "SW") {    //polu-zach
                xMax = xSr;
                yMax = ySr;
                xSr = (xMin+xMax)/2;
                ySr = (yMin+yMax)/2;
            } else if(strTest == "W") {     //zachod
                xMax = xSr;
                xSr = (xMin+xMax)/2;
            } else if(strTest == "NW") {    //poln-zach
                xMax = xSr;
                yMin = ySr;
                xSr = (xMin+xMax)/2;
                ySr = (yMin+yMax)/2;
            }
            strTest = test(xSr, ySr, i);    //test po warunku dla nastepnej iteracji
        }
    }

    return 0;
}