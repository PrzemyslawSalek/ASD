/*
Treść zadania
Napisz program, który podnosi do zadanej potęgi podane liczby.

Wejście
Na standardowym wyjściu program otrzyma liczbę n liczb, które należy podnieść do potęgi a następnie n par postaci p w. Każda taka para oznacza, że należy liczbę p podnieść do potęgi w. Do mnożenia należy użyć funkcji int mnozenie(int, int).

1<=n<4294967296 
0<=w
Wyjście
Program powinien wypisać wyniki potęgowania.

Przykłady
Wejście
3
2 0
2 1
2 2
Wyjście
1 2 1
gdzie funkcja mnozenie jest zdefiniowana następująco:
int mnozenie(int a, int b){
    return (a*b)%3;
}
Uwaga
Magiczna linijka: ios_base::sync_with_stdio(false);

Program musi być próbą rozwiązania przedstawionego problemu. Programy, które będą próbowały zgadnąć rozwiązanie bez rozwiązania problemu (np. zgadując wynik) będą dyskwalifikowane.
*/

#include <iostream>

using namespace std;

//int mnozenie(int a, int b){
//    return (a*b)%3;
//}

int potegowanie(int a, int b){

    int wynik;

    if(b == 0) return 1;
    if(b%2) return mnozenie(a,potegowanie(a,b-1));

    wynik = potegowanie(a, b/2);

    return mnozenie(wynik,wynik);
}

int main() {

    ios_base::sync_with_stdio(false);

    int n;

    cin >> n;

    int p,w;

    int wynik = 0;

    for(int i = 0; i < n; i++) {
        cin >> p >> w;

        wynik = potegowanie(p,w);

        cout << wynik << endl;
    }
    return 0;
}

/*
3
2 0
2 1
2 2
*/