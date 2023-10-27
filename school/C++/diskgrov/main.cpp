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

    struct City {
        string name; // nazov obce
        list<RoadTo> roads; // zoznam "priamych" jednosmernych cestnych spojeni do dalsich obci (zoznam vystupnych hran z tohto uzla grafu)

        SearchData searchData; // udaje pouzite v algoritmoch hladania

        // Mozete doplnit dalsi konstruktor alebo metody, ale tento konstruktor nemente
        explicit City(string name) : name(move(name)) {
            searchData.clear();
        };
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
    City miniDist(Planet *planet) // finding minimum distance
    {
        std::cout<<"vstup do funkcie miniDist"<<endl;

        unsigned int minimum=+2147483647;

        City citycity = planet->cities.front();

        for(auto &city: planet->cities)
        {
            std::cout<<"vo funkcii skumane mesto je"<<city.name<< " s distance"<< city.searchData.distance<<endl;
            if(!city.searchData.discovered && city.searchData.distance <= minimum)
            {
                minimum=city.searchData.distance;
                citycity = city;
            }
        }
        std::cout<<"mesto ktore vratila funkcia je "<<citycity.name<< " s distance"<< citycity.searchData.distance<<endl;
        return citycity;
    }

    void dijkstra(Planet * planet, const string & startCity){
        std::cout<<"zaciatok definicia"<<endl;
        auto curr = find_if(planet->cities.begin(),planet->cities.end(),[&startCity](City& c){
            return startCity == c.name;
        });

        std::cout<<"mesto je"<<curr->name<< "s distance"<< curr->searchData.distance<<endl;
        for (auto &city: planet->cities) {
            city.searchData.distance;
            city.searchData.discovered = false;
           // city.searchData.previous = nullptr;
        }
        curr->searchData.distance = 0;

        std::cout<<"mesto je po zadani distancu 0"<<curr->name<< "s distance"<< curr->searchData.distance<<endl;
        for (auto &city: planet->cities)
        {
            *curr = miniDist(planet);
            std::cout<<"curent je"<<curr->name<<endl;
            curr->searchData.discovered=true;
            for (auto &RoadTo: curr->roads)
            {
                if(curr->searchData.discovered &&curr->searchData.distance!=2147483647  && curr->searchData.distance+RoadTo.length< RoadTo.city->searchData.distance){


                    RoadTo.city->searchData.distance = curr->searchData.distance+RoadTo.length;
                    std::cout<<"cesta z "<<curr->name<<"do RoadTO.city "<<RoadTo.city->name<< "s distance "<< RoadTo.city->searchData.distance<<endl;
                }
            }

        }
    }
    //-------------------------------------------------------------------------------------------------
    // TESTOVANIE
    //-------------------------------------------------------------------------------------------------

    // tu mozete doplnit pomocne funkcie a struktury

    int main() {

        Planet* pl{new Planet};
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
        dijkstra(pl,"London");

        for  (auto &what: pl->cities) {
            std::cout<<what.name<<" "<<what.searchData.distance<<endl;

        }
        std::cout<<pl->cities.front().roads.front().city->searchData.distance<<endl;

        return 0;
    }