/*
Treść zadania
Napisz program, który przesuwa elementy n-elementowej początkowo posortowanej rosnąco listy o wartościach elementów 0, 1 ... n-1.

Wejście
Program na wejściu dostaje liczbę n elementów listy oraz liczbę m operacji na liście, a następnie m opisów operacji. Pojedynczy opis operacji składa się z pary liczb a b oznaczających, że element listy o wartości a należy przesunąć do przodu o b miejsc. Jeżeli przesuwając dany element na liście dojdziemy do końca listy to należy kontynuować przesuwanie począwszy od początku listy. Wzajemne położenie elementów listy, poza elementem przesuwanym, nie powinno ulec zmianie.

0 < n<=1000000
0<=m<=2000000
0<=b<=n
Wyjście
Na standardowym wyjściu program powinien wypisać elementy przetwarzanej listy w kolejności w jakiej znajdują się na liście po wykonaniu wczytanych operacji.

Przykłady
Wejście
5 3
3 2
2 1
1 5
Wyjście
3 0 1 4 2
Uwaga
Magiczna linijka: ios_base::sync_with_stdio(false);

Rozwiązanie tego zadanie nie powinno używać STL-a.

Program musi być próbą rozwiązania przedstawionego problemu. Programy, które będą próbowały zgadnąć rozwiązanie bez rozwiązania problemu (np. zgadując wynik) będą dyskwalifikowane.
*/
