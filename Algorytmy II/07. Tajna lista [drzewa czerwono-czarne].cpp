/*
Treść zadania
﻿
Partycja spędza ostatnio bardzo dużo czasu na analizowaniu listy potencjalnie zagrażających jej osób. Są wśród nich politycy, ukryci agenci specjalni a nawet pani z pobliskiego warzywniaka. Jak wszyscy wiemy, nasza bohaterka lubi porządek. Właśnie dlatego jej lista jest uszeregowana od osób najniebezpieczniejszych do tych mniej niebezpiecznych. Co ważne, miejsca na liście dynamicznie się zmieniają, np. jeżeli pani Krysia z warzywniaka podejrzanie długo wydaje resztę, to po chwili Partycja musi przepisywać listę przenosząc ją o kilka miejsc w górę. Oczywiście czasami wykonuje również inne operacje, takie jak zamiana osób miejscami czy dopisanie nowej. Nasza bohaterka obawia się jednak, że jej notes może wpaść w niepowołane ręce. Właśnie dlatego nadała wszystkim osobom unikalne pseudonimy. Jak można się domyślić prowadzenie takiego notatnika jest bardzo trudne i pracochłonne. Partycja chciałaby mieć program, który pomoże jej z tym zadaniem.

Wejście:
W pierwszej linii wejścia program otrzymuje liczbę n oznaczającą początkową liczbę osób na liście. Następnie w n liniach program otrzymuje ciągi znaków s będących pseudonimami osób. Zakładamy, że pierwsza osoba na liście najbardziej zagraża Partycji. W kolejnym kroku program otrzymuje liczbę m będącą ilością operacji do wykonania. Na koniec w m liniach program otrzymuje opisy operacji. Pierwszy znak zawsze oznacza akcję do wykonania, a po nim pojawiają się stosowne dane zgodnie z poniższym opisem:

a s – dodanie osoby o pseudonimie s na koniec listy, gdzie s jest ciągiem znaków
m s x – przesunięcie osoby o pseudonimie s na liście o x miejsc, gdzie s jest ciągiem znaków, a x liczbą całkowitą (jeżeli x jest dodatnie to przesuwamy osobę w górę listy, w przeciwnym wypadku w dół)
r s1 s2 – zamiana miejscami osoby o pseudonimie s1 z osobą o pseudonimie s2, gdzie s1 i s2 są ciągiem znaków
Wyjście:
Na wyjściu program powinien wypisać listę pseudonimów poczynając od osoby najniebezpieczniejszej.

1 < n ≤ 50000

1 < m ≤ 10000

Przykładowe wejście:
5
Okruszek
Tester
Interfejs
Agent
Scyzoryk
4
r Okruszek Interfejs
a Kontakt
m Kontakt 2
m Interfejs -1
Przykładowe wyjście:
Tester
Interfejs
Okruszek
Kontakt
Agent
Scyzoryk
Uwaga:
Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych drzew czerwono-czarnych bez wykorzystania bibliotek STL.
*/

#include <iostream>

using namespace std;

struct Node {           //struktura elementu w liście
    string pseudo;      //wartość elementu (pseudonimy osob)
    Node *next;         //nastepnik
    Node *prev;         //poprzednik
};

class List {                                                    //lista
    Node *head, *curr;                                          //glowa i aktualny wskaznik(w sumie tez ogon)
public: 
    List() {                                                    //konstruktor
        head = curr = nullptr;
    }

    Node* push_back(string val) {                               //metoda dodawania nowego elementu
        Node *new_node = new Node{val, nullptr, nullptr};       //tworzymy nowy element
        if(!head) {                                             //jezeli glowa jest pusta
            head = new_node;                                    //to nowy element jest glowa
            curr = new_node;                                    // i aktualnym wskaznikiem
        } else {                                                //jezeli nie jest pusta to
            curr->next = new_node;                              //dodajemy element na koniec listy
            new_node->prev = curr;
            curr = new_node;
        }
        return new_node;                                        //zwracamy wskaznik ktory bedzie potrzebny w drzewie
    }

