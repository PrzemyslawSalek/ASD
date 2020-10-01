/*
Treść zadania
Partycja Logiczna nie do końca wierzy wynikom programów napisanych przez studentów (może dlatego, że jest wystarczająco stara, żeby pamiętać tworzenie systemu dla ZUS-u). Dlatego poprosiła o sprawdzenie wyników niezależnie napisanym programem. Żeby zabezpieczyć się na wypadek użycia przez kogoś tego samego programu ze zmienionymi nazwami zmiennych itp. postawiła warunek, że program musi wykorzystywać kopce Fibonacciego (Partycja wie, że nikt o zdrowych zmysłach nie implementuje kopców Fibonacciego o ile nie musi).

Wyślij program będący rozwiązaniem pierwszego zadania, ale używający kopców Fibonacciego i funkcji DecreaseKey.
*/

/*                  SIXTY HOURS LATER                  */               

#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <climits>
#include <math.h>

using namespace std;

class Fibonacci_heap {                          //~~~~kopiec fibonacciego (kolejka priorytetowa)~~~~
public:
    struct Node {                               //~~~~sturktur do kopca~~~~
        pair<int, int> value;                   //para (wartosc drogi AB, indeks postoju)
        bool loser;                             //loser lub mark do decrease_key
        Node *father;                           //wskaznik na ojca
        Node *son;                              //wskaznik na syn
        Node *next;                             //wskaznik na prawego brata
        Node *prev;                             //wskaznik na lewego brata
    };
private:
    int n_size;                                 //liczba wszystkich elementow (n)
    Node *head, *min;                           //wskaznik na glowe i element minimum
    Node **fast_indx;                           //tablica szybkiego dostepu z wskaznikami do elemntu pod indeksem
    int counter;                                //liczba korzeni
public:

    Fibonacci_heap(int n) {                     //~~~~konstruktor~~~~
        n_size = n;                             //liczba elementow
        counter=0;                              //licznik korzeni na 0
        fast_indx = new Node*[n_size];          //inicujemy tablice szybkiego dostepu
        for(int i = 0; i < n_size; i++) {
            fast_indx[i] = nullptr;             //czyscimy ją
        }
    }

    void push(pair<int, int> val) {                                                 //~~~~dodawanie elementu~~~~
        Node *p= new Node{val, false, nullptr, nullptr, nullptr, nullptr};          //tworzymy nowy element
        fast_indx[val.second] = p;                                                  //wpisujemy go do tablicy szybkiego dostepu
        if(counter==0) {                                                            //jezeli lista jest pusta
            head = p; min = p;                                                      //to nowy element jest glowa i minimum
        } else {                                                                    //jezeli mamy juz elementy w liscie
            if(min->prev == nullptr) head = p;                                      //to wpinamy go przed min
            else {
                min->prev->next = p; p->prev = min->prev;                           //wpinamy go przed min uwazajac zeby nie stracic innych elementow
            }
            min->prev = p; p->next = min;                                          
            if(p->value.first < min->value.first) min = p;                          //jezeli jest mniejszy od aktualnego min to staje sie min
        }
        ++counter;                                                                  //zwiekszamy licznik korzeni 
    }

    void push_node(Node *p, bool first_ele) {                   //~~~~dodawanie elementu (przyjmuje Node a nie pare jak wczesniej~~~~
        if(!first_ele) {                                        //gdy nie ma zadnego elementu w liscie
            head = p; min = p;                                  //to nasz element jest glowa i minimum
        } else {                                                //w innym przypadku wpinamy go przed minimum
            if(min->prev == nullptr) head = p;
            else {
                min->prev->next = p; p->prev = min->prev;
            }
            min->prev = p; p->next = min;
            if(p->value.first < min->value.first) min = p;      //jezeli jest mniejszy od minimum to staje sie minimum
        }
        counter++;                                              //licznik korzeni++
    }

