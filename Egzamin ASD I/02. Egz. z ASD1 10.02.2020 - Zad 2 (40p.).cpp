/*
Treść zadania
Napisz program sprawdzający czy wczytany nieskierowany graf da się pokolorować dwoma kolorami, to jest nadać wierzchołkom etykiety 0 i 1 w taki sposób, żeby każde dwa sąsiednie wierzchołki miały różne etykiety.

Wejście
Na standardowym wejściu program otrzymuje liczbę t zestawów, a następnie t opisów poszczególnych zestawów. Opis zestawu składa się z liczby n wierzchołków grafu (ponumerowanych od 0 do n-1) liczby m krawędzi grafu oraz m opisów krawędzi grafu. Każdy opis krawędzi składa się dwóch liczb całkowitych oznaczających numery wierzchołków połączonych daną krawędzią.

1<=n<=120000
0<=m<=300000
Wyjście
Dla każdego zestawu danych program powinien wypisać TAK lub NIE w zależności czy wczytany graf da się czy się nie da pokolorować dwoma kolorami.

Przykłady
Wejście
2
4 2
0 2
1 3
3 3
0 1
1 2
2 0
Wyjście
TAK NIE
Uwaga
Magiczna linijka: ios_base::sync_with_stdio(false);

Program musi być próbą rozwiązania przedstawionego problemu. Programy, które będą próbowały zgadnąć rozwiązanie bez rozwiązania problemu (np. zgadując wynik) będą dyskwalifikowane.
*/