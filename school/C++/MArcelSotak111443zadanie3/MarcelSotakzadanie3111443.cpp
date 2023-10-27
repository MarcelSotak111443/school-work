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
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};
Node *createNode(int value){
    Node *newNode = new Node;
    newNode->data=value;
    newNode->next= nullptr;
    return newNode;
}

void appendNode(List *list, const int val) {
    Node *newNode = createNode(val);
    if (list->first == nullptr){
        list->first = newNode;
    }
    else{
        Node *tmp = list->first;
        while (tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
}

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        {1, 3, 2} -> {3, 2, 1}
        {1, 2, 2, 1} -> {2, 2, 1, 1}
        {1} -> {1}
        {} -> {}
*/
void insertionSort(int *data, const size_t length) {
    int current;
    for (size_t i = 1;i < length; i++) {
        current = data[i];
        size_t j = i;
        while (j > 0    && current > data[j-1]){
            data[j] = data[j-1];
            -- j;
        }
        data[j] = current;


    }
}



//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        {"Juraj", "Peter", "Andrej", nullptr} -> {"Peter", "Juraj", "Andrej", nullptr}
        {"Juraj", "Anabela", "Peter", "Andrej", nullptr} -> {"Peter", "Juraj", "Andrej", "Anabela", nullptr}
        {"Andrej", "Juraj", "Andrej", nullptr} -> {"Juraj", "Andrej", "Andrej", nullptr}
        {"Andrej", nullptr} -> {"Andrej", nullptr}
        {nullptr} -> {nullptr}

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    if (data[0]== nullptr)
        return;
    const char *current;
    int number;
    for (size_t i = 1; *(data+i) != nullptr; i++) {
        current = *(data+i);

        // std::cout<<*current<<"  data[i] ma cislo"<<number<<endl;
        size_t j = i;
        while (j > 0  && strcmp(data[j-1],current)<0){
            data[j] = data[j-1];
            -- j;
        }
        data[j] = current;


    }
}


//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
    if (list->first == nullptr)
        return;

    Node *first = list->first;
    Node *redfirst = list->first->next;
    first->next = nullptr;

    while (redfirst != nullptr) {

        Node *current = redfirst;
        redfirst = redfirst->next;
        if (current->data > first->data) {
            current->next = first;
            first = current;
        }else{
            Node *previous = first;
            while (previous->next != nullptr && previous->next->data>current->data){
                previous = previous->next;

            }
            current->next = previous->next;
            previous->next = current;
        }
    }
    list->first = first;



}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1], zvysne prvky v 'output' funkcia nemeni.
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         {10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10}
        output pred vykonanim funkcie: {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20}
        output po vykonani funkcie:    {20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20}
*/
void merge(int* output, const int* input, const size_t low, const size_t middle, const size_t high)
{
    {
        size_t first = low;
        size_t second = middle;
        size_t out = low;

        while (first < middle && second < high) {
            if (input[first] >= input[second]) {
                output[out] = input[first];
                ++first;
            }
            else {
                output[out] = input[second];
                ++second;
            }
            ++out;
        }
        while (first < middle) {
            output[out] = input[first];
            ++first;
            ++out;
        }
        while (second < high) {
            output[out] = input[second];
            ++second;
            ++out;
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        {1, 3, 2} -> {3, 2, 1}
        {1, 2, 2, 1} -> {2, 2, 1, 1}
        {1} -> {1}
        {} -> {}

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/

void mergeSort(int* arrayA, int* arrayB, const size_t low, const size_t high)
{
    if (low + 1 >= high) {
        return;
    }

    const size_t middle = (high + low) / 2;

    mergeSort(arrayB, arrayA, low, middle);
    mergeSort(arrayB, arrayA, middle, high);

    merge(arrayA, arrayB, low, middle, high);
}
void mergeSort(int *data, const size_t length) {
    int* tmpArray = new int[length]; // pomocne pole
    std::memcpy(tmpArray, data, length * sizeof(int));
    mergeSort(data, tmpArray, 0, length);
    delete[] tmpArray;
}


//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

    int data[]{2,5,6,7,8,5,4,8};

    insertionSort(data,8);
    for (int i = 0; i < 8; ++i) {
        std::cout<<data[i]<<endl;

    }
   /* List *list = new List;
    list->first = nullptr;

    // List *list2 = new List;
    // list2->first = nullptr;

    int aray[]{5,3,7,4,7,8,3,4,7,5};

    // int arayz[]{7};

    for(int i = 0; i < 9; ++i) {
        appendNode(list,aray[i]);
    }



    insertionSort(data,8);

    const char *mena[] = {"abe","ab","abc","abcd","terka", nullptr};

//    insertionSort(data,9);
 //   insertionSort(mena);


    insertionSort(list);

    Node *tmp = list->first;
    while (tmp) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;*/
    return 0;
}