/*
Treść zadania
Partycja ma już dość tego roku. Wydawałoby się, że kosmiczna katastrofa mogąca oznaczać koniec życia na ziemi to wystarczający powód by uznać rok za nie najlepszy. A tu do tego doszły pożary, pandemia i idąca za tym kwarantanna. Partycja siedząc w domu z nudów zaczęła słuchać starych kaset (dobrze, że magnetofonu nie wyrzuciła na śmieci) i przypomniała jej się jej buntownicza młodość, Ach gdyby zamiast chodzić na punkowe koncerty uczyła się przed maturą matematyki. Skończyłaby informtykę i żyła teraz jak królowa.

Partycja szybko przypomniała sobie, że to wszystko nie ma znaczenia, bo prawdopodobnie nie dożyje początku października. ,,No future'' pomyślała sobie i sięgnęła po kasetę The Exploited. A potem przypomniał się jej jeden z jej ulubionych punkowych numerów.

,,Wszyscy jedziemy na tym samym wózku,
od strachu ratuje nas tylko defekt mózgu''.

nuciła Partycja hit Defektu muzgó, ale przypomniała sobie, że jednak nie wszyscy jadą na tym samym wózku, bo wózki niektórych są nieco wygodniejsze. To jeszcze bardziej popsuło Partycji nastrój. Jednak, jako że w ciągu ostatnich kilku miesięcy Partycja przywykła do porządkowania wszystkiego, postanowiła zrobić porządek ze swoimi kasetami, żeby w razie potrzeby bez problemu odnaleźć ukochaną płytę.

Wejście:
W pierwszej linii wejścia program otrzymuje liczbę n oznaczającą liczbę operacji na bazie kaset a następnie n opisów operacji z poniższej listy

d – dodanie do bazy nowej kasety, w przypadku tej operacji w kolejnych dwóch liniach znajdowała się będzie nazwa zespołu i tytuł kasety.
w – wypisanie w osobnych liniach tytułów kaset podanego zespołu. Nazwa zespołu zostanie podana w kolejnej linii wejścia. Zespołu należy wypisywać w kolejności ich dodawania do bazy.
z– wypisanie w osobnych liniach zespołów, które nagrały kasetę o podanym tytule. Nazwa zespołu zostanie podana w kolejnej linii. Nazwy zespołów należy wypisywać w kolejności dodawania kaset o podanym tytule do bazy.
UWAGA: w zestawach mogą pojawić się linie, które nie pasują do powyższego wzorca (zamiast jednoznakowego symbolu polecenia mogą pojawić się dłuższe linie). Takie linie program powinien ignorować.

1<=n<=100000
Wyjście:
Na standardowym wyjściu program powinien wypisać efekty działania operacji w i z. W przypadku gdy w bazie nie ma zespołu o podanej nazwie (operacja w) lub kasety o podanym tytule (operacja z) program nie powinien niczego wypisać.

Przykładowe wejście:
5
d
Defekt muzgó
Wszyscy jedziemy...
d
Zielone żabki
Lekcja historii
d
Defekt muzgó
Lekcja historii
w 
Defekt muzgó
z
Lekcja historii
z
Wszyscy pokutujemy
Przykładowe wyjście:
Wszyscy jedziemy...
Lekcja historii
Zielone żabki
Defekt muzgó
Uwaga:
Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych drzew splay.
*/

#include <iostream>
#include <list>
#include <string>
#include <limits>

using namespace std;

struct Node {                               //struktura elementu drzewa
    string value;                           //wartość (klucz też) elementu
    Node *r_son, *l_son, *father;           //wskaźnik na prawego i lewego syna oraz ojca
    list<Node*> linked;                     //lista odwołań do drugiego drzewa
};

class SplayTree {                           //drzewo splay
    Node *root;                             //wskaźnik na korzeń drzewa
public:

    SplayTree() {                               //konstruktor drzewa
        root = nullptr;                         //brak korzenia
    }

