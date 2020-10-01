/*
Treść zadania
Partycja Logiczna podczas ferii wpadła na innowacyjne rozwiązanie dotyczące technologii elastycznych ekranów. Chciałaby sfinalizować swój pomysł, a więc wymaga to odwiedzenia naszej pięknej stolicy i siedziby Agencji Techniki i Technologii. Niestety to kawałek drogi, a Partycje jazda samochodem bardzo stresuje. W związku z tym wpadła na pomysł, że zabierze ze sobą swoją koleżankę Magistrale. Ona również nie cieszy się wizją prowadzenia samochodu, jednakże bardzo chciałaby zobaczyć Warszawę.

Partycja wymyśliła system, który pozwala zminimalizować czas prowadzenia samochodu, co narazi ją na mniejszy stres. Po drodze do Warszawy znajduje się n postojów, które numerujemy liczbami od 0 do n - 1. Numerem s jest oznaczone miejsce, z którego dziewczyny ruszają w trasę, zaś numerem d miejsce docelowe - Warszawa. Po naniesieniu odpowiedniej siatki na mapę, Partycja zauważyła pewną ciekawą zależność. Mianowicie doszła do wniosku, że mogą poruszać się tylko w jednym z czterech kierunków świata. Dodatkowo zgodnie z naniesioną siatką każdy z postojów był na przecięciu osi odciętych i rzędnych.

Nasza inteligentna bohaterka wpadła na pomysł, że za każdym razem, gdy zmienią swój kierunek o 90 stopni zamieniają się miejscami przy kierownicy. Dodatkowo po drodze mogą zatrzymać się na dowolnej ilości postojów, nie ma znaczenia, jak długo będzie trwała cała trasa. Dla Partycji liczy się tylko to, że powinna być za kierownicą możliwie najkrócej. Na koniec aby dać sobie więcej możliwości do zrezygnowania z prowadzenia automobila, Partycja zaproponowała jeszcze jedną zasadę. Dziewczyny ustaliły, że po każdym postoju Partycja może zdecydować, czy usiądzie za kierownicą. Innymi słowy na każdym fragmencie trasy prowadzącym z postoju do postoju jedna z kobiet usiądzie za kierownicą, gdy poruszają się północ, południe, zaś druga z nich prowadzi podczas jazdy na wschód lub zachód. W szczególności, jeśli pewien odcinek trasy prowadzi dokładnie w jednym z czterech kierunków świata, wtedy na tym odcinku prowadzi tylko jedna z kobiet.

Partycja zastanawia się, jak zaplanować trasę do siedziby Agencji Techniki i Technologii oraz podział pracy, by spędzić za kierownicą jak najmniej czasu. Przyjmujemy, że jedna jednostka na siatce jest równa jednej jednostce stresu Partycji, który należy zminimalizować.

WEJŚCIE
W pierwszej linii wejścia znajduje się liczba naturalna n, mówiąca o ilości postojów. Następnie program powinien wczytać n sekwencji danych: x y, które są współrzędnymi postojów na naniesionej przez Partycje siatce. Na koniec program powinien wczytać dwie liczby naturalne s i d, które są odpowiednio postojem startowym i postojem docelowym, czyli siedzibą instytucji, do której zmierza nasza bohaterka. Każdy postój ma inne współrzędne.

0 <= n <= 32000
0 <= x, y, s, d <= 2000000000

WYJŚCIE
Na wyjściu algorytm powinien wypisać jedną liczbę całkowitą, która jest możliwie najmniejszą liczbą jednostek stresu, które przeżyje nasza bohaterka na trasie z punktu s do punktu d.

PRZYKŁADOWE DANE WEJŚCIOWE
5
2 2
1 1
4 5
7 1
6 7
0 4
PRZYKŁADOWE DANE WYJŚCIOWE
2
Uwaga program rozwiązujący zadanie powinien być implementacją algorytmu Dijkstry i nie powinien korzystać z kopców Fibonacciego
*/

#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <climits>

using namespace std;

//struktura dla postoju
struct Node {
    int index;                                                              //indeks postoju
    int x, y;                                                               //wspolrzedne postoju
    list<int> sasiedzi;                                                     //lista sasiadow (elementow najblizej wedlug x i wedlug y (maksymalnie 4))
};

bool comp_sorted_list_x(Node &a, Node &b) {                                 //komperator do sortowania po x rosnaco
    return a.x < b.x;
}

bool comp_sorted_list_y(Node &a, Node &b) {                                 //komperator do sortowania po y rosnaco
    return a.y < b.y;
}

