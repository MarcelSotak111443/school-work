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
(9) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Hmotnost produktu a obalu. Hmotnost zabaleneho produktu je suctom obidvoch zloziek
struct Weight {
    int product; // hmotnost produktu
    int packing; // hmotnost balenia
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data', od najvacsieho prvku po najmensi.
    Pouzite algoritmus bubble sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNA PODMIENKA:
        ak 'length' > 0, tak 'data' ukazuje na platne pole

    PRIKLADY:
        {1, 3, 2} -> {3, 2, 1}
        {1, 2, 2, 1} -> {2, 2, 1, 1}
        {1} -> {1}
        {} -> {}
*/
void swap(int *a,int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void bubbleSort(int *data, const size_t length) {
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < length-1; ++j) {
            if (data[j] < data[j+1]){
                swap(&data[j],&data[j+1]);

            }


        }

    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' podla celkovej hmotnosti zabaleneho tovaru, t.j. podla suctu zloziek ('product' a 'packing').
    Poradie usporiadania je od najtazsieho zabaleneho tovaru po najlahsi zabaleny tovar.
    Pouzite algoritmus bubble sort.

    Podmienka porovnania struktur:
    Pri porovnavani prvkov funkcia scita hodnoty 'product' a 'packing' oboch porovnavanych struktur.
    Struktury s vacsim suctom zloziek budu po usporiadani pred strukturami s mensim suctom zloziek.

    Vzajomne usporiadanie struktur s rovnakym suctom poloziek:
    Pri bodovom hodnoteni nezalezi na vzajomnom usporiadani struktur s rovnakym suctom poloziek (aj ked hodnoty poloziek mozu byt rozne).
    Lepsie je vsak implementovat stabilne triedenie (struktury s rovnakym suctom poloziek nemenia vzajomne usporiadanie).

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNA PODMIENKA:
        ak 'length' > 0, tak 'data' ukazuje na platne pole

    PRIKLADY:
        {{10, 1}, {20, 2}, {5, 2}} -> {{20, 2}, {10, 1},{5, 2}} pretoze 20+2=22, 10+1=11, 5+2=7 a 22 > 11 > 7
        {{11, 1}, {2, 1}, {10, 2}, {15, 7}} -> {{15, 7}, {11, 1}, {10, 2}, {2, 1}}
        {} -> {}

    POZNAMKA:
        Priklady jednoducheho vytvorenia pola v testovacom kode:
        Weight baliky[] = {{10, 1}, {20, 2}, {5,2}};
        Weight baliky[] = {{.product = 10, .packing = 1}, {.product = 20, .packing = 2}, {.product = 5, .packing = 2}}; // od C++ 20
*/
void swapWeight(Weight *data,Weight *data2){
    Weight tmp = *data;
    *data = *data2;
    *data2 = tmp;

}
void bubbleSort(Weight *data, const size_t length) {
    int sucet;
    int sucet2;
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < length-1; ++j) {
            sucet = data[j].packing + data[j].product;
            sucet2 = data[j+1].packing + data[j+1].product;
            if (sucet < sucet2){
                swapWeight(&data[j],&data[j+1]);
            }


        }

    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vyberie pivota a vrati jeho index.
    Pivota vyberie ako median prvkov:
      - data[low]
      - data[(high+low)/2]
      - data[high-1]

    PARAMETRE:
        [in] data - pole, v ktoreho casti s indexami 'low' ... 'high'-1, funkcia vybera pivot
        [in] low  - index prveho prvku casti pola, v ktorej funkcia hlada pivot
        [in] high - index za poslednym prvkom casti pola, v ktorej funkcia hlada pivot

    NAVRATOVA HODNOTA:
        index pivota

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole
        'low' < 'high'

    PRIKLADY:
        data: {10, 20, 2000, 30, 1000, 40, 5000, 50, 60, 70}, low: 2, high: 7 -> return 2
        data: {10, 20, 1000, 30, 2000, 40, 5000, 50, 60, 70}, low: 2, high: 7 -> return 4
        data: {10, 20, 5000, 30, 1000, 40, 2000, 50, 60, 70}, low: 2, high: 7 -> return 6

        data: {10, 20, 1000, 30, 40, 2000, 50, 5000, 60, 70}, low: 2, high: 8 -> return 5

        data: {10, 20, 1000, 2000, 30, 40, 50},               low: 2, high: 4 -> return 3
        data: {10, 20, 2000, 1000, 30, 40, 50},               low: 2, high: 4 -> return 3

        data: {10, 20, 1000, 30, 40},                         low: 2, high: 3 -> return 2
*/
size_t getPivotIndex(const int *data, const size_t low, const size_t high)
{
    size_t middle = (high+low)/2;
    size_t win;
    std::cout<<data[low]<<" "<<data[middle]<<" "<<data[high-1]<<endl;
    if (data[low] <= data[middle] && data[middle] <= data[high-1] || data[low] >= data[middle] && data[middle]>= data[high-1])
        return  middle ;
    if (data[middle] <= data[low] && data[low]<= data[high-1] || data[middle] >= data[low] && data[low]>= data[high-1])
        return low ;
    if (data[middle] <= data[high-1] && data[high-1] <= data[low] || data[middle] >= data[high-1] && data[high-1] >= data[low])
        return high-1;


}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona partition (cast algoritmu quick sort) a vrati novy index pivota.
    Pouzite styl algoritmu Lomuto.
    Poradie usporiadania:
        Najprv (vlavo) budu prvky vacsie alebo rovne ako pivot,
        potom pivot,
        potom (vpravo) prvky mensie ako pivot.

    PARAMETRE:
        [in, out] data - pole, v ktoreho casti 'low' ... 'high'-1 bude vykonane partition
        [in] pivot     - index pivota (pred partition)
        [in] low       - index prveho prvku casti pola, v ktorej bude vykonany partition
        [in] high      - index za poslednym prvkom casti pola, v ktorej bude vykonany partition

    NAVRATOVA HODNOTA:
        Index pivota po vykonani partition.

    VSTUPNE PODMIENKY:
        'low' <= 'pivot' < 'high'
        (index pivota moze byt lubobolny v rozsahu 'low'...'high'-1, napriklad v pripade nahodneho vyberu pivota)
        'data' ukazuje na platne pole

    PRIKLADY:
        1. priklad:
            vstup:  data: {10, 20, 30, 40, 50, 60, 70, 80, 90}, pivot: 5, low: 2, high: 7
            vystup: data: {10, 20, 70, 60, 50, 30, 40, 80, 90}, return 3

        2. priklad:
            vstup:  data: {10, 20, 30, 40, 50, 60, 70, 50, 80, 90}, pivot: 4, low: 2, high: 8
            vystup: data: {10, 20, 50, 60, 70, 50, 30, 40, 80, 90}, return 5
*/
size_t partition(int *data, const size_t pivot, const size_t low, const size_t high)
{


    swap(&data[pivot],&data[high-1]);
    size_t insert = low;
    for (size_t i = low; i < high; i++) {
        if (data[i] >= data[high-1]){
            swap(&data[insert],&data[i]);
            insert++;
        }


    }


    return insert-1;// tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada cast pola 'data' (s indexami 'low' ... 'high'-1).
    Pouzite algoritmus quick sort, styl Lomuto.
    Poradie usporiadania je od najvacsieho prvku po najmensi.

    PARAMETRE:
        [in, out] data - pole, ktoreho cast funkcia usporiada
        [in] low       - index prveho prvkou casti pola, ktoru funkcia usporiada
        [in] high      - index za posledny prvok casti pola, ktoru funkcia usporiada

    VSTUPNA PODMIENKA:
        ak 'low' < 'high', tak 'data' ukazuje na platne pole

    PRIKLAD:
        data: {1, 2, 3, 4, 5, 6, 7, 8, 9}, low: 2, high: 7 -> data: {1, 2, 7, 6, 5, 4, 3, 8, 9}
*/
void quickSort(int *data, const size_t low, const size_t high)
{



    if(low+1 < high){
        size_t pivot_index = getPivotIndex(data,low,high);
        pivot_index = partition(data, pivot_index, low, high);
        quickSort(data, low, pivot_index);
        quickSort(data,pivot_index+1, high);
    }
}


//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

    Weight baliky[] = {{10, 1}, {20, 2}, {5,2}};

    int data[]  = {55,44,86,932,24,57,54,76,89,6};
    int n = sizeof(data) / sizeof(data[0]);
    bubbleSort(data,9);
   // int number;
   // number = getPivotIndex(data,2,3);
  //  std::cout<<number<<"je index "<<endl;
 //     partition(data,4,2,8);

  //  quickSort(data,0,n);



    for (int i = 0; i < 10; ++i) {
        std::cout<<data[i]<<endl;

        bubbleSort(baliky,3);
    }
   // for (int i = 0; i < 3; ++i) {
    //    std::cout<<baliky[i].product<<" + "<<baliky[i].packing<<endl;

  //  }


    return 0;
}