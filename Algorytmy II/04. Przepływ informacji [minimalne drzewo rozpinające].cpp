/*
Treść zadania
Partycja Logiczna po powrocie z Warszawy pochwaliła się swoim innowacyjnym pomysłem znajomym. Zauważyła, że w niektórych grupach społecznych, do których należy, przepływ informacji jest bardzo dobry. W innych zaś wiadomość, którą się podzieliła, wróciła do niej. Wszystko byłoby w porządku, gdyby jej rozmówca wiedział, że ten innowacyjny pomysł należy do jej osoby. Niestety... rozczarowujące okazało się, że jej interlokutor nie był tego świadomy. Nic w tym dziwnego komunikacja interpersonalna powoduje, że dane często stają się “zaszumione” - przykładem może być gra “głuchy telefon”.

Cała sytuacja bardzo zdenerwowała naszą bohaterkę i doszła do wniosku, że nie będzie chwaliła się swoimi osiągnięciami w środowiskach, gdzie informacje mogą zataczać koło. Chce zmniejszyć prawdopodobieństwo wystąpienia takiej sytuacji, dlatego skłonna jest wykluczyć wszystkie grupy społeczne, gdzie dowolna informacja może do kogoś wrócić.

Bohaterka wie, że rozmawiają ze sobą osoby o wspólnych zainteresowaniach. Dodatkowo osoby te mogą rozmawiać na różne tematy, nie tylko te dotyczące wspólnych zainteresowań. Innymi słowy przepływ informacji jest pomiędzy tymi dwiema osobami. Osoba, która otrzymała informacje od swojego rozmówcy może przekazać je innemu rozmówcy, z którym również ma wspólne zainteresowania.

Partycja zastanawia się, które grupy społeczne wykluczyć ze swojego przepływu informacji.

WEJŚCIE
W pierwszej linii wejścia znajduje się liczba naturalna n, mówiąca o ilości osób w danej grupie społecznej. Następnie program powinien wczytać n sekwencji danych: m, czyli ilość zainteresowań danego członka grupy społecznej, a następnie m liczb całkowitych będących odpowiednikami dziedzin, którymi jest zainteresowana ta osoba.

0 <= n, m, numery dziedzin <= 2000000000

WYJŚCIE
Na wyjściu algorytm powinien wypisać jedną z informacji: TAK - jeśli jakaś informacja może wrócić do tej samej osoby i tym samym Partycja powinna wykluczyć tą grupę, NIE - w przeciwnym wypadku.

PRZYKŁADOWE DANE WEJŚCIOWE
I

4
3 1 2 3
2 3 4
2 4 5
2 5 6
II

4
3 1 2 3
2 3 4
2 4 5
2 3 5
PRZYKŁADOWE DANE WYJŚCIOWE
I

NIE
II

TAK
UWAGI
Rozwiązane zadania powinno być implementacją struktury zbiorów rozłącznych.
*/

#include <iostream>
#include <list>
#include <string>
#include <map>

using namespace std;

struct Node {
    Node *father, *next, *prev;                 //ojciec, następnik, poprzednik w liście
    Node *sec_next, *sec_tail;                  //następnik w zbiorze oraz ogon zbioru
    int sec_size;                               //rozmiar zbioru
    int index;                                  //indeks elementu
};

//Lista zbiorów do struktury zbiorów rozłącznych//
class Our_list {
    Node *head, *curr;                          //głowa i aktualny wskaźnik
    map<int, list<Node*>> map_neighbours;       //mapa krawędzi (int - zainteresowanie, lista - elementy)
public:
    Our_list() {
        head = nullptr; curr = nullptr;
    }

    void push_back(int i, Node *n) {                    //dodajemy elementy na koniec listy zbiorów//
        n->sec_next = nullptr;                          //zerujemy następnik zbioru
        n->next = nullptr; n->prev = nullptr;           //zerujemy następnik i poprzednik listy zbiorów      
        n->father = n; n->sec_tail = n;                 //ustawiamy ojca i ogon zbioru elementowi 
        n->sec_size = 1; n->index = i;                  //ustawiamy wielkość zbioru i indeks elementowi
        if(head == nullptr) {                           //gdy lista jest pusta
            head = n; curr = n;                         //ustawiamy głowę i aktualny element
        } else {                                        //gdy w liście są już inne elementy
            curr->next = n; n->prev = curr;             //to dodajemy element na koniec
            curr = n;                                   //i ustawiamy go jako aktualny element
        }
    }