    void consolidate() {                                                    //~~~~condolidate czyli funkcja laczaca elementy w drzewa~~~~                                              
        int size = int(log2(n_size));                                       //tablica w ktorej trzymamy wskaznik w indeksie = wysokosci drzewa
        Node **arr = new Node*[size];                                       //inicjujemy ja

        for(int i = 0; i < size; i++) {                                     //czyscimy ja
            arr[i] = nullptr;
        }

        int tree_size = 0;                                                  //wysokosc drzewa rowna 0

            while(head != nullptr) {                                        //dopoki glowa nie jest nullem(zawsze dzialamy na glowie)
                tree_size = 0;                                              //wysokosc drzewa 0 dla kolejnego obrotu petli
        
                Node* ts = head;
                while(ts->son != nullptr) {                                 //liczymy wysokosc drzewa
                    tree_size++;
                    ts = ts->son;
                }

                if(arr[tree_size] == nullptr) {                             //jezeli tablica jest pusta
                    arr[tree_size] = head;                                  //to wpinamy element do tablicy
                    if(head->next != nullptr) {                             //jezeli mamy nastepny element
                        head = head->next;                                  //to glowa jest teraz nastepny element
                        if(head->prev != nullptr) {                         //wypinamy poprzednia glowe
                            head->prev->prev = nullptr; 
                            head->prev->next = nullptr;
                        }
                        head->prev = nullptr;                               //usuwamy poprzednia glowe z listy
                    } else if(head->next == nullptr) {                      //jezeli nie ma nastepnego elementu
                        head = nullptr;                                     //to usuwamy ostatni element
                    }
                } else {                                                    //gdy mamy juz jakis element w tablicy
                    if(head->value.first < arr[tree_size]->value.first) {   //to jesli glowa jest mniejsza od elementu w tablicy
                        arr[tree_size]->next = nullptr;                     //usuwamy wskazniki na braci elementowi z tablicy
                        arr[tree_size]->prev = nullptr;                     
                        if(head->son == nullptr) {                          //jezeli nie ma synow
                            head->son = arr[tree_size];                     //to wpisujemy element z tablicy jako syn glowy
                            head->son->father = head;                       //glowie wpisujemy nowego syna
                            arr[tree_size] = nullptr;                       //usuwamy element z tablicy (jest teraz synem glowy)
                        } else if(head->son != nullptr) {                   //jezeli ma synow
                            Node *n = head->son;                            //przypisujemy sobie syna do chwilowego wskaznika
                            head->son = arr[tree_size];                     //synem staje sie element z tablicy
                            head->son->father = head;                       //synowi pokazujemy ze ma ojca
                            arr[tree_size] = nullptr;                       //czyscimy tablice
                            head->son->next = n;                            //przypisujemy synowi jako brata poprzedniego syna
                            head->son->prev = nullptr;                      //czyscimy synowi poprzednika
                            head->son->next->prev = head->son;              //wskazujemy bratowi syna ze ma lewego brata
                        }
                    } else {                                                //gdy element w tablicy jest mniejszy od glowy
                        Node *m = head;                                     //glowe przypisujemy sobie do chwilowego wskaznika
                        head = arr[tree_size];                              //glowa staje sie element z tablicy
                        head->next = nullptr; head->prev = nullptr;         //czyscimy nowej glowie poprzednik i nastepnik
                        if(m->next != nullptr) {                            //jezeli stara glowa ma nexta
                            head->next = m->next; head->next->prev = head;  //to wpinamy nowa glowe w miejsce starej
                        }
                        if(head->son == nullptr) {                          //jezeli glowa nie ma syna
                            head->son = m;                                  //to synem staje sie stara glowa
                            head->son->father = head;                       //reszta tak samo robimy
                            head->son->next = nullptr;
                            head->son->prev = nullptr;
                            arr[tree_size] = nullptr;
                        } else if(head->son != nullptr) {                   //jezeli glowa ma synow
                            Node *n = head->son;                            //to synow przypinamy do uchwytu na chwile
                            head->son = m;                                  //a synem staje sie stara glowa
                            head->son->father = head;                       
                            arr[tree_size] = nullptr;                       //czyscimy tablice pod indeksem
                            head->son->next = n;                            //przypinamy synowi jako bracia starych synow
                            head->son->prev = nullptr;
                            n->prev = head->son;                            //i mowimy braciom ze maja nowego syna
                        }
                    }
                }
            }

            head = nullptr; min = nullptr;                                  //czyscimy min i head
            counter = 0;                                                    //counter na 0
            bool first_element = false;                                     //flaga dla pierwszego elementu
            for(int i = 0; i < size; i++) {                                 //i tworzymy nowa liste z elementow w tablicy
                if(arr[i] != nullptr) {
                    push_node(arr[i], first_element);
                    first_element = true;
                }
            }
    }