int distance(Node &a, Node &b) {                                            //funkcja liczaca dystans miedzy postojami
    if(abs(a.x-b.x) < abs(a.y-b.y)) return abs(a.x-b.x);                    //zwroc roznice miedzy x jezeli jest mniejsza niz roznica miedzy y
    else return abs(a.y-b.y);                                               //w przeciwnym wypadku zwroc roznice miedzy y
}

class comparator{                                                           //komperator do sortowania par wedlug pierwszej wartosci rosnaco
public:
    bool operator()(const pair<int,int>& a, const pair<int,int>& b){
        return a.first >= b.first;
    }
};

int main() {
    ios_base::sync_with_stdio(false);                       //magiczna linijka

    int n;                                                  //ilosc postojow 0 <= n <= 32000
    cin >> n;                                               //pobieramy ilosc postojow  0 <= x, y, s, d <= 2000000000

    Node *arr;                                              //tablica na punkty postojow (wspolrzedne x, y)
    arr = new Node[n];                                      //allokowanie tablicy postojow (wspolrzednych x, y)

    Node *sorted_arr;                                       //kopia tablicy ktora bedziemy sortowac wedlug x a potem y
    sorted_arr = new Node[n];                               //allokowanie tablicy

    int x, y;                                               //tymczasowe zmienne na x i y
    int s, d;                                               //postoj startowy, postoj docelowy

    for(int i = 0; i < n; i++) {                            
        cin >> x >> y;                                      //wczytujemy pary wspolrzednych
        Node new_n;                                         //chwilowa zmienna dla postoju
        new_n.index = i; new_n.x = x; new_n.y = y;          //przypisujemy jej dane
        arr[i] = new_n;                                     //zapisujemy do podstawowej tablicy
        sorted_arr[i] = new_n;                              //zapisujemy do kopii tablicy
    }

    sort(sorted_arr, sorted_arr+n, comp_sorted_list_x);                                             //sortujemy wedlug x rosnaco

    for(int i = 0; i < n; i++) {
        if(i == 0)                                                                                  //jezeli jest rowne zero
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //to bierzemy sasiada tylko dalszego
        else if(i == n-1)                                                                           //jezeli jest ostatnim elemenetem
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //to bierzemy tylko wczesniejszego
        else {                                                                                      //w innym przypadku
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //bierzemy wczesniejszego
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //i dalszego
        }
    }

    sort(sorted_arr, sorted_arr+n, comp_sorted_list_y);                                             //sortujemy wedlug y rosnaco

    for(int i = 0; i < n; i++) {
        if(i == 0)                                                                                  //jezeli jest rowne zero
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //to bierzemy sasiada tylko dalszego
        else if(i == n-1)                                                                           //jezeli jest ostatnim elemenetem
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //to bierzemy tylko wczesniejszego
        else {                                                                                      //w innym przypadku
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i-1].index].index);          //bierzemy wczesniejszego
            arr[sorted_arr[i].index].sasiedzi.push_back(arr[sorted_arr[i+1].index].index);          //i dalszego
        }
    }

    cin >> s >> d;                                                                  //wczytujemy postoj startowy oraz docelowy

    int *stress;                                                                    //tablica do algorytmu Dijkstry
    stress = new int[n];                                                            //(do szukania drogi z najmniejszym stresem)

    priority_queue<pair<int, int>, vector<pair<int, int> >, comparator> p_que;      //kolejka priorytetowa na indeksy zmienionych elementów

    for(int i = 0; i < n; i++) {                                                    
        if(i != s) {                                                                //jezeli nie jest startowym elementem
            stress[i] = INT_MAX;                                                    //wypeniamy ja "nieskonczonoscia"
        } else {                                                                    //gdy jest startowym elementem
            stress[i] = 0;                                                          //a startowy element zerem
            p_que.push(make_pair(stress[i], i));                                    //i dodajemys startowy element do kolejki
        }
    }

    while(!p_que.empty()) {                                                         //dopoki kolejka nie jest pusta
        int top_val = p_que.top().second; p_que.pop();                              //bierzemy minimum i usuwamy je z kolejki
        for(auto x : arr[top_val].sasiedzi) {                                       //przegladmy jego sasiadow
            int di = distance(arr[top_val], arr[x])+stress[top_val];                //liczymy dystans miedzy minimum a danym sasiadem
            if(di < stress[x]) {                                                    //jezeli jest mniejsze od wczesniejszej drogi miedzy punktami
                stress[x] = di;                                                     //to zamieniamy
                p_que.push(make_pair(stress[x], x));                                //i dodajemy do kolejki
            }
        }
        if(top_val == d) break;                                                     //gdy dojdziemy do punktu ktory nas intersuje to przerywamy
    }

    cout << stress[d] << endl;                                                      //wyswietlamy wynik     


    return 0;
}