/*
Treść zadania
Do siedziby operacyjnej Partycji dotarła wiadomość od jednego z jej tajnych informatorów. Miał do przekazana bardzo obiecujące informacje, który mogły w znacznym stopniu przyczynić się do ujawnienia rządowego spisku. Podał miejsce spotkania, jednak zastrzegł, by po mieście poruszać się z dużą ostrożnością i unikać monitorowanych miejsc.

Partycja zaczęła studiować mapę miasta, o wymiarach nxm. Podzieliła ją na n rzędów i m kolumn, a każdy tak powstały fragment mapy oznaczyła w następujący sposób:

. - miejsce z możliwością przejazdu
# - miejsce zablokowane bez możliwości przejazdu
M - miejsce z możliwością przejazdu, monitorowane
S - siedziba operacyjna
X - miejsce spotkania
Na początku postanowiła wyznaczyć najkrótszą drogę z siedziby do miejsca spotkania i sprawdzić ile miejsc monitorowanych się na tej drodze znajduje. Przez najkrótszą drogę rozumiana jest liczba miejsc odwiedzonych pomiędzy siedzibą a miejscem spotkania. Po mapie z danego miejsca można się poruszać na sąsiadujące pola w górę, w dół, lewo lub prawo (o ile pola te nie są zablokowane). W przypadku znalezienia więcej niż jednej najkrótszej drogi o tej samej długości, pierwszeństwo ma ta z mniejszą liczbą miejsc monitorowanych.

Wejście
W pierwszej linii wejścia znajdują się dwie liczby naturalne n i m, oznaczające wymiary mapy. W kolejnych liniach znajduje się reprezentacja mapy zgodna z opisem. Należy przyjąć, że zawsze istnieje droga prowadząca od siedziby do miejsca spotkania.

1 ≤ n,m ≤ 1000
Wyjście
Na wyjściu program ma wypisać dwie liczby naturalne oznaczające długość najkrótszej drogi do punktu docelowego oraz liczbę napotkanych miejsc monitorowanych.

Przykład
Wejście:
5 8
#..M.M#X
S..##...
.#.M...#
...#.#.#
####..M#


Wyjście:
10 1
*/

#include <iostream>
#include <queue>

using namespace std;

//struktura dla elementu grafu//
struct Element {
    char value;             //znak na mapie
    int counter = 0;        //liczba krokow
    int counterM = 0;       //liczba miejsc monitorowanych po drodze
};


class Graph {

    Element **matrix;       //nasza macierz
    int heig;               //wysokosc
    int wid;                //szerokosc
    int startX, startY;     //wspolrzedne startu
    int endX, endY;         //wspolrzedne konca

public:

    //konstruktor//
    Graph(int n, int m) {                   //przyjmuje wysokosc i szerokosc
        heig = n+2; wid = m+2;              //powiekszamy o 2 dla obudowy z '#'
        matrix = new Element*[heig];
        for(int i = 0; i < wid; ++i) {
            matrix[i] = new Element[wid];
        }
    }
    
//destruktor//
//    ~Graph() {
//        for(int i = 0; i < wid; ++i)
//            delete[] matrix[i];
//        delete[] matrix;
//    }

    //funkcja dodajaca elementy//
    void add() {
        char value;

        for(int i = 0; i < heig; ++i) {
            for(int j = 0; j < wid; ++j) {
                if(i == 0 || j == 0 || i == heig-1 || j == wid-1) {     //tworzymy obudowe
                    value = '#';
                } else {                        //dodajemy elementy do dwuwymiarowej tablicy struktury
                    cin >> value;
                    if(value == 'S') {              //gdy jest startem
                        startX = i; startY = j;
                        value = '.';
                        matrix[i][j].counter = -1;      //zaczynamy od -1 zeby go ominac w dalszej czesci
                    }
                    if(value == 'X') {              //gdy jest koncem
                        endX = i; endY = j;
                        value = '.';
                    }
                }
                matrix[i][j].value = value;         //przypisujemy wartosc do tablicy
            }
        }
    }

    //funkcja przeszukujaca//
    void findX() {
        queue<int> Que;     //tworzymy kolejke

        int line, column;

        Que.push(startX); Que.push(startY);     //dodajemy wiersz i kolumne do kolejki

        while(!Que.empty()) {
            line = Que.front(); Que.pop();          //pobieramy wartosci ustawiamy jako wiersz
            column = Que.front(); Que.pop();        //i kolumna, usuwamy

            if(line == endX && column == endY) break;   //gdy dojdziemy do konca

            for(int i = -1; i <=1; ++i) {           //petle ktore daja 10 01 -10 0-1
                for(int j = -1; j <=1; ++j) {       //oszczednosc 60 linijek
                    if(i != j && (i==0 || j==0)) {  //warunki dajace nam nasze 4 przesuniecia
                        if(matrix[line+i][column+j].counter == 0 && matrix[line+i][column+j].value != '#') {    //gdy jest nieodwiedzony i rozny od '#'
                            if(matrix[line+i][column+j].value == 'M') {     //kiedy miejsce jest monitorowane
                                matrix[line+i][column+j].counterM = matrix[line][column].counterM+1;    //dodajemy do licznika
                            } else matrix[line+i][column+j].counterM = matrix[line][column].counterM;   //inaczej przepisujemy licznik
                            matrix[line+i][column+j].counter = matrix[line][column].counter+1;          //dodajemy krok
                            Que.push(line+i);       //do kolejki element odwiedzony
                            Que.push(column+j);
                        } else if((matrix[line+i][column+j].counter == matrix[line][column].counter+1) && matrix[line+i][column+j].value != '#') {  //gdy jest nieodwiedzony a ma tyle samo krokow
                            if(matrix[line+i][column+j].counterM > matrix[line][column].counterM) { //jezli liczba miejsc monitorowanych jest mniejsza
                                matrix[line+i][column+j].counterM = matrix[line][column].counterM;  //przepisujemy
                                if(matrix[line+i][column+j].value == 'M')   //gdy miejsce jest monitorowane
                                    matrix[line+i][column+j].counterM = matrix[line][column].counterM+1;    //to musimy je dodac zeby obliczenia sie zgadzaly
                            }
                        }
                    }
                }
            }
        }
        cout << matrix[endX][endY].counter+1 << " " << matrix[endX][endY].counterM << endl;     //wyswietlanie wyniku
    }

//    void print(){
//        for(int i = 0; i < heig; i++) {
//            for(int j = 0; j < wid; j++) {
//                cout << matrix[i][j].value << " ";
//            }
//            cout << endl;
//        }
//    }

};



int main() {
    ios_base::sync_with_stdio(false);

    int n, m;

    cin >> n >> m;

    Graph graph(n,m);

    graph.add();

    graph.findX();

//    graph.print();

    return 0;
}