    void shift(int n, Node *val) {                              //przesuwanie elementu "gora/dol"
        Node *cur_val = val;                                    //naszym aktaulnym wskaznikiem jest nasz wskaznik
        if(n>0) {                                               //jezeli przesuniecie jest wieksze od 0
            while(n-- > 0) {                                    
                cur_val = cur_val->prev;                        //to przesuwamy sie w strone poczatku listy
            }
            if(val == curr) curr = val->prev;                   //jezeli nasz element byl ostatnim elementem
            if(val->next) val->next->prev = val->prev;          //wypinamy element z listy
            if(val->prev) val->prev->next = val->next;
            val->prev = cur_val->prev;                          //wpinamy element na nowe miejsce
            if(cur_val->prev) cur_val->prev->next = val;
            cur_val->prev = val;
            val->next = cur_val;
            if(cur_val == head) head = val;                     //jezeli element staje sie pierwszym elementem
        } else {
            while(n++ < 0) {                                    //gdy mamy ujemne przesuniecie
                cur_val = cur_val->next;                        //to przesuwamy sie w strone konca listy
            }
            if(val == head) head = val->next;                   //jezeli element byl piewrszy
            if(val->next) val->next->prev = val->prev;          //wypinamy elemeny
            if(val->prev) val->prev->next = val->next;
            if(cur_val->next) cur_val->next->prev = val;        //wpinamy go na nowe miejsce
            val->next = cur_val->next;
            cur_val->next = val;
            val->prev = cur_val;
            if(cur_val == curr) curr = val;                     //jezeli stal sie ostatnim elementem
        }
    }

    void print() {                          //metoda wyswietlajaca liste
        Node *it = head;
        while(it) {
            cout << it->pseudo << endl;
            it = it->next;
        }
    }

};

class RBtree {              //drzewo czerwono czarne
public:
    struct RBNode {         //struktura elementu drzewa
      string key;           //klucz drzewa (pseudonim osoby)
      char color;           //kolor w drzewie
      Node *wsk;            //wskaznik na element w liscie
      RBNode *father;       //wskaznik na ojca
      RBNode *l_son;        //wskaznik na lewego syna
      RBNode *r_son;        //wskaznik na prawego syna
    };
private:
    RBNode *guard;          //wskaznik na straznika(straznicy to czarne liscie wyrownujace drzewo)
    RBNode *root;           //wskaznik na korzen
    List lista;             //lista glowna
public:

    RBtree() {
        guard = new RBNode{"Bramkasz", 'B', nullptr, guard, guard, guard};      //ustawiamy straznika
        root = nullptr;                                                         //ustawiamy korzen
    }

    void print() {          //funkcja wyswietlajaca liste
        lista.print();      
    }

    RBNode* search(string x) {                  //funkcja szukajaca elementu w drzewie o danym kluczu
        RBNode *v = root;                       //zaczynamy od korzenia

        while(v->key != x) {                    //dopoki klucz sie nie zgadza
            if(x < v->key) v = v->l_son;        //jezeli klucz elementu jest wiekszy od szukanego to idziemy do lewego syna
            else if(x > v->key) v = v->r_son;   //jezeli mniejszy to do prawego
            
            if(v == guard) return nullptr;      //jezeli trafimy na straznika to zwracamy nulla
        }
        return v;                               //jezeli nie to zwracamy wskaznik na element w drzewie
    }

    void left_rotation(RBNode *v) {                                 //lewa rotacja elementow w drzewie
        RBNode *right = v->r_son;                                   //wskaznik na prawego syna elementu
        v->r_son = right->l_son;                                    //prawy syn jest teraz lewym synem prawego syna

        if(v->r_son != guard) v->r_son->father = v;                 //jezeli prawy syn nie jest staznikiem to ojcem prawego syna jest element
        right->father = v->father;                                  //zamieniamy ojcow miejscami

        if(v->father) {                                             //jezeli ojciec elementu istnieje
            if(v == v->father->l_son) v->father->l_son = right;     //jezeli elment jest lewym synem ojca to lewym synem ojca jest prawy syn
            else v->father->r_son = right;                          //jezeli jest prawym synem to prawym synem jest prawy syn
        } else root = right;                                        //jezeli nie ma ojca to root staje sie prawym synem

        right->l_son = v;                                           //lewym synem prawego syna jest nasz element
        v->father = right;                                          //ojcem elementu jest prawy syn
    }

    void right_rotation(RBNode *v) {                                //lewa rotacja elementow w drzewie
        RBNode *left = v->l_son;                                    //wszystko tak samo tylko na odwrotw
        v->l_son = left->r_son;

        if(v->l_son != guard) v->l_son->father = v;
        left->father = v->father;

        if(v->father) {
            if(v == v->father->r_son) v->father->r_son = left;
            else v->father->l_son = left;
        } else root = left;

         left->r_son = v;
         v->father = left;
    }

