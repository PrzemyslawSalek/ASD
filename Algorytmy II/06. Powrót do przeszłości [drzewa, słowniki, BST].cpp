/*
Treść zadania
Wracając do zmagań naszej bohaterki z października 2019 roku, wiemy o dużych zawirowaniach i nielogicznych decyzjach w światowej polityce. Te nielogiczne decyzje i nierozwiązane tropy męczą naszą bohaterkę do dzisiaj.

Przez okres tych paru miesięcy Partycja sporo przemyślała i chce dalej kontynuować swoje zmagania z odkryciem źródła tych decyzji. Tym razem ma inny pomysł na połączenie poszlak i tropów. Wszystkie tropy zostały opatrzone pewną wartością. Wartość, jaką Partycja opisała każdą z poszlak to wpływ poglądów politycznych. Gdy wartość jest większa poglądy są bardziej prawicowe. Należy dodać, że kolejność pojawiających się tropów ma ogromne znaczenie. Wynika to z tego, że poprzednie wydarzenia mają wpływ na to, jak postrzegane politycznie są kolejne tropy.

Pani doktor z politologii w oparciu o swoje poprzednie badania twierdzi, że prawidłowe tropy należą do relatywnie wąskiej grupy wszystkich poszlak. Jest nawet w stanie w prosty sposób odrzucić przesłanki, które do tej wąskiej grupy nie należą. Doświadczenia naszej bohaterki mówią, że tylko w obrębie pewnych wpływów poglądów politycznych znajduje się poprawny trop, zaś skrajne tropy może pominąć w swoich rozważaniach.

Dotychczas Partycja była przekonana, że tylko jeden trop może być tym prawidłowym, jednak zmieniła zdanie. Twierdzi, że w całym tym zamieszaniu źródło nielogicznych decyzji wynika z dwóch poszlak. Niestety zna jedynie sumę politycznych wpływów obu tych przesłanek, ponieważ ich konsekwencją jest aktualny stanu rzeczy. Trzeba pamiętać, że wartość wpływu poglądów politycznych na dzisiejsze wydarzenia jest jedynie estymowany. W związku z tym nasza dociekliwa Pani detektyw może nie znaleźć pary tropów, które wskazywałyby na przyczynę współczesnych faktów.

Niestety tylko jedna para tropów jest poprawna i doprowadzi naszą bohaterkę do rozwiązania tej zagadki. Partycja wie, że wybór odpowiedniej pary tropów zależny jest od chronologicznej kolejności ich poznawania. Dodatkowo zauważyła, że aby odnaleźć odpowiednią parę dwóch poszlak będących źródłem nielogicznych decyzji, należy znaleźć taką parę tropów, których różnica wpływów politycznych jest najmniejsza.

WEJŚCIE
W pierwszej linii wejścia znajduje się liczba naturalna n, która jest ilością tropów. Następnie program powinien odczytać n wartości wpływów politycznych dla chronologicznie przedstawionych tropów. W kolejnym kroku program powinien odczytać dwie wartości a i b, które są granicami domkniętego przedziału wartości wpływów politycznych dla przesłanek, które warto rozważać. Na koniec program powinien odczytać estymowaną wartość k , która jest wpływem poglądów politycznych na dzisiejsze wydarzenia.

0 <= n, k, a, b, wartości wpływów politycznych dla tropów <= 2000000000

WYJŚCIE
Na wyjściu program powinien wypisać parę wartości wpływów poglądów politycznych tropów, które spełniałyby wartość k lub “NIE ZNALEZIONO” w przeciwnym wypadku. Wartości pary powinny być wypisane w kolejności niemalejącej.

PRZYKŁADOWE DANE WEJŚCIOWE
7                                                                               
15 10 20 8 12 16 25                                                             
9 16                                                                            
25 
PRZYKŁADOWE DANE WYJŚCIOWE
10 15
UWAGI
W rozwiązaniu zadania powinna pojawić się implementacja drzew BST, precyzując powinny pojawić się operacje tj. dodawanie nowych węzłów, przycinanie drzewa BST do określonego przedziału oraz wyszukiwanie pary liczb spełniających podaną sumę.
*/

#include <iostream>
#include <set>

using namespace std;

class BSTree {                              //drzewo BST
    struct Node {                           //struktura elementu drzewa
        int value;                          //wartość (klucz też) elementu
        Node *r_son, *l_son, *father;       //wskaźnik na prawego i lewego syna oraz ojca
    };

    Node *root;                             //wskaźnik na korzeń drzewa
public:

    BSTree() {                              //konstruktor drzewa
        root = nullptr;                     //brak korzenia
    }

    void add(int x) {                                                       //metoda dodająca element do drzewa
        if(!root) {                                                         //jeżeli nie mamy jescze zadnego elementu w drzewie
            root = new Node{x, nullptr, nullptr, nullptr};                  //to nowy element jest korzeniem drzewa
        } else {                                                            //natomiast gdy mamy już korzeń drzewa to
            Node *curr = root;                                              //ustawiamy aktualny wskaźnik na korzeń
            while(true) {                                                   //dopóki nie dodamy elementu 
                if(x <= curr->value && !curr->l_son) {                      //gdy nowy element jest mniejszy od aktualnego i aktualny nie ma syna
                    curr->l_son = new Node{x, nullptr, nullptr, curr};      //to dodajemy nowy elment jako lewy syn
                    break;                                                  //koniec petli
                } else if(x <= curr->value && curr->l_son) {                //gdy nowy element jest mniejszy ale mamy juz syna
                    curr = curr->l_son;                                     //to przesuwamy sie w drzewie dla kolejnego obrotu petli
                } else if(x > curr->value && !curr->r_son) {                //gdy nowy element jest wiekszy od aktualnego i nie ma syna
                    curr->r_son = new Node{x, nullptr, nullptr, curr};      //to nowy element jest prawym synem
                    break;                                                  //konczymy petle
                } else if(x > curr->value && curr->r_son) {                 //gdy nowy element jest wiekszy ale ma prawego syna
                    curr = curr->r_son;                                     //to przesuwamy sie po drzewie dla kolejnego obrotu petli
                }
            }
        }
    }