    void left_rotation(Node *v) {                                       //lewa rotacja elementow w drzewie
            Node *right = v->r_son;                                     //wskaznik na prawego syna elementu
            
            v->r_son = right->l_son;                                    //prawy syn jest teraz lewym synem prawego syna
            if(v->r_son) v->r_son->father = v;                          //jezeli prawy syn istnieje
            right->father = v->father;                                  //ustawiamy prawemu synowi ojca 

            if(v->father) {                                             //jezeli ojciec elementu istnieje
                if(v == v->father->l_son) v->father->l_son = right;     //jezeli elment jest lewym synem ojca to lewym synem ojca jest prawy syn
                else v->father->r_son = right;                          //jezeli jest prawym synem to prawym synem jest prawy syn
            } else root = right;                                        //jezeli nie ma ojca to root staje sie prawym synem

            right->l_son = v;                                           //lewym synem prawego syna jest nasz element
            v->father = right;                                          //ojcem elementu jest prawy syn
        }

        void right_rotation(Node *v) {                                  //lewa rotacja elementow w drzewie
            Node *left = v->l_son;                                      //wszystko tak samo tylko na odwrotw
            
            v->l_son = left->r_son;
            if(v->l_son) v->l_son->father = v;
            left->father = v->father;

            if(v->father) {
                if(v == v->father->r_son) v->father->r_son = left;
                else v->father->l_son = left;
            } else root = left;

             left->r_son = v;
             v->father = left;
        }


    Node* add(string x) {                                                   //metoda dodająca element do drzewa
        Node *new_node = new Node{x, nullptr, nullptr, nullptr};            //tworzymy nowy element
        if(!root) {                                                         //jeżeli nie mamy jescze zadnego elementu w drzewie
            root = new_node;                                                //to nowy element jest korzeniem drzewa
        } else {                                                            //natomiast gdy mamy już korzeń drzewa to
            Node *curr = root;                                              //ustawiamy aktualny wskaźnik na korzeń
            while(true) {                                                   //dopóki nie dodamy elementu albo nie znajdziemy juz istniejacego
                if(x == curr->value) {                                      //gdy element istnieje
                    splay(curr);                                            //wywolujemy na nim splay
                    return curr;                                            //zwracamy go
                } else if(x < curr->value && !curr->l_son) {                //gdy nowy element jest mniejszy od aktualnego i aktualny nie ma syna
                    curr->l_son = new_node;                                 //to dodajemy nowy elment jako lewy syn
                    new_node->father = curr;                                //ustawiamy ojca nowemu elementowi
                    break;                                                  //koniec petli
                } else if(x < curr->value && curr->l_son) {                 //gdy nowy element jest mniejszy ale mamy juz syna
                    curr = curr->l_son;                                     //to przesuwamy sie w drzewie dla kolejnego obrotu petli
                } else if(x > curr->value && !curr->r_son) {                //gdy nowy element jest wiekszy od aktualnego i nie ma syna
                    curr->r_son = new_node;                                 //to nowy element jest prawym synem
                    new_node->father = curr;                                //ustawiamy ojca nowemu elementowi
                    break;                                                  //konczymy petle
                } else if(x > curr->value && curr->r_son) {                 //gdy nowy element jest wiekszy ale ma prawego syna
                    curr = curr->r_son;                                     //to przesuwamy sie po drzewie dla kolejnego obrotu petli
                }
            }
        }
        splay(new_node);                                                    //wywolujemy splay na nowym elemencie
        return new_node;                                                    //zwracamy nowy element
    }

    void add_list(Node* a, Node* b) {       //funkcja dodajaca do listy
        a->linked.push_back(b);             //dodajemy elementowi(np.zespolowi) element z drugiego drzewa(np.utwor)
    }

    Node* search(string key) {                  //funkcja szukajaca elementu po kluczu
        Node *n = root;                         //ustawiamy nasz aktualny element na root
        bool flag = false;                      //flaga pokazujaca czy znalezlismy element
        while(true) {                           //dopoki prawda
            if(n) {                             //jezeli element istnieje
                if(key == n->value) {           //jezeli znalezlismy klucz
                    break;                      //to wychodzimy z flaga false
                } else if(key < n->value) {     //jezeli klucz jest mniejszy od wartosci elementu
                    if(!n->l_son) {             //i lewy syn nie istnieje
                        flag = true;            //flaga na true
                        break;                  //i wychodzimy
                    }               
                    n = n->l_son;               //w przeciwnym przypadku przechodzimy do lewego syna
                } else {                        //gdy klucz jest wiekszy od wartosci
                    if(!n->r_son) {             //i prawy syn nie istnieje
                        flag = true;            //to ustawiamy flage
                        break;                  //i wychodzimy
                    }
                    n = n->r_son;               //jezeli nie to przechodzimy na prawego syna
                    }
            } else break;                       //gdy element nie istnieje to wychodzimy
        }
        if(n) splay(n);                         //jezeli element istnieje to wywolujemy splay na znalezionym kluczu lub elemencie przed
        if(flag || !n) return nullptr;          //jezezli flaga jest ustawiona lub element nie istnieje to zwracamy null
        else return n;                          //w przeciwnym przypadku zwracamy element    
    }