    void insert(string val) {                                                   //metoda dodawania elementu do drzewa
        Node* wsk = lista.push_back(val);                                       //dodajem element do listy
        RBNode* new_node = new RBNode{val, 'R', wsk, root, guard, guard};       //tworzymy nowy element drzewa
        if(!root) {                                                             //jezel nie mamy korzenia
            root = new_node;                                                    //to dodajemy element jako korzen
            root->color = 'B';                                                  //dajemy mu czarny kolor
            return;                                                             //i konczymy funkcje
        } else {                                                                //w innym przypadku
            RBNode *c = root;                                                   //szukamy miejsca dla naszego elementu
            while(true) {                                                       //i dodajemy go w odpowiednie miejsce
                if(val < c->key && c->l_son == guard) {
                    c->l_son = new_node;
                    c->l_son->father = c; c = c->l_son;
                    break;
                } else if(val < c->key && c->l_son != guard) {
                    c = c->l_son;
                } else if(val >= c->key && c->r_son == guard) {
                    c->r_son = new_node;
                    c->r_son->father = c; c = c->r_son;
                    break;
                } else if(val >= c->key && c->r_son != guard) {
                    c = c->r_son;
                }
            }

            if(!c->father->father) return;                          //jezeli dziadek elementu nie istnieje to konczymy

            while(c != root && c->father->color == 'R') {           //dopoki nie jestesmy w korzeniu i ojciec elementu jest czerwony
                if(c->father == c->father->father->r_son) {         //jezeli ojciec jest prawym synem to 
                    RBNode *uncle = c->father->father->l_son;       //bierzemy jego wujka

                    if(uncle && uncle->color == 'R') {              //przypadek 1 gdy wujek jest czerwony
                        c->father->father->color = 'R';             //to ustawiamy dziadkowi czerwony
                        c->father->color = 'B';                     //ojcowi czarny
                        uncle->color = 'B';                         //i wujkowi czarny
                        c = c->father->father;                      //aktualnym elementem jest dziadek
                    } else {                                        //przypadek 2 gdy wujek jest czarny
                        if(c == c->father->l_son) {                 //gdy nasz element jest lewym synem
                            c = c->father;                          //to aktualnym elementem jest ojciec
                            right_rotation(c);                      //wykonujemy na nim prawa rotacje
                        }
                        c->father->color = 'B';                     //przypadek 3    
                        c->father->father->color = 'R';             //zmieniamy kolor ojcu i dziadkowi
                        left_rotation(c->father->father);           //lewa rotacja na dziadku
                    }
                } else {                                            //gdy ojciec jest lewym synem
                    RBNode *uncle = c->father->father->r_son;       //robimy to samo tylko w odbiciu lustrzanym

                    if(uncle && uncle->color == 'R') {              //przypadek 1
                        c->father->father->color = 'R';
                        c->father->color = 'B';
                        uncle->color = 'B';
                        c = c->father->father;
                    } else {                                        //przypadek 2
                        if(c == c->father->r_son) {
                            c = c->father;
                            left_rotation(c);
                        }                                           //przypadek 3
                        c->father->color = 'B';
                        c->father->father->color = 'R';
                        right_rotation(c->father->father);
                    }
                }
            }
            root->color = 'B';                                      //ustawiamy korzen zawsze czarny
        }
    }

    void shift(int n, string val) {                         //metoda przesuwania w liscie
        RBNode *node_shift = search(val);                   //szukamy w drzewie elementu do przesuniecia
        if(node_shift) lista.shift(n, node_shift->wsk);     //przesuwamy go w liscie bo mamy jego wskaznik
    }

    void change(string n1, string n2) {             //metoda zamiany miejscami elementow
        RBNode* w1 = search(n1);                    //szukamy pierwszego elementu
        RBNode* w2 = search(n2);                    //szukamy drugiego elementu
        if(w1 && w2) {                              //jezeli oba elementu istnieja
            string ts; Node *ws;                    //to zamieniamy miejscami
            ts = w1->wsk->pseudo;                   //ich nazwy w liscie
            w1->wsk->pseudo = w2->wsk->pseudo;
            w2->wsk->pseudo = ts;
            ws = w1->wsk;                           //i wskazniki w drzewie
            w1->wsk = w2->wsk;
            w2->wsk = ws;
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);       //magiczna linijka

    int n;                                  //liczba pseudonimow                         
    cin >> n;

    string tmp;                             //pseudonim
    RBtree tree;                            //drzewo czerwono czarne

    for(int i = 0; i < n; i++) {            //wczytujemy pseudonimy
        cin >> tmp;
        tree.insert(tmp);                   //dodajemy je do listy i drzewa
    }

    cin >> n;                               //liczba operacji
    char sg;
    string n1, n2;  
    int v;

    for(int i = 0; i < n; i++) {
        cin >> sg;                          //znak operacji
        switch(sg) {
        case 'r':                           //jezeli r to zamieniamy miejscami dwa pseudonimy
            cin >> n1 >> n2;
            tree.change(n1, n2);
            break;
        case 'a':                           //jezeli a to dodajemy nowy element
            cin >> n1;
            tree.insert(n1);
            break;
        case 'm':                           //jezeli m to przesuwamy element o v miejsc
            cin >> n1 >> v;
            tree.shift(v, n1);
            break;
        }
    }

    tree.print();                           //wyswietlamy wynik

    return 0;
}