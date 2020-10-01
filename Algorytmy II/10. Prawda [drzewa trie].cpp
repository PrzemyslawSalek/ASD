/*
Treść zadania
Słuchanie punkowych piosenek może przybitego człowieka pogrążyć jeszcze bardziej. Są jednak również utwory, które motywują do działania. Partycja w trakcie porządków dotarła do płyty zespołu Prawda i utworu Walcz!.

,,Jest jedna droga - wstań i walcz!
Wstań i walcz z uniesioną głową.'

krzyczy ostatnio na całe mieszkanie Partycja i nie może się doczekać kiedy sytuacja epidemiologiczna pozwoli na bardziej zdecydowane działania. Partycja uświadomiła sobie też, że jeżeli chce w swojej bazie danych przechowywać nie tylko kasety, ale także płyty, to musi zbudować bardziej wydajny system. Zaczęła więc eksperymentować z drzewami trie.

Specyfikacja wejścia i wyjścia oraz testy są identyczne jak w zadaniu 9.

Uwaga:
Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych skompresowanych drzew trie.
*/

#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <string>

using namespace std;

struct Node {                       //---Element drzewa Trie---//
    string full_word;               //fragment tekstu który przechowuje element
    bool isEnd = false;             //czy kończy wyraz/posiada print_word
    map<char, Node*> childs;        //dzieci elementu według ich pierwszej litery z full_word
    list<Node*> linked;             //lista łącząca oba drzewa
    string print_word;              //cały wyraz przechowywany przez element(do wyświetlenia)
};

class Compressed_Trie {             //---Skompresowane drzewo Trie---//
    Node *root;                     //korzeń drzewa
public:
    Compressed_Trie() {             //~~~Konstruktor~~~//
        root = new Node;            //ustawiamy root jako pusty element
    }

    void add_list(Node* a, Node* b) {       //~~~Funkcja dodajaca do listy~~~//
        a->linked.push_back(b);             //dodajemy elementowi(np.zespolowi) element z drugiego drzewa(np.utwor)
    }

    Node* add(string word) {                        //~~~Funckja dodająca element do drzewa~~~//
        if(!root->childs[word[0]]) {                //Gdy root nie ma takiego syna
            Node *new_node = new Node;              //tworzymy nowy element
            new_node->full_word = word;             //ustawiamy mu full_word na word
            new_node->print_word = word;            //print_word tak samo
            new_node->isEnd = true;                 //ustawiamy że posiada element do wyświetlenia
            root->childs[word[0]] = new_node;       //ustawiamy go jako syn root
            return new_node;                        //zwracamy go
        } else {                                    //Gdy root ma już taki element
            Node *curr = root->childs[word[0]];     //tworzymy sobie element curr
            Node *prev = root;                      //i poprzednik
            size_t sizeWord = 0;                    //licznik przechodzenia po word
            while(sizeWord < word.length()) {       //dopóki licznik word jest mniejszy od długości word
                size_t size = 0, num = sizeWord;    //rozmiar full_word w aktualnym elemencie i num przechowujacy poprzedni sizeWord

                for(size_t i = num; i < word.length(); i++) {                           //sprawdzamy ile szukanego slowa 
                    if(curr->full_word[size] && word[i] == curr->full_word[size]) {     //zgadza sie z full_word aktualnego
                        size++;                                                         //licznik full_word++
                        sizeWord++;                                                     //licznik word
                    } else                                                              //gdy sie nie zgadza jakis znak
                        break;                                                          //to konczymy petle
                }

                if(word.length() == sizeWord && curr->full_word.length() == size) {     //gdy zgadza się cały word z full_word
                    curr->print_word = word;                                            //to ustawiamy print_word
                    curr->isEnd = true;                                                 //zaznaczamy ze element przechowuje koniec wyrazu
                    return curr;                                                        //zwracamy ten elemet
                } else if(word.length() == sizeWord) {                                  //gdy full_word jest dluzszy od word np. w = Ala f_w = Alan
                    Node *new_node = new Node;                                          //tworzymy nowy element

                    string splited_end = "";                                            //wyciagamy z full_word koncowke czyli to n z Alan
                    for(size_t i = size; i < curr->full_word.length(); i++)
                            splited_end += curr->full_word[i];

                    string splited_start = "";                                          //wycigamy poczatek czyli Ala
                    for(size_t i = 0; i < size; i++)
                        splited_start += curr->full_word[i];

                    new_node->full_word = splited_start;                                //ustawiamy nowemu elem full_word na Ala
                    new_node->print_word = word;                                        //ustawiamy wartosc do wyswietlenia
                    new_node->isEnd = true;                                             //ustawiamy ze przechowuje taka wartosc

                    curr->full_word = splited_end;                                      //aktualnego elementowi koncowke ustawiamy na full_word

                    prev->childs[word[num]] = new_node;                                 //zastepujemy aktualny element nowym
                    new_node->childs[splited_end[0]] = curr;                            //a aktualny element staje sie synem nowego

                    return new_node;
                } else if(curr->full_word.length() == size) {                   //gdy nowy wyraz jest dluzszy od aktualnego np w = Jak f_w = Ja
                    if(!curr->childs[word[sizeWord]]) {                         //gdy element nie ma takiego syna
                        Node *new_node = new Node;                              //tworzymy nowy element
    
                        string splited_end = "";                                //wyciagamy koncowke z Jak czyli k
                        for(size_t i = sizeWord; i < word.length(); i++)    
                                splited_end += word[i];

                        new_node->full_word = splited_end;                      //ustawiamy nowemu elementowi koncowke
                        new_node->print_word = word;                            //ustawiamy wartosc do wyswietlenia
                        new_node->isEnd = true;                                 //ustawiamy ze przechowuje taka wartosc

                        curr->childs[word[sizeWord]] = new_node;                //ustawiamy go jako syna aktualnego elementu
                        return new_node;                                        //zwracamy go
                    } else {                                                    //gdy taki syn istnieje
                        prev = curr;                                            //to prevem jest teraz curr
                        curr = curr->childs[word[sizeWord]];                    //a curr jest ten syn
                    }
                } else {                                                        //gdy mamy sytuacje gdzie sa wyrazy typu w = Mak f_w = Mam
                    string splited_end = "";                                    //wyciagamy koncowke z aktualnego
                    for(size_t i = size; i < curr->full_word.length(); i++)
                            splited_end += curr->full_word[i];

                    string splited_end2 = "";                                   //wyciagamy koncowke z dodawanego
                    for(size_t i = sizeWord; i < word.length(); i++)
                            splited_end2 += word[i];

                    string splited_start = "";                                  //i wspolny poczatek z aktualnego
                    for(size_t i = 0; i < size; i++)
                        splited_start += curr->full_word[i];

                    Node* new_node = new Node;                                  //tworzymy nowy element
                    new_node->full_word = splited_start;                        //ustawiamy mu poczatek wyrazu
                    new_node->isEnd = false;                                    //i ze nie przechowuje konca wyrazu

                    Node* new_node2 = new Node;                                 //tworzymy nowy element
                    new_node2->full_word = splited_end2;                        //ustawiamy mu koniec nowego wyrazu
                    new_node2->isEnd = true;                                    //ustawiamy ze przechowuje print_word
                    new_node2->print_word = word;                               //ustawiamy print_word

                    curr->full_word = splited_end;                              //aktalnemu elmenetowi zmieniamy na koniec aktualnego

                    new_node->childs[splited_end[0]] = curr;                    //teraz nowemu elementowi ustawiamy aktualny jako syna
                    new_node->childs[splited_end2[0]] = new_node2;              //i drugi nowy jako syn
                    prev->childs[word[num]] = new_node;                         //a pierwszy nowy wstawiamy w miejsce aktaulnego

                    return new_node2;                                           //i zwracamy drugiego nowego
                }
            }
        }
    }

