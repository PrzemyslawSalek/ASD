/*
Treść zadania
﻿
Partycja Logiczna zauważyła, że rządzący na całym świecie coraz więcej obiecują swoim obywatelom. Szczególnie dużo obietnic dotyczy okresu po wrześniu 2020 roku (na przykład jeden z rządów obiecał podnieść minimalną pensję dwukrotnie, inny zbudować kopię Wielkiego Muru Chińskiego na innym kontynencie, a jeszcze inny rozwiązać problem emisji CO2). Partycja zleciła niezależnemu ekspertowi z jednej z czołowych polskich uczelni przeanalizowanie obietnic wyborczych z całego świata pod kątem złożonych obietnic i zadeklarowanego czas ich spełnienia.

Ze względów bezpieczeństwa przygotowaną przez eksperta analizę przekaże Partycji nieznany jej łącznik. Łącznik będzie jechał pociągiem linii Lublin-Kołobrzeg i będzie miał na sobie koszulkę z napisem ,,Łącznik''. Niestety Partycja nie wie gdzie wsiądzie i gdzie wysiądzie łącznik, planuje więc wsiąść do pociągu w Lublinie i przemierzać go w tą i z powrotem wypatrując łącznika. Aby nie wzbudzać podejrzeń Partycja chce chodzić po pociągu tylko tyle ile jest to konieczne. W tym celu sobie tylko znanymi kanałami zdobyła listę pasażerów wraz z informacjami na jakich stacjach wsiadają a na jakich wysiadają. Pomóż Partycji zaplanować momenty w których powinna przejść się po pociągu tak, żeby jak najmniej razy opuszczać przedział, ale jednocześnie żeby miać pewność, że w trakcie któregoś ze spacerów po pociągu spotka łącznika.

Dla uproszczenia załóżmy, że stacje przez które przejeżdża pociąg są ponumerowane kolejnymi liczbami naturalnymi. Spacery Partycji po pociągu odbywają się w trakcie przejazdu pociągu między dwiema kolejnymi stacjami. (Partycja boi się, że w zamieszaniu na stacji mogłaby przeoczyć łącznika)

Wejście
Pierwsza linia wejścia zawiera liczbę całkowitą t - liczbę zestawów danych, których opisy występują kolejno po sobie. W pierwszej linii zestawu danych podana jest liczba naturalna n - liczba pasażerów pociągu. Każda z kolejnych n linii zawiera parę liczb naturalne a i b - opis podróży jednego pasażera (numer stacji na której wsiada i wysiada)

1 ≤ t ≤ 2000
1 ≤ n ≤ 200000
0 < a < b ≤ 1000000000
Wyjście
Dla każdego zestawu danych program powinien wypisać jedną linię zawierającą minimalną liczbę spacerów po pociągu, które musi wykonać Partycja aby mieć pewność, że na którymś z nich spotka łącznika.

Przykładowe wejście
3
3
1 2
2 3
3 4
3
1 2
2 4
3 5
4
1 10
2 3
3 5
11 12
Przykładowe wyjście
3
2
3
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

//funkcja do sort, sortuje po drugim elemencie rosnaco//
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b) {
    return (a.second < b.second);
}

int main()
{
    ios_base::sync_with_stdio(false);   //magiczna linijka

    int t;      //liczba zestawow danych
    cin >> t;

    int n;      //liczba pasazerow

    int a, b;   //stacja na ktorej wsiada i wysiada
    for(int i = 0; i < t; ++i) {
        cin >> n;
        vector<pair<int,int>> vec;  //vector par
        int oK = -1;        //ostatnia kontrola, zaczynamy od -1 poniewaz musimy ustawic pierwszemu zawsze a moze wsiadac na peronie 0
        int W = 0;          //ilosc wejsc
        for(int j = 0; j < n; ++j) {
            cin >> a >> b;
            vec.push_back(make_pair(a, b));     //dodajemy do vectora pary
        }
        sort(vec.begin(), vec.end(), sortbysec);    //sortujemy
        for(auto it = vec.begin(); it < vec.end(); ++it) {  //petla po vectorze
            if(it->first >= oK) {   //sprawdzamy czy ostatnia kontrola jest mniejsza lub rowna pierwszemu elementowi
                W++;        //powiekszamy ilosc wejsc
                oK = it->second;    //zmieniamy ostatnia kontrole na aktualna
            }
        }
        cout << W << endl;  //wyswietlamy ilosc wejsc
    }

    return 0;
}