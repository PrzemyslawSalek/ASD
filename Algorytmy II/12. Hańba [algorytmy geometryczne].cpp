/*
Treść zadania
Ile można siedzieć w domu? Czego tu się bać jak planuje się żyć do jesieni? Partycja postanowiła kontestować otaczającą rzeczywistość i zaczęła chodzić na długie spacery (oczywiście w maseczce, bo co za dużo kontestowania to nie zdrowo). Odkryła też, że Julian Tuwim wielkim poetą był. A w tym odkryciu pomógł jej zespół Hańba, który fragmenty wiersza ,,Mój dzionek'' wyśpiewuje w piosence ,,Hoży i świeży''. O ironio! Broni ludzi inteligentnych. Zakrzyknęła Partycja i zaczęła śpiewać:

Le­d­wo sło­necz­ko ude­rzy
W okno zło­ci­stym pro­my­kiem,
Bu­dzę się hoży i świe­ży
Z an­ty­pań­stwo­wym okrzy­kiem.

W trakcie swych długich spacerów Partycja pokonuje wiele kilometrów. Nie wie niestety jak wiele bo ze względów bezpieczeństwa nie zabiera ze sobą telefonu (Wielki Brat patrzy!) i nie ma jak zapisywać swojej trasy. Wymyśliła więc sposób, jak w przybliżeniu oszacować pokonywany dystans. Raz na jakiś czas Partycja pyta przypadkowych przechodniów o współrzędne punktu w którym się znajdują. W ten sposób powstała baza punktów przez które przechodziła Partycja. Ponieważ Partycja nie zawsze chodzi tą samą trasą punkty nie układają się w jedną ścieżkę. Partycja chodzi dookoła swojego domu, który oznacza jako punkt (0,0). Chce od góry oszacować długość pokonywanej trasy i dlatego w przypadku wczytania wielu punktów znajdujących się na jednej półprostej o początku w punkcie (0,0) usuwa ze zbioru punktów wszystkie punkty leżące na tej półprostej poza punktem najbardziej odległym od początku układu współrzędnych (punktu (0,0)).

Wejście:
W pierwszej linii wejścia program otrzyma liczbę n punktów w zbiorze a następnie, n par liczb całkowitych opisujących współrzędne punktu w zbiorze.

1<=n<=100000
Wyjście:
Na standardowym wyjściu program powinien wypisać wczytane punkty uporządkowane względem amplitudy w ich reprezentacji w biegunowym układzie współrzędnych o biegunie w punkcie (0,0) i osi OX jako osi biegunowej. Spośród punktów o takiej samej amplitudzie powinien zostać wypisany tylko jeden, ten o największym promieniu wodzącym.

Przykładowe wejście:
6
0 0
1 2
2 1
5 0
-1 -2
4 2
Przykładowe wyjście:
5 0
4 2
1 2
-1 -2
*/

#include <iostream>
#include <cmath>
#include <map>

using namespace std;

double polar_radius(double x, double y) {       //~~~Oblicza promień wodzący~~~//
    return sqrt(pow(x,2) + pow(y,2));           //czyli odległość od punktu (0,0) do punktu (x,y)
}

double amplitude(double x, double y) {          //~~~Oblicza amplitude punktu (kąt do osi OX)~~~//
    if(x > 0 && y >= 0)                         //gdy x i y są większe od 0
        return atan(y/x);                       //liczby arctanges z y/x
    else if(x > 0 && y < 0)                     //gdy x jest większy a y mniejszy
        return atan(y/x) + 2.0*M_PI;            //arctanges(y/x) + 2*PI
    else if(x < 0)                              //gdy x jest mniejszy od 0
        return atan(y/x) + M_PI;                //arctanges(y/x) + PI
    else if(x == 0 && y > 0)                    //gdy x jest równy 0 a y większy od 0
        return M_PI/2.0;                        //PI/2
    else                                        //gdy x jest równy 0 a y mniejszy od 0
        return 3.0*M_PI/2.0;                    //3*PI/2
}

struct Node {                                   //~~~struktura na element mapy~~~//
    double x, y, r;                             //współrzędne punktu na układzie oraz promień wodzący
};

int main() {
    ios_base::sync_with_stdio(false);                   //magiczna linijka

    int n;                                              //ilość danych do wczytania
    double x, y;                                        //współrzedne punktu
    cin >> n;

    map<double, Node> points;                           //mapa na punkty (aby nie sortować)
    double r, fi;                                       //promień wodzący i amplituda punktu

    for(int i = 0; i < n; i++) {                        //wczytujemy n danych
        cin >> x >> y;                                  //wczytujemy współrzędne
        if(x == 0 && y == 0)                            //jeżeli mamy punkt (0,0)
            continue;                                   //to pomijamy go
        r = polar_radius(x, y);                         //obliczamy promień wodzący
        fi = amplitude(x, y);                           //obliczamy amplitude punktu
        if(points.find(fi) == points.end())             //gdy nie mamy takiego elementu w mapie
            points[fi] = Node{x, y, r};                 //to go dodajemy
        else                                            //gdy już jest taki element
            if(points[fi].r < r)                        //i jego r jest mniejsze od tego nowego punktu
                points[fi] = Node{x, y, r};             //to go podmieniamy
    }

    for(auto x : points)                                    //wyswietlamy wszystkie elementy mapy
        cout << x.second.x << " " << x.second.y << endl;    //posortowane według aplitudy (od najmniejszej)

    return 0;
}