    void splay(Node* val) {                                         //funkcja splay, wykonujaca operacje naprawiajace drzewo
        while(true) {                                               //dopoki prawda
            if(val == root || !val->father) break;                  //gdy aktualny element jest korzeniem to wychodzimy

            if(val->father == root || !val->father->father) {       //--ZIG-- gdy ojciec jest korzeniem
                if(val->father->r_son == val)                       //gdy jestesmy prawym synem
                    left_rotation(val->father);                     //to lewa rotacja
                else                                                //gdy jestesmy lewym synem
                    right_rotation(val->father);                    //to prawa rotacja
                break;                                              //koniec                        //--ZIG ZIG-- 
            } else if(val->father->father->r_son == val->father && val->father->r_son == val) {     //gdy jestesmy prawym synem 
                left_rotation(val->father->father);                                                 //i nasz ojciec jest prawym synem
                left_rotation(val->father);                                                         //to dwie rotacje w lewo
            } else if(val->father->father->l_son == val->father && val->father->l_son == val) {     //gdy jestesmy lewym synem
                right_rotation(val->father->father);                                                //i nasz ojciec jest lewym synem
                right_rotation(val->father);                                                        //to dwie rotacje w prawo
            } else if(val->father->father->r_son == val->father && val->father->l_son == val) {     //--ZIG ZAG--
                right_rotation(val->father);                                                        //gdy jestesmy lewym synem
                left_rotation(val->father);                                                         //ii nasz ojciec jest prawym to prawa lewa rotacja
            } else if(val->father->father->l_son == val->father && val->father->r_son == val) {     //gdy jestesmy prawym synem 
                left_rotation(val->father);                                                         //a ojciec lewym
                right_rotation(val->father);                                                        //to lewa prawa rotacja
            }
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);                                       //magiczna linijka
    
    SplayTree titles;                                                       //drzewo splay przechowujace tytuly
    SplayTree names;                                                        //drzewo splay przechowujace nazwy zespolow

    int n;                                                                  //ilosc komend do wykonania
    cin >> n;

    string name, title, sg;                                                 //zmienne na nazwe, tytul, znak

    for(int i = 0; i < n; i++) {                                            //petla do wczytywania
        cin >> sg;                                                          //wczytujemy znak
        cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');   //ignorujemy spacje po cin
        if(sg == "d") {                                                     //jezeli dostaniemy d
            getline(cin, name);                                             //pobieramy linie z nazwa zespolu
            Node* a = names.add(name);                                      //dodajemy zespol
            getline(cin, title);                                            //pobieramy linie z tytulem piosenki
            Node *b = titles.add(title);                                    //dodajemy tytul do drzewa tytulow
            names.add_list(a, b);                                           //dodajemy zespolowi piosenke
            titles.add_list(b, a);                                          //piosence dodajemy zespol
        } else if(sg == "w") {                                              //jezeli dostaniemy w 
            getline(cin, name);                                             //pobieramy linie z nazwa
            Node* a = names.search(name);                                   //szukamy zespolu
            if(a) {                                                         //jezeli znalezlismy
                for(auto it : a->linked)                                    //to wyswietlamy jego wszystkie utwory
                    cout << it->value << endl;
            }
        } else if(sg == "z") {                                              //jezeli dostaniemy z
            getline(cin, title);                                            //pobieramy linie z tytulem
            Node* b = titles.search(title);                                 //szukamy go w drzewie tytulow
            if(b) {                                                         //jezeli isntieje
                for(auto it : b->linked)                                    //to wyswietlamy wszystkie zespoly grajace go
                    cout << it->value << endl;
            }
        }
    }

    return 0;
}