    void map_in(int i, Node *val) {             //dodajemy elementy do mapy krawędzi//
        map_neighbours[i].push_back(val);       
    }

    Node* find_tree(Node *value) {              //szukamy elementu w zbiorach//
        return value->father;                   //i zwracamy jego ojca
    }

    void erase(Node *val) {                     //usuwamy element z listy zbiorów//
        //Jeżeli element jest głową//
        if(val == head) {
            head = head->next;
        }
        //W każdym przypadku//
        if(val->next) val->next->prev = val->prev;
        if(val->prev) val->prev->next = val->next;
        val->next = nullptr; val->prev = nullptr;
    }

    void union_tree(Node *first_val, Node *sec_val) {                       //łączymy dwa zbiory//
        //Wybieramy mniejszy zbiór//
        if(first_val->father->sec_size < sec_val->father->sec_size) {       //Wybieramy mniejszy, ponieważ będziemy potem zmieniać ojca
            //Wypinamy z głównej listy//                                    //każdemy elementowi w tym mniejszym zbiorze na nowego
            erase(first_val);
            //Przypinamy mniejszą listę na koniec większej listy//
            sec_val->father->sec_tail->sec_next = first_val->father;
            //Ustawiamy ojcowi nowy koniec listy//
            sec_val->father->sec_tail = first_val->father->sec_tail;
            //Zmieniamy ojcowi rozmiar na aktualny//
            sec_val->father->sec_size = sec_val->father->sec_size + first_val->father->sec_size;
            //Zmieniamy mniejszej liście ojca na aktualnego//
            Node *n = first_val->father;
            while(n != nullptr) {
                n->father = sec_val->father;
                n = n->sec_next;
            }
        } else {
            //Wypinamy z głównej listy//
            erase(sec_val);
            //Przypinamy mniejszą listę na koniec większej listy//
            first_val->father->sec_tail->sec_next = sec_val->father;
            //Ustawiamy ojcowi nowy koniec listy//
            first_val->father->sec_tail = sec_val->father->sec_tail;
            //Zmieniamy ojcowi rozmiar na aktualny//
            first_val->father->sec_size = sec_val->father->sec_size + first_val->father->sec_size;
            //Zmieniamy mniejszej liście ojca na aktualnego//
            Node *n = sec_val->father;
            while(n != nullptr) {
                n->father = first_val->father;
                n = n->sec_next;
            }
        }
    }

    //Funkcja główna algorytmu//                                                                //Funkcja główna sprawdza czy wierzchołki
    string main_fun() {                                                                         //są w tym samym zbiorze, jeżeli nie to
        //Przeglądamy mapę krawędzi//                                                           //łączy dane zbiory, a w przeciwnym wypadku
        for(auto x : map_neighbours) {                                                          //kończymy działanie programu i zwraca
            //Przeglądamy listę od początku do końca//                                          //"TAK", ponieważ informacja może wrócić
            for(list<Node*>::iterator i = x.second.begin(); i != x.second.end(); ++i) {         //sama do siebie.
                list<Node*>::iterator j = i;
                //Przeglądamy listę od i do końca//
                for(j++; j != x.second.end(); ++j)  {
                    //Jeżeli find nie zwróci tego samego ojca//
                    if(find_tree(*i) != find_tree(*j)) {
                        //To łączymy oba zbiory//
                        union_tree(*i, *j);
                    } else return  "TAK";   //W przeciwnym wypadku kończymy program//
                }
            }
        }
        return  "NIE";  //Zwracamy "NIE", bo informacja nie wróciła do samej siebie//
    }

};

int main() {
    ios_base::sync_with_stdio(false);       //Magiczna linijka

    int n, m, ins;                          //Ilość wierzchołków, ilość zainteresowań wierzchołka, numer zainteresowania
    cin >> n;                               //Wczytujemy ilość wierzchołków

    Our_list lista;                         //Tworzymy listę zbioróW

    map<int, list<Node*>> our_map;          //Tworzymy mapę krawędzi

    for(int i = 0; i < n; i++) {            //Wczytujemy wszystkie wierzchołki
        Node *new_node = new Node;
        cin >> m;
        for(int j = 0; j < m; j++) {        //Wczytujemy zainteresowania
            cin >> ins;
            lista.map_in(ins, new_node);
        }
        lista.push_back(i, new_node);       //dodajemy element do listy
    }

    cout << lista.main_fun() << endl;       //Wykonujemy główną funkcję programu

    return 0;
}