    Node* search(string word) {                 //~~~Funkcja szukająca elementu w drzewie po kluczu~~~//
        if(!root->childs[word[0]])              //jezeli nie ma takiego syna 
            return nullptr;                     //to zwracamy null

        Node *curr = root->childs[word[0]];     //w przeciwnym przypadku
        size_t sizeWord = 0;                    //ustawiamy wszystko tak jak w dodawaniu elementu
        while(sizeWord < word.length()) {
            size_t size = 0, num = sizeWord;

            for(size_t i = num; i < word.length(); i++) {                           //sprawdzamy ile nowego wyrazu zgadza sie z aktualnym
                if(curr->full_word[size] && word[i] == curr->full_word[size]) {
                    size++;
                    sizeWord++;
                } else
                    break;
            }
            
            if(sizeWord == word.length()) {                             //Jezeli przeszlismy caly nowy wyraz
                if(size == curr->full_word.length() && curr->isEnd)     //oraz aktualny i przechowuje print_word
                    return curr;                                        //to zwracamy aktualny
                else                                                    //w przeciwnym przypadku
                    return nullptr;                                     //zwracamy null
            } else if(size == curr->full_word.length()) {               //jezeli przeszlismy caly aktaulny ale nowego nie
                if(!curr->childs[word[sizeWord]])                       //to sprawdzamy czy syn istnieje
                    return nullptr;                                     //jezeli nie to null
                else                                                    //jezeli tak
                    curr = curr->childs[word[sizeWord]];                //to aktualnym elementem jest syn
            } else                                                      //gdy nie przeszlismy ani tego ani tego
                return nullptr;                                         //to zwracamy null
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);                                       //magiczna linijka

    Compressed_Trie titles;                                                 //drzewo splay przechowujace tytuly
    Compressed_Trie names;                                                  //drzewo splay przechowujace nazwy zespolow

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
                    cout << it->print_word << endl;
            }
        } else if(sg == "z") {                                              //jezeli dostaniemy z
            getline(cin, title);                                            //pobieramy linie z tytulem
            Node* b = titles.search(title);                                 //szukamy go w drzewie tytulow
            if(b) {                                                         //jezeli isntieje
                for(auto it : b->linked)                                    //to wyswietlamy wszystkie zespoly grajace go
                    cout << it->print_word << endl;
            }
        }
    }

    return 0;
}