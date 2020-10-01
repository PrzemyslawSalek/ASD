/*
Treść zadania
I znowu Partycję dopadł gorszy nastrój. Znowu widzi przyszłość w czarnych barwach. Wciąż wraca do niej to samo pytanie. Czy jej śledztwo ma jakiś sens? Przecież nie zmieni orbity pędzącej w stronę Ziemi asteroidy. A nawet jeżeli naukowcy się mylą i historia ludzkości nie skończy się jesienią, to przecież wszystko zmierza w złą stronę.

W takim nastroju Partycja przypomniała sobie jedejn ze swoich ulubionych teledysków z czasów młodości. Do the Evolution zespołu Pearl Jam. Kiedyś wizja przyszłości z teledysku wydawała jej się zbyt pesymistyczna. Teraz wydawała się ona być raczej aż nadto realistyczna. Partycja z rozrzewnieniem wspominała czasy, gdy takich utworów można było posłuchać w piątek wieczorem na jej ulubionej liście przebojów (że też nikt tego nie ocenzurował - przyszło do głowy Partycji). Przy okazji Partycja uświadomiła sobie, że jej bazę danych płyt i kaset trzeba poszerzyć o teledyski.

Specyfikacja wejścia i wyjścia oraz testy są identyczne jak w zadaniu 9.

Uwaga:
Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych tablic haszujących.
*/

#include <iostream>
#include <string>
#include <list>
#include <limits>

using namespace std;

struct Node {                   //---Struktura przechowująca napis i odwołanie do drugiej mapy---//
    string word;                //slowo
    list<Node*> linked;         //lista powiązań
};

class Hash_table {                                      //Tablica mieszająca (nie haszująca)
    list<Node*> *arr;                                   //tablica przechowująca listy
    int size;                                           //rozmiar tablicy
public:
    Hash_table(int size) : size(size) {                 //~~~Konstruktor tablcy~~~//
        arr = new list<Node*>[size];                    //inicjalizujemy tablice
    }

    int hash(string word) {                             //~~~Funkcja mieszająca~~~//
        int value = 0, a = 62830;                       //wartosc zwracana i przypadkowa liczba

        for(size_t i = 0; i < word.length(); i++) {     //przechodzimy calego stringa
            value = (word[i] + a*value)%size;           //obliczamy wartosc i modulujemy aby nie przekroczyło zakresu
            a = a*value%(size-3);                       //obliczamy a dla kolejnej litery
        }

        if(value < 0)                                   //moze sie zdarzyc ze wyjdzie liczba ujemna
            value += size;                              //wtedy dodajemy rozmiar do wartosci zwracanej

        return value;                                   //zwracamy wartosc
    }

    Node* search(string word) {             //~~~Funkcja szukajaca slowa w tablicy~~~//
        int index = hash(word);             //pobieramy indeks z funkcji haszującej

        for(auto x : arr[index]) {          //przegladamy elementy listy 
            if(x->word == word)             //jezeli znajdziemy nasz klucz
                return x;                   //to zwracamy ten element
        }
        return nullptr;                     //w przeciwnym przypadku zwracamy null
    }

    Node* insert(string word) {                 //~~~Funkcja dodawania elementu do tablicy~~~//
        int index = hash(word);                 //pobieramy indeks z funkcji haszującej
        Node *curr = search(word);              //szuakmy danego słowa przed dodaniem

        if(!curr) {                             //jeżeli go nie znajdziemy 
            Node *new_node = new Node;          //to tworzymy nowy element
            new_node->word = word;              //przypisujemy mu słowo
            arr[index].push_back(new_node);     //dodajemy do tablicy pod indeksem wyznaczonym przez f.mieszającą
            return new_node;                    //zwracamy ten element
        } else                                  //gdy element o takim kluczu już istniał
            return curr;                        //to go zwracamy bez dodawania
    }

    void add_list(Node* a, Node* b) {       //~~~Funkcja dodajaca do listy~~~//
        a->linked.push_back(b);             //dodajemy elementowi(np.zespolowi) element z drugiego drzewa(np.utwor)
    }

};


int main() {

    ios_base::sync_with_stdio(false);                                       //magiczna linijka

    int n;                                                                  //ilosc komend do wykonania
    cin >> n;

    Hash_table titles(n);                                                   //tworzymy tablice dla tytułów
    Hash_table names(n);                                                    //tworzymy tablice dla nazw

    string name, title, sg;                                                 //zmienne na nazwe, tytul, znak

    for(int i = 0; i < n; i++) {                                            //petla do wczytywania
        cin >> sg;                                                          //wczytujemy znak
        cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');   //ignorujemy spacje po cin
        if(sg == "d") {                                                     //jezeli dostaniemy d
            getline(cin, name);                                             //pobieramy linie z nazwa zespolu
            Node* a = names.insert(name);                                   //dodajemy zespol
            getline(cin, title);                                            //pobieramy linie z tytulem piosenki
            Node *b = titles.insert(title);                                 //dodajemy tytul do drzewa tytulow
            names.add_list(a, b);                                           //dodajemy zespolowi piosenke
            titles.add_list(b, a);                                          //piosence dodajemy zespol
        } else if(sg == "w") {                                              //jezeli dostaniemy w
            getline(cin, name);                                             //pobieramy linie z nazwa
            Node* a = names.search(name);                                   //szukamy zespolu
            if(a) {                                                         //jezeli znalezlismy
                for(auto it : a->linked)                                    //to wyswietlamy jego wszystkie utwory
                    cout << it->word << endl;
            }
        } else if(sg == "z") {                                              //jezeli dostaniemy z
            getline(cin, title);                                            //pobieramy linie z tytulem
            Node* b = titles.search(title);                                 //szukamy go w drzewie tytulow
            if(b) {                                                         //jezeli isntieje
                for(auto it : b->linked)                                    //to wyswietlamy wszystkie zespoly grajace go
                    cout << it->word << endl;
            }
        }
    }

    return 0;
}