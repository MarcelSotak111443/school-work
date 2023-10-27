/*
Meno a priezvisko:

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (dopleny o riesenia).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <deque>
#include <algorithm>
#include <limits>

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Upravte definiciu metody 'T::met()' tak, aby informovala, ze metoda nemeni stav objektu.

    Pre kontrolu odkomentujte riadok v testovacej funkcii. Odkomentovany riadok musi byt kompilovatelny.
*/

class T {
public:
    void met() const{}
};

void testUloha1() {
    cout << "----- 1. uloha (metoda nemeni stav objektu) ------------------------------------" << endl;
    const T o;
    o.met(); // odkomentujte
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Upravte definiciiu konstruktora tak, aby bol konverznym konstruktorom.

    Zakomentovane riadky v testovacom kode musia byt kompilovatelne.
*/

class Number {
private:
    int number;
public:
    Number(int value) : number(value){
    }
    int getValue() const {
        return number;
    }
};

void fun(Number n) {
    cout << n.getValue() << endl;
}

void testUloha2() {
    cout << "----- 2. uloha (konverzny konstruktor) -----------------------------------------" << endl;

    Number a = 10; // ak existuje zodpovedajuci konverzny konstruktor, tak je tento riadok kompilovatelny
    cout << a.getValue() << endl;

    fun(20); // ak existuje zodpovedajuci konverzny konstruktor, tak je tento riadok kompilovatelny
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvorte triedu 'B', ktora je podtriedou triedy 'A'.
    Upravte definiciu metody 'A::met()' a definujte metodu 'B::met()' tak,
    aby bol testovaci kod po odkomentovani uspesne vykonany (aby bola vzdy volana spravna metoda).
*/

class A {
public:
    virtual char met() const {
        return 'a';
    }
};

class B:public A{
public:
    char met() const override{
        return 'b';
    }
};

void testUloha3() {
    cout << "----- 3. uloha (volanie spravnej metody) ---------------------------------------" << endl;
    A a;
    B b;

    A *pa  = &a;
    A *pab = &b;
    B* pb  = &b;

    assert(pa->met()  == 'a'); // volanie A::met()
    assert(pab->met() == 'b'); // volanie B::met()
    assert(pb->met()  == 'b'); // volanie B::met()
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Upravte definicie destruktorov tried 'C' a 'D' tak, aby sa v testovacej funkcii zavolal spravny destruktor.
    Testovacia funkcia musi namiesto:
        C::~C()
    po uprave vypisat:
        D::~D()
        C::~C()
*/

class C {
public:
    virtual ~C() {

        cout << "C::~C()" << endl;
    }
};

class D : public C {
public:
    ~D ()override{
        cout << "D::~D()" << endl;
    }
};

void testUloha4() {
    cout << "----- 4. uloha (volanie spravneho destruktora) ---------------------------------" << endl;
    C *obj = new D;
    delete obj; // aby sa zavolal spravny detruktor
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvorte operator +=, ktory bude sluzit pre pripocitanie druheho komplexneho cisla ku prvemu.
    Operator definujte ako clena triedy.

    Pre kontrolu odkomentujte riadky v testovacom kode, kde je priklad pouzitia operatora.
*/

class Complex {
private:
    int real;
    int imaginary;
public:
    Complex (int realPart, int imaginaryPart)
            : real(realPart)
            , imaginary(imaginaryPart) {
    }

    int getRealPart() const {
        return real;
    }
    int getImaginaryPart() const {
        return imaginary;
    }
    Complex & operator+=(const Complex &rhs){
        this->real += rhs.real;
        this->imaginary += rhs.imaginary;
        return *this;
    }

};

void testUloha5() {
    cout << "----- 5. uloha (operator +=) ---------------------------------------------------" << endl;

    Complex a(1,2);
    Complex b(10, 20);
    Complex c(100, 200);

    c += b += a;

    assert(a.getRealPart() == 1);
    assert(a.getImaginaryPart() == 2);
    assert(b.getRealPart() == 11);
    assert(b.getImaginaryPart() == 22);
    assert(c.getRealPart() == 111);
    assert(c.getImaginaryPart() == 222);
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvorte operator <<, ktory zapise hodnotu objektu triedy 'Complex' (z predchadzajuceho prikladu)
    do textoveho prudu dat.
    Poznamka: Operator musi byt definovany ako globalny.

    Pre kontrolu odkomentujte riadky v testovacom kode.
*/

inline ostream& operator<<(ostream& os, const Complex& complex){
    if (complex.getImaginaryPart() > 0) {
        os << complex.getRealPart() << "+" << complex.getImaginaryPart() << "i";
    }
    else {
        os << complex.getRealPart()  << complex.getImaginaryPart() << "i";
    }
    return os;
}

void testUloha6() {
    cout << "----- 6. uloha (operator << ) --------------------------------------------------" << endl;

    Complex a( 1, 2);
    Complex b(-3,-4);
    cout << "a = " << a << ", b = " << b << endl;

    ostringstream stream;
    stream << a << " " << b;
    assert(stream.str() == "1+2i -3-4i");
}

//=================================================================================================
// STROM - definicia pre dalsie ulohy
//=================================================================================================

// Uzol stromu
struct Node {
    char value; // hodnota uzla
    list<Node*> children; // zoznam nasledovnikov

    explicit Node(char value) : value(value) {}
};

// Strom
struct Tree {
    Node * root; // koren stromu

    explicit Tree(Node *root = nullptr) : root(root) {}
};
Node *newNode(char key)
{
    Node *temp = new Node{key};
    return temp;
}
//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam vsetkych hodnot uzlov v strome 'tree', ktorych hodnotou je velke pismeno.
    Pouzite algoritmus hladania DO HLBKY (styl pre-order).
    Pouzite iterativnu implementaciu.
    Doporucenie: pre identifikaciu velkych pismen pouzite funkciu 'std::isupper'

    VSTUPNA HODNOTA:
        [in] tree - prehladavany strom

    NAVRATOVA HODNOTA:
        zoznam velkych pismen, ktore su hodnotami uzlov v strome 'tree'

    VYSTUPNA PODMIENKA:
        Poradie vo vystupnom zozname musi zodpovedat postupnosti prehladavania algoritmom DO HLBKY, styl PRE-ORDER.

    PRIKLAD:
        obrazok na webe
*/


list<char> depthFirstSearchUpperCases(const Tree *tree) {
    list<char> list{};
    Node* root = tree->root;
    if(!root)
    {
        return list;
    }
    stack<Node*> s;
    map<Node*, bool> visited;
    for(Node* vv : tree->root->children)
    {
        visited[vv] = false;
    }
    s.push(root);
    while(!s.empty())
    {
        root = s.top();
        s.pop();
        if(!visited[root])
        {
            visited[root] = true;
            if(isupper(root->value))
            {
                list.push_back(root->value);
                //cout << root->value;
            }
            //cout << root->value;
            for(Node* e : root->children)
            {
                s.push(e);
            }
        }
    }
    return list;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam vsetkych hodnot uzlov v strome 'tree', ktorych hodnotou je velke pismeno.
    Pouzite algoritmus hladania DO SIRKY.
    Pouzite iterativnu implementaciu.
    Doporucenie: pre identifikaciu velkych pismen pouzite funkciu 'std::isupper'

    VSTUPNA HODNOTA:
        [in] tree - prehladavany strom

    NAVRATOVA HODNOTA:
        zoznam velkych pismen, ktore su hodnotami uzlov v strome 'tree'

    VYSTUPNA PODMIENKA:
        Poradie vo vystupnom zozname musi zodpovedat postupnosti prehladavania algoritmom DO SIRKY.

    PRIKLAD:
        obrazok na webe
*/



list<char> breadthFirstSearchUpperCases(const Tree *tree) {
    list<char> list{};
    Node* root = tree->root;
    if(!root) return list;
    queue<Node*> q;
    map<Node*, bool> visited;
    for(Node* vv : tree->root->children){
        visited[vv] = false;
    }
    visited[root] = true;
    if(isupper(root->value))
    {
        list.push_back(root->value);
        //cout << root->value;
    }
    //cout << root->value << " ";
    q.push(root);
    while(!q.empty()){
        for(Node* e : q.front()->children){
            if(!visited[e]){
                visited[e] = true;
                q.push(e);
            }
            if(isupper(e->value))
            {
                list.push_back(e->value);
                //cout << e->value;
            }
        }
        q.pop();
    }
    return list;
}

//=================================================================================================
// GRAF - definicia pre dalsie ulohy
//=================================================================================================
// Graf reprezentuje cestnu siet medzi obcami na planete.
// Uzol grafu reprezentuje obec.
// Hrana grafu reprezentuje "priame" cestne spojenie z jednej obce do druhej.
// Graf je orientovany -> Hrana grafu reprezentuje moznost jazdy len jednym smerom.
//  Preto je moznost "priamej" jazdy medzi obcami oboma smermy reprezentovana dvoma hranami grafu.
// Graf je ohodnoteny -> Mapa cestnej siete eviduje dlzky "priamych" cestnych spojeni medzi obcami.
// Obce nemusia byt prepojene cestnou sietou, napriklad ak sa nachadzaju na roznych pevninach.

// Forward deklaracie su potrebne, pretoze:
//  - definicie 'City' a 'RoadTo' su cyklicky zavisle:
//      - v definicii 'City' je pouzite 'RoadTo'
//      - a v definicii 'RoadTo' je pouzite 'City'
//  - definicie 'City' a 'SearchData' su cyklicky zavisle:
//      - v definicii 'City' je pouzite 'SearchData'
//      - a v definicii 'SearchData' je pouzite 'City'
struct RoadTo;
struct City;

// Udaje pouzite v algoritmoch hladania
struct SearchData {
    // Mozete si doplnit dalsie atributy a metody, ktore pouzijete v algoritmoch hladania
    bool discovered;
    unsigned distance;
    const City *previous;
    bool foundShortestPath;

    void clear() { // nastavi na implicitne hodnoty (tuto metodu mozete upravit (ale nie jej deklaracnu cast - nedoplnajte parametre))
        discovered = false;
        distance = numeric_limits<unsigned>::max();
        previous = nullptr;
        foundShortestPath = false;
    }
};

// Obec (uzol grafu)
struct City {
    string name; // nazov obce
    list<RoadTo> roads; // zoznam "priamych" jednosmernych cestnych spojeni do dalsich obci (zoznam vystupnych hran z tohto uzla grafu)

    SearchData searchData; // udaje pouzite v algoritmoch hladania

    // Mozete doplnit dalsi konstruktor alebo metody, ale tento konstruktor nemente
    explicit City(string name) : name(move(name)) {
        searchData.clear();
    };
    City(void){
        this->name = "";
    }
};

// Jednosmerne "priame" cestne spojenie do dalsej obce (orientovana, ohodnotena hrana grafu)
struct RoadTo {
    City *city; // obec, do ktorej je toto "priame" cestne spojenie
    unsigned length; // dlzka tohto "priameho" spojenia

    // Mozete doplnit dalsi konstruktor alebo metody, ale tento konstruktor nemente
    RoadTo(City *city, unsigned length)
            : city(city)
            , length(length) {
    }
};

// Cestna mapa planety (orientovany, ohodnoteny graf)
struct Planet {
    list<City> cities; // zoznam obci na planete (zoznam vrcholov grafu)

    void clearSearchData() { // inicializuje atributy pouzite v algoritme hladania
        for(City &c : cities) {
            c.searchData.clear();
        }
    }
};

// Vyminka v pripade neexistencie obce so zadanym nazvom
class CityNotExistsException : exception {
    string cityName; // nazov obce
public:
    explicit CityNotExistsException(string name)
            : cityName(move(name)) {
    }
    const char * what() const noexcept override { // vrati nazov neexistujucej obce
        return cityName.c_str();
    }
};

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam nazvov vsetkych obci na planete 'planet',
    ktore su z obce s nazvom 'startCity' dosiahnutelne pomocou cestnej siete.
    Pouzite algoritmus hladania DO SIRKY.

    VSTUPNA HODNOTA:
        [in] planet - cestna siet na planete
        [in] startCity - nazov obce

    NAVRATOVA HODNOTA:
        zoznam nazvov vsetkych obci, dosiahnutelnych z obce 'startCity'

    VYNIMKA:
        CityNotExistsException - ak na planete 'planet' neexistuje obec s nazvom 'startCity'.
        Metoda 'CityNotExistsException::what()' vrati nazov neexistujucej obce (hodnota 'startCity').

    VYSTUPNE PODMIENKY:
        Vystupny zoznam obsahuje aj 'startCity'.
        Poradie vo vystupnom zozname musi zodpovedat postupnosti prehladavania algoritmom DO SIRKY.

    PRIKLAD:
        obrazok na webe

    POZNAMKA:
        Ak v implementacii pouziteje 'City::searchData',
        tak bude pravdepodobne potrebne na zaciatku zavolat 'planet->clearSearchData()',
        aj aby bolo osetrene viacnasobne volanie algoritmu s tym istym objektom 'planet'.
*/

list<string> breadthFirstSearchReachable(Planet * planet, const string & startCity) {
    planet->clearSearchData();
        queue<City*> cities ;
        list<string> cityList;
        City *c;
        auto it = find_if(planet->cities.begin(),planet->cities.end(),[&startCity](City& c){
            return startCity == c.name;
        });

        if (it == planet->cities.end()){
            throw CityNotExistsException(startCity);
        }

        c = &(*it);
        if (!c) return cityList;
        it->searchData.discovered = true;
        cities.push(&(*it));
        while (!cities.empty()){
            c = cities.front();
            cityList.push_back(c->name);
            cities.pop();
            for (auto i:c->roads) {
                if (!i.city->searchData.discovered){
                    i.city->searchData.discovered = true;
                    cities.push(i.city);
                }
            }
        }
        return cityList; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
    }

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najte dlzky najkratsich ciest z obce 'startCity' do vsetkych dosiahnutelnych obci.
    Pouzite Dijkstrov algoritmus.

    VSTUPNE HODNOTY:
        [in] planet - cestna siet na planete
        [in] startCity - nazov obce

    NAVRATOVA HODNOTA:
        Pre kazdu obec dosiahnutelnu zo 'startCity' (na planete 'planet') obsahuje dlzku najkratsej cesty zo 'startCity'.

    VYNIMKA:
        CityNotExistsException - ak na planete 'planet' neexistuje obec s nazvom 'startCity'.
        Metoda 'CityNotExistsException::what()' vrati nazov neexistujucej obce (hodnota 'startCity').

    VYSTUPNA PODMIENKA:
        Navratova hodnota obsahuje nazvy len tych miest, ktore su dosiahnutelne zo 'startCity'.
        Navratova hodnota obsahuje aj vzdialenost do 'startCity' (nula).

    PRIKLAD:
        obrazok na webe

    POZNAMKA:
        Ak v implementacii pouziteje 'City::searchData',
        tak bude pravdepodobne potrebne na zaciatku zavolat 'planet->clearSearchData()',
        aj aby bolo osetrene viacnasobne volanie algoritmu s tym istym objektom 'planet'.
*/
auto extract(Planet * planet, const string & startCity, vector<string> & mesta , int begin_indx, int numb_edges){

    vector<vector<int>> incidenc_matic( numb_edges , vector<int> (numb_edges));

    int first_indx = 0;
    for (auto item : planet->cities)
    {
        for (auto item2 : item.roads)
        {
            int second_indx = 0;
            for ( int x = 0 ; x < numb_edges ; ++x)
            {
                if (mesta[x] == item2.city->name){
                    second_indx = x;
                    break;
                }
            }
            incidenc_matic[first_indx][second_indx] = item2.length;
        }
        ++first_indx;
    }

    return incidenc_matic;
}

# define INF 0x3f3f3f3f
typedef pair<int, int> iPair;

void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
}

map<string, unsigned> dijkstra(Planet * planet, const string & startCity) {
    // Find start city
    int numb_edges = 0;
    int begin_indx = 0;
    vector<string> mesta;

    for (auto k : planet->cities){
        if (k.name == startCity){
            begin_indx = numb_edges;
        }
        mesta.push_back(k.name);
        ++numb_edges;
    }

    // Throw Exception
    City begin;
    for (auto item : planet->cities ){
        if (item.name == startCity){begin = item;
            break;}}

    if (begin.name == ""){throw(CityNotExistsException(startCity));}

    // Extract Incident Matrix
    vector<iPair> adj[numb_edges];

    auto matica = extract(planet,startCity, mesta, begin_indx, numb_edges);

    for (int i = 0 ; i < numb_edges ; ++i)
    {
        for (int k = 0 ; k < numb_edges ; ++k)
        {
            if (matica[i][k] != 0){
                addEdge(adj,i,k,matica[i][k]);
            }
        }
    }


    int src = begin_indx;

    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<int> dist(numb_edges, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();


        for (auto x : adj[u])
        {

            int v = x.first;
            int weight = x.second;


            if (dist[v] > dist[u] + weight)
            {

                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }


    map<string, unsigned> output;
    for (int i = 0; i < numb_edges; i++)
        if (dist[i] != INF){
            output.insert(make_pair( mesta[i] , (unsigned)dist[i]));}

    return output;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {
  //  testUloha1();
  //  testUloha2();
   //   testUloha3();
  //     testUloha4();
  // testUloha5();
 //  testUloha6();

    // tu mozete doplnit testovaci kod
 /*   Tree* strom{new Tree};

    Node* druhy = new Node{'b'};
    //druhy->value = 'B';
    druhy->children = list<Node*>{};

    Node* piaty = new Node{'E'};
    //piaty->value = 'E';
    piaty->children = list<Node*>{};

    Node* stvrty = new Node{'d'};
    //stvrty->value = 'D';
    stvrty->children.push_back(piaty);

    Node* treti = new Node{'C'};
    //treti->value = 'C';
    treti->children = {stvrty};

    Node* prvy = new Node{'A'};
    //prvy->value = 'A';
    prvy->children = list<Node*>{druhy, treti};

 //   strom->root = prvy;

    list<char> list;
    list  =  depthFirstSearchUpperCases(strom);
    for (char i:list) {
        std::cout<<i<<endl;

    }
*/

 Planet zem;

 City he("Humenne");
 City Po("Presov");
 City Ke("kosice");

    zem.cities.push_back(Po);
    zem.cities.push_back(he);
    zem.cities.push_back(Ke);

 RoadTo cestaPO(&Po,10);
 RoadTo cestaKE(&Ke,9);
 RoadTo cestaHE(&he,11);

 he.roads.push_back(cestaPO);
 Po.roads.push_back(cestaKE);
 Ke.roads.push_back(cestaPO);
 Ke.roads.push_back(cestaHE);

    list<string> cityList;
    cityList = breadthFirstSearchReachable(&zem,"Humenne");

    for (auto &i: cityList) {
        std::cout<<i<<endl;

    }
    /*Planet* pl{new Planet};
    City London{"London"};
    City Haron{"Haron"};
    City Pecelon{"Pecelon"};
    City Bailon{"Bailon"};
    City Nicudon{"Nicudon"};
    City Etalon{"Etalon"};
    City Tigron{"Tigron"};

    RoadTo Lon(&London, 1);
    RoadTo harL(&Haron, 10);
    RoadTo harB(&Haron, 15);
    RoadTo pecL(&Pecelon, 40);
    RoadTo pecH(&Pecelon, 20);
    RoadTo nicL(&Nicudon, 100);
    RoadTo nicP(&Nicudon, 50);
    RoadTo nicB(&Nicudon, 50);
    RoadTo baiP(&Bailon, 10);
    RoadTo tigE(&Tigron, 10);

    London.roads = {harL, pecL, nicL};
    Haron.roads = {pecH};
    Pecelon.roads = {nicP, baiP};
    Nicudon.roads = {};
    Bailon.roads = {harB, nicB};
    Etalon.roads = {tigE};
    Tigron.roads = {};

    pl->cities = {London, Haron, Pecelon, Nicudon, Bailon, Tigron, Etalon};
    dijkstra(pl,"London");*/
    return 0;
}