    void pop() {                                                                //~~~~funkcja usuwajaca element z listy~~~~
        
        if(fast_indx[min->value.second] != nullptr)                             //jezeli jest w tablicy to (sprawdzamy dla pewnosci)
            fast_indx[min->value.second] = nullptr;                             //usuwamy go z tablicy szybkiego dostepu
        
        if(counter == 1 && min->son == nullptr) {                               //jezeli jest to ostatni element listy i nie ma synow
            min = nullptr; head = nullptr;                                      //usuwamy go z listy
            counter--;                                                          //zmniejszamy licznik korzeni
        } else if(min->son == nullptr) {                                        //jezeli element nie ma synow
            if(min->prev == nullptr) head = min->next;                          //jezeli jest glowa to glowa staje sie element nastepny
            if(min->prev != nullptr) min->prev->next = min->next;               //jezeli ma poprzednik to poprzednik o nim zapomina
            if(min->next != nullptr) min->next->prev = min->prev;               //jezeli ma nastepnik to nastepnik o nim zapomina
            min = head;                                                         //minimum staje sie na chwile glowa
            counter--;                                                          //zmniejszamy licznik korzeni 
        } else if(min->son->next == nullptr) {                                  //jezeli ma tylko jednego syna
            min->son->father = nullptr;                                         //to synowi usuwamy ojca
            Node *n = min;                                                      //zapamietujemy nasz element
            if(min->prev == nullptr && min->next != nullptr) head = min->next;  //jezeli jest glowa to glowa staje sie kolejny elment
            else if(min->prev == nullptr && min->next == nullptr) {             //jezeli jest ostatnim korzeniem
                min = n->son;                                                   //to minimum staje sie syn
                head = min;                                                     //glowa staje sie syn
                return;                                                         //koniec
            }
            if(min->prev != nullptr) min->prev->next = min->next;               //jezeli ma poprzednika to poprzednik o nim zapomina
            if(min->next != nullptr) min->next->prev = min->prev;               //jezeli ma nastepnik to nastepnik o nim zapomina
            min = head;                                                         //minimum staje sie chwilowo glowa

            if(min->next != nullptr) {                                          //wpinamy syna do listy jako korzen
                min->next->prev = n->son; 
                n->son->next = min->next;
            }
            min->next = n->son; n->son->prev = min;
        } else if(min->son->next != nullptr) {                                  //jezeli element ma wielu synów
            Node *n = min;                                                      //zapamietujemy go w jakims uchwycie
            if(min->prev == nullptr && min->next != nullptr) head = min->next;  //jezeli ejst glowa to nastepny element staje sie glowa
            else if(min->prev == nullptr && min->next == nullptr) {             //hezeli jest ostatnim korzeniem to
                min = n->son;                                                   //syn staje sie min i korzeniem
                head = min;
                return;
            }
            if(min->prev != nullptr) min->prev->next = min->next;               //jezeli ma poprzednika to poprzednik o nim zapomina       
            if(min->next != nullptr) min->next->prev = min->prev;               //jezeli ma nastepnik to nastepnik o nim zapomina
            min = head;                                                         //minimum staje sie chwilowo glowa

            Node *r_son = n->son;                                               //szukamy skrajnie prawego syna
            do{
                r_son->father = nullptr;                                        //usuwamy im przy okazji ojcow
                r_son = r_son->next;
            } while(r_son->next != nullptr);

            if(min->next != nullptr) {                                          //wpinamy wszystkich synow do listy korzeni
                min->next->prev = r_son; r_son->next = min->next;
            }
            min->next = n->son; n->son->prev = min;


            Node *s = head; counter = 0;                                        //liczymy ile mamy korzeni
            while(s != nullptr) {                                               // (bo nie wiadomo ile synow dodalismy jako korzenie)
                counter++;
                s = s->next;
            }

        }

        consolidate();                                                          //tworzymy kopce z korzeni

        if(counter != 0) {                                                      //szukamy nowego minimum
            Node *n = head;
            do {
                if(n->value.first < min->value.first) min = n;
                n = n->next;
            } while(n != nullptr);
        }

    }