    Node *max_node(Node *r) {               //metoda ktora zwraca najwiekszy element w galezi
        while(r->r_son) {                   //dopoki mamy prawego syna
            r = r->r_son;                   //to idziemy dalej
        }
        return r;                           //zwracamy najwiekszy element (czyli najniższego prawego syna)
    }

    void del(Node *v) {                                         //metoda usuwajaca element z drzewa
        if(v->l_son && v->r_son) {                              //gdy element ma obu synow
            Node *w = max_node(v->l_son);                       //to szukamy najwikeszego elementu zaczynajac od lewego syna
            swap(v->value, w->value);                           //zamieniamy nasza wartosc z najwiekszym synem
            v = w;                                              //naszym aktualnym wskaznikiem jest byly najwiekszy syn
        }
        if(v->l_son) {                                          //gdy lewy syn istnieje
            v->l_son->father = v->father;                       //to ojcem lewego syna staje sie ojcec naszego elementu
        }
        if(v->r_son) {                                          //gdy prawy syn istnieje
            v->r_son->father = v->father;                       //to ojcem prawego syna staje sie ojciec naszego elementu
        }
        if(v->father && v->father->l_son == v) {                //gdy ojciec istnieje i nasz element jest lewym synem ojca
            if(v->l_son) v->father->l_son = v->l_son;           //to gdy nasz lewy syn istnieje to nasz lewy syn staje sie lewym synem ojca
            else if(v->r_son) v->father->l_son = v->r_son;      //gdy nasz prawy syn istnieje to nasz prawy syn staje sie lwym synem ojca
            else v->father->l_son = nullptr;                    //gdy zaden syn nie istniej to usuwamy lewego syna ojcowi
        }
        if(v->father && v->father->r_son == v) {                //gdy ojciec istnieje i nasz element jest prawym synem ojca
            if(v->l_son) v->father->r_son = v->l_son;           //---||---
            else if(v->r_son) v->father->r_son = v->r_son;      //---||---
            else v->father->r_son = nullptr;                    //---||---
        }
        v = nullptr;                                            //usuwamy nasz element
    }

    void del_tree(Node *n, int a, int b) {                  //funkcja usuwajaca wszystkie elementy spoza zakresu (prawy syn, lewy syn, ojciec)
        if(n) {                                             //jezeli element istnieje
            if(n->r_son) del_tree(n->r_son, a, b);          //jezeli prawy syn istnieje to wywolujemy rekurencyjnie funkcje na nim
            if(n->l_son) del_tree(n->l_son, a, b);          //jezeli lewy syn istnieje to wywyolujemy rekurencyjnie fukncje na nim
    
            if(n->value < a || n->value > b) del(n);        //jezeli element nie miesci sie w zakresie to go usuwamy
        }
    }
    

    Node *get_root() {      //funkcja zwracajaca korzen
        return root;        //zwraca korzen
    }

    bool find_pair(set<int> &x, int k, Node *n) {                   //funkcja szukajaca pary liczb rownej wartosci wplywow politycznych
        if(!n) return false;                                        //jezeli element nie istnieje to zwracamy false
        if(find_pair(x, k, n->l_son)) return true;                  //jezeli rekurencja na lewym synu zwroci true to my tez zwracamy true
        if(x.count(k - n->value)) {                                 //jezeli szukany element znajduje sie w zbiorze elementow
             if(k - n->value < n->value)                            //wyswietlamy najpierw mniejszy element
                 cout << k - n->value << " " << n->value << endl;   //a potem wiekszy element
             else 
                 cout << n->value << " " << k - n->value << endl;
             return true;                                           //i zwracamy true
        } else {                                                    //gdy szukany element nie znajduje sie w zbiorze
            x.insert(n->value);                                     //to dodajemy wartosc aktualnego elementu do zbioru
            if(find_pair(x, k, n->r_son)) return true;              //jezeli rekurencja na prawym synie zwroci true to my zwracamy true
        }
        return false;                                               //jezeli nie znajdziemy pary liczb to zwracamy false
    }
};

int main() {
    ios_base::sync_with_stdio(false);                           //magiczna linijka

    int n, x;                                                   //ilosc tropow, zmienna na tropy
    cin >> n;                                                   //wczytujemy ilosc tropow

    BSTree our_tree;                                            //tworzymy drzewo BST

    for(int i = 0; i < n; i++) {                                //petla do wczytywania danych
        cin >> x;                                               //pobieramy wartosc z wejscia
        our_tree.add(x);                                        //dodajemy wartosc do drzewa
    }

    int a, b, k;                                                //granice przedziału wpływów politycznych, estymowana wartość
    cin >> a >> b >> k;                                         //wczytujemy dane

    our_tree.del_tree(our_tree.get_root(), a, b);               //usuwamy z drzewa wartosci spoza przedzialu

    set<int> tree_set;                                          //tworzymy zbior dla elementow drzewa

    if(!our_tree.find_pair(tree_set, k, our_tree.get_root()))   //wywolujemy glowna funkcje szukajaca wyniku dla algorytmu
        cout << "NIE ZNALEZIONO" << endl;                       //jezeli nie znajdzie wyniku to zwracamy odpowiedni komunikat

    return 0;
}