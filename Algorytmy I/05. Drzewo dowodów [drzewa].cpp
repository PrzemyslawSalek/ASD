/*
Treść zadania
Grupa operacyjna Partycji (którą udało się skompletować w ostatnim czasie) działała bardzo prężnie i każdego dnia wprowadzała do ich współdzielonego arkusza kalkulacyjnego dane o nowych materiałach dowodowych. Umówili się na dokładne kategoryzowanie danych i przykładowy wpis do arkusza wyglądał następująco:

"Kategoria 1 - Podkategoria 4 - Rodzaj 2 - Typ 7 - Wpis 2" lub "Kategoria 3 - Podkategoria 2 - Rodzaj 6" czy też "Kategoria 3 - Podkategoria 2 - Rodzaj 3" co w skrócie można zapisać jako: 1 4 2 7 2 dla pierwszego przykładu, 3 2 6 dla drugiego przykładu i 3 2 3 dla trzeciego przykładu.

Danych było coraz więcej i śledczy zaczęli się coraz bardziej gubić. Partycja doszła do wniosku, że dużo lepiej wyglądałoby to w formie drzewa, takiego jak poniżej.

          0
         / \
        1   3
       /     \
      4       2
     /       / \
    2       6   3
   /
  7
 /
2

Potrzebowała więc małego systemu, który na podstawie ponumerowanych i skategoryzowanych wpisów umieszczałby poszczególne wartości w odpowiednim miejscu drzewa materiałów dowodowych. Zakładamy, że korzeń drzewa ma numer 0 i od niego zaczynają się wszystkie wpisy.

Wejście
W pierwsze linii wejścia znajduje się liczba naturalna n oznaczająca liczbę wpisów w arkuszu materiałów dowodowych. W kolejnych n liniach znajdują się wpisy. Każdy wpis składa się z liczby naturalnej x, po której następuje x liczb, tworzących wpis.

1 ≤ n ≤ 10000
0 ≤ x ≤ 10000
Wyjście
Na wyjściu należy wyświetlić tak zbudowane drzewo w kolejności preorder. Korzeń o wartości "0" należy na wyjściu pominąć.

UWAGA! W zadaniu nie można używać bibliotek STL.

Przykład
Wejście:
10
5 3 1 5 2 7
4 3 1 2 6
3 3 4 1
2 5 6
3 2 6 7
3 2 6 8
3 2 5 6
1 1
1 3
2 1 3 
Wyjście:
3 1 5 2 7 2 6 4 1 5 6 2 6 7 8 5 6 1 3
*/

#include <iostream>


using namespace std;

struct Node{
    int val;
    Node *fat, *son, *bro;      //ojciec syn brat
};

class Tree{

    Node *root;     //korzeń

public:
    //konstruktor//
    Tree() {
        root->val = 0;
        root->bro = nullptr;
        root->son = nullptr;
        root->fat = nullptr;
    }

    //zwraca pierwszego syna po root//
    Node* getRoot() {
        return root->son;
    }

    //pierwsza galaz//
    void addfirst(int counter) {
        int value;
        Node *n = root;                 //uchwyt

        for(int i = 0; i < counter; i++) {  //iteracja po zestawie

            cin >> value;               //wczytujemy wartosc
            Node *newNode = new Node;   //tworzymy nowy wskaznik
            newNode->val = value;       //przypisujemy mu wartosc
            newNode->fat = n;           //ustawiamy ojca
            newNode->bro = nullptr;     //nie ma brata
            n->son = newNode;           //ustawiamy element jako kolejny
            n = n->son;                 //zmieniamy uchwyt
        }
    }

    //kolejne galezie//
    void add(int counter) {
        int value;
        Node *n = root;         //uchwyt
        Node *l_bro;            //uchwyt na brata
        Node *curr = root;      //aktualny wskaznik
        int i;

        for(i = 0; i < counter; ++i) {

            cin >> value;       //wczytujemy wartosc

            n = n->son;         //ustawiamy uchwyt na syna
            l_bro = nullptr;    //restart uchwytu na brata
            if(n) {             //jezeli istnieja elementy
                while(n) {      
                    if(n->val == value) {       //jezeli wartosc jest rowna dodawanej
                        curr = n;               //to przestawiamy wskaznik
                        break;                  //wychodzimy
                    }
                    if(n->bro==nullptr) l_bro = n;  //jezeli nie ma braci to ustawiamy uchwyt brata zeby dodac poza petla
                    n=n->bro;                   //przesuwamy sie po braciach
                }
                if(l_bro) {                     //jezeli dodajemy brata
                    Node *newNode = new Node;   
                    newNode->val = value;
                    newNode->bro = nullptr;
                    newNode->fat = nullptr;
                    newNode->son = nullptr;
                    l_bro->bro = newNode;
                    curr = l_bro->bro;          //ustawiamy aktualny wskaznik
                }
            } else {                            //dodajemy synna
                Node *newNode = new Node;       
                newNode->val = value;
                newNode->bro = nullptr;
                newNode->fat = nullptr;
                newNode->son = nullptr;
                curr->son = newNode;
                curr = curr->son;               //ustawiamy aktualny wskaznik
            }
            n = curr;
        }
    }

    //funkcja wyswietlajaca preorder czyli ojciec syn brat//
    void preorder(Node *n){
        if(n) {                     //jezeli element nie jest null
            cout<<n->val<<" ";      //wyswietlamy

        if(n->son!=nullptr)         //jezeli ma syna
                preorder(n->son);
        if(n->bro!=nullptr)         //jezeli ma brata
                preorder(n->bro);
        }
    }



};

int main() {
    ios_base::sync_with_stdio(false);
    Tree tree;      //tworzymy drzewo

    int x, n;       //x to liczby dodawane do drzewa n to ilosc zestawow

    cin >> n;

    cin >> x;
    tree.addfirst(x);   //dodajemy pierwsza galaz

    for(int i = 1; i < n; i++) {    //dodajemy kolejne
        cin >> x;
        tree.add(x);
    }

    tree.preorder(tree.getRoot());  //wyswietlamy

    return 0;
}