    void decrease_key(int index, int new_val) {                                     //~~~~funkcja podmieniajaca wartosc isntniejacemu elementowi~~~~
    
        if(fast_indx[index] == nullptr) {                                           //jezeli element nie istnieje              
            push(make_pair(new_val, index));                                        //to po prostu dodajemy go do listy
        } else {                                                                    //jezeli nie istnieje 
            Node *curr = fast_indx[index];                                          //to pobieramy go z tablicy szybkiego dostepu
            if(curr->value.first > new_val) {                                       //sprawdzamy czy nowa wartosc jest mniejsza od starej
                curr->value.first = new_val;                                        //jezeli tak to podmieniamy
            } else return;                                                          //w innym przypadku konczymy zabawe
            while(true) {                                                           //dopoki jest co robic
                if(curr->father == nullptr) break;                                  //jezeli nasz element nie ma ojca to wychodzimy
                else {                                                              //w innym przypadku
                    if(curr->value.first > curr->father->value.first) break;        //jezeli ojciec ma mniejsza wartosc to wychodzimy (wlasnosc kopca)
                    else {                                                          //w innym przypadku
                        Node *fat = curr->father;                                   //zapamietujemy ojca

                        if(curr->prev == nullptr && curr->next == nullptr) {        //jezeli nasz element jest jedyny
                           curr->father->son = nullptr;                             //to usuwamy jego ojcowi syna
                           curr->father = nullptr;                                  //i nasz element zapomina ojca
                        } else if(curr->prev == nullptr && curr->next != nullptr) { //jezeli element jest pierwszy i ma nastepniki
                           curr->father->son = curr->next;                          //to synem ojca jest nastepnik poprzedniego syna
                           curr->next->prev = nullptr; curr->next = nullptr;        //reszta zapomina o sobie
                           curr->father = nullptr;
                        } else if(curr->prev != nullptr && curr->next != nullptr) { //jezeli element jest w srodku
                            curr->next->prev = curr->prev;                          //to go wypinamy ze srodka 
                            curr->prev->next = curr->next;
                            curr->next = nullptr; curr->prev = nullptr;             //i wszyscy o nim zapominaja
                            curr->father = nullptr;
                        } else if(curr->prev != nullptr && curr->next == nullptr){  //jezeli element jest ostani
                            curr->prev->next = nullptr;                             //to wszyscy o nim zapominaja
                            curr->next = nullptr; curr->prev = nullptr;
                            curr->father = nullptr;
                        }

                        if(head->next != nullptr) {                                 //teraz wpinamy nasz element do listy korzeni
                            curr->next = head->next;                                //jako nastepnik glowy
                            head->next->prev = curr;
                            head->next = curr; curr->prev = head;
                            counter++;
                        } else {
                            head->next = curr;
                            curr->prev = head;
                            counter++;
                        }

                        if(curr->value.first < min->value.first) curr = min;        //jezeli nasz element jest mniejszy od akt minimum to jest nowym min

                        if(fat->loser == false) fat->loser = true;                  //jezeli to pierwsza utrara syna to ustawiamy ojca jako przegryw
                        else {                                                      //jezeli to kolejna utrata
                            curr = fat;                                             //to ojciec juz nie jest przegrywem ale naszym aktualnhym elementem
                            fat->loser = false;                                     //i zabawa trwa dalej (pseudo rekurencja) 
                        }

                    }
                }
            }
        }
    }

    bool empty() {                          //~~~~funkcja zwracajaca czy lista jest pusta~~~~
        return counter == 0;
    }

    pair<int, int> top() {                  //~~~~funkcja zwracajaca minimum~~~~
        if(!empty()) return min->value;
    }
};


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

    Fibonacci_heap p_que(n);                                                        //kolejka priorytowa fibonacciego na indeksy elementów

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
                p_que.decrease_key(x, stress[x]);                                   //i dodajemy do kolejki lub zamieniamy wartosc elementu
            }
        }
        if(top_val == d) break;                                                     //gdy dojdziemy do punktu ktory nas intersuje to przerywamy
    }

    cout << stress[d] << endl;                                                      //wyswietlamy wynik


    return 0;
}