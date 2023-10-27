/*
Meno a priezvisko: Marcel Sotak 111443
POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_zadanie02.cpp (pouzite vase udaje bez diakritiky).
(2)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(3)  Cela implementacia musi byt v tomto jednom subore.
(4)  Odovzdajte len tento (spravne premenovany) zdrojovy subor.
(5)  Program musi byt kompilovatelny.
(6)  Globalne a staticke premenne su zakazane.
(7)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(8)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node *next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node *first; // adresa prveho uzla zoznamu
};

// Pomocna struktura pre ulohu 2
struct ListData {
    int *data; // pole hodnot uzlov
    size_t len; // dlzka pola 'data'
};

Node *createNode(int value){
    Node *newNode = new Node;
    newNode->data=value;
    newNode->next= nullptr;
    return newNode;
}


//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zretazeneho zoznamu 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr') a moze
           mat lubovolny pocet uzlov (0 a viac).

    PARAMETRE:
        [in/out] list   - adresa zretazeneho zoznamu, do ktoreho ideme pridavat uzol
        [in] val        - hodnota uzla, ktory sa ma pridat na koniec zoznamu 'list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        {prazdny zoznam},5 ---> {5}
        {1},1 ---> {1,1}
        {8,2,6,6},14 ---> {8,2,6,6,14}
        {6,100,33},-85 ---> {6,100,33,-85}
        {1,2,3,4,5},3 ---> {1,2,3,4,5,3}
*/

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
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam, ktory bude skonstruovany pomocou udajov vo vstupnej
    strukture 'list_data'. Struktura 'list_data' obsahuje polozku 'data', ktora reprezentuje pole
    hodnot pre jednotlive uzly zoznamu. Struktura 'list_data' taktiez obsahuje polozku 'len', ktora
    hovori aku ma dlzku pole 'data'. Vytvoreny zoznam musi obsahovat uzly, ktore zodpovedaju
    svojimi hodnotami a poradim prvkom ulozenym v poli 'data' (dlzka zoznamu bude 'len').
    Funkcia nakoniec vrati adresu takto vytvoreneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list_data' vzdy existuje (t.j. 'list_data' je rozny od 'nullptr').
        2) Pre polozku 'len' plati, ze 'len' >= 0 a nikdy nebude mat vacsiu hodnotu ako je
           realny pocet prvkov v poli 'data'.
        3) Ak je polozka 'len' rovna 0, vtedy sa vytvori a vrati prazdny zretazeny zoznam
           (t.j. platny zoznam, ktory ma 0 uzlov).

    PARAMETRE:
        [in] list_data - struktura, pomocou ktorej sa vytvori zoznam

    NAVRATOVA HODNOTA:
        Adresa zretazeneho zoznamu, ktory bol vytvoreny pomocou struktury 'list_data'.
        Vid pokyny vyssie.

    PRIKLADY:
        polozka 'data' = [1,2,3]
        polozka 'len' = 0
        vystupny zoznam bude mat 0 uzlov, t.j. {}

        polozka 'data' = [1,2,3]
        polozka 'len' = 2
        vystupny zoznam bude {1,2}

        polozka 'data' = [1,2,3]
        polozka 'len' = 3
        vystupny zoznam bude {1,2,3}

        polozka 'data' = [-9,412,64,72,100,100,6]
        polozka 'len' = 4
        vystupny zoznam bude {-9,412,64,72}

*/

List *createList(const ListData *list_data) {
    List *list2 = new List;
    if (list_data->len==0){
        List *listData = new List();
        return listData;
    }
    Node *tmp = createNode(list_data->data[0]);
    list2->first =tmp;

    for (int i = 1; i < list_data->len; ++i) {
        tmp->next = createNode(list_data->data[i]);
        tmp=tmp->next;
    }

    return list2; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' do vzostupne zotriedeneho zoznamu 'sorted_list'.
    Pridanie musi prebehnut takym sposobom, aby bol zoznam 'sorted_list' po pridani noveho uzla
    stale vzostupne zotriedeny.

    POZNAMKA: Na poradi duplikatov v zozname 'sorted_list' nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'sorted_list' vzdy existuje (t.j. 'sorted_list' je rozny od 'nullptr').
        2) Vstupny zoznam 'sorted_list' moze mat lubovolny pocet uzlov (0 a viac).
        3) Vstupny zoznam 'sorted_list' je vzostupne zotriedeny.

    PARAMETRE:
        [in/out] sorted_list    - adresa vstupneho zretazeneho zoznamu, ktory je zotriedeny
                                  vzostupne (z angl. ascending)
        [in] val                - hodnota uzla, ktory sa ma pridat do zoznamu 'sorted_list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        {},0 ---> {0}
        {},156 ---> {156}
        {8},4 ---> {4,8}
        {7},10 ---> {7,10}
        {55},55 ---> {55,55} ... poznamka: na poradi duplikatov nezalezi
        {1,8,236,888},70 ---> {1,8,70,236,888}
        {6,6,14,82,82,100},6 ---> {6,6,6,14,82,82,100}

*/

void insertNode(List *sorted_list, const int val) {
    Node *newNode = createNode(val);
    appendNode(sorted_list, val);

    Node *value = sorted_list->first;
    Node *tmp = sorted_list->first;
    Node *temp = new Node;
    Node *temp2 = new Node;

    while(tmp->next != nullptr){

        while (value->next != nullptr) {
            if (value->data > value->next->data) {

                temp->data = value->data;
                temp2->data = value->next->data;

                value->next->data = temp->data;
                value->data = temp2->data;

            }
            value = value->next;
        }
        value = sorted_list->first;
        tmp = tmp->next;
    }

}
//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zoznam spojenim zoznamov 'list1' a 'list2'. Funkcia vrati adresu
    novo vytvoreneho zoznamu. V spojenom zozname idu najprv uzly zoznamu 'list1' (v nezmenenom poradi)
    a potom nasleduju uzly zoznamu 'list2' (v nezmenenom poradi). Pri vytvarani noveho zoznamu mozete
    pouzit hlboku alebo plytku kopiu existujucich uzlov (obe riesenia budu akceptovane).

    POZNAMKA:
        Prazdny zoznam je taky zoznam, ktory je platny, ale obsahuje 0 uzlov
        (t.j. polozka 'first' je nastavena na 'nullptr').

    VSTUPNE PODMIENKY:
        1) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).

    PARAMETRE:
        [in/out] list1 - adresa prveho zoznamu
        [in/out] list2 - adresa druheho zoznamu

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol spojenim zoznamov 'list1' a 'list2'.

    PRIKLADY:
        {} + {} ---> {}
        {5,9} + {} ---> {5,9}
        {} + {2,2,2} ---> {2,2,2}
        {1} + {2} ---> {1,2}
        {7} + {3,9,16} ---> {7,3,9,16}
        {50,-47,23,1} + {0,0,9,-8} ---> {50,-47,23,1,0,0,9,-8}
*/

List *joinLists(List *list1, List *list2) {
    List *list = new List;
    list->first = nullptr;

    Node *tmp = list1->first;
    Node *tmp2 = list2->first;
    list->first = list1->first;
    if (tmp == nullptr && tmp2 == nullptr){

        return list;
    }
    if (tmp == nullptr){
        tmp = list2->first;
        list->first = tmp;


    }

    while (tmp->next != nullptr){
        tmp = tmp->next;

    }
    if (list1->first != nullptr)
        tmp->next = tmp2;

    return list; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani posledny uzol zo zoznamu 'list'. Ak je zoznam 'list' prazdny, funkcia nic
    nevykona. Pamat uzla, ktory funkcia vymaze musi byt korektne dealokovana.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in/out] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        {} ---> {}
        {1} ---> {}
        {1,2} ---> {1}
        {1,2,3} ---> {1,2}
*/

void removeLastNode(List *list) {

    if (list->first != nullptr){
        if (list->first->next == nullptr){
            delete(list->first);
            list->first = nullptr;
            return;
        }
        Node *tmp = list->first;
        while (tmp->next->next != nullptr) {
            tmp = tmp->next;
        }
        delete tmp->next;
        tmp->next = nullptr;
    }





    /*if (tmp->next == nullptr) {
        delete tmp;
    } else {
        delete tmp->next;
        tmp->next = nullptr;
    }*/
}
//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci je vstupny zoznam 'list' palindrom. Prazdny zoznam budeme povazovat za
    palindrom.

    Poznamka: Palindrom predstavuje taku postupnost hodnot, ktora sa cita rovnako v oboch smeroch.
    URL: https://sk.wikipedia.org/wiki/Palindr%C3%B3m
    Priklad palindromu: {1212121} alebo {4953594}

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci vstupny zoznam je/nie je palindrom.

    PRIKLADY:
        {} ---> true
        {1} ---> true
        {2,2,2,2} ---> true
        {1,2,3,4,5} ---> false
        {1,2,2,1} ---> true
        {8,4,8,4,8} ---> true
        {9,842,613,2,613,842,9} ---> true
        {7,9,1,2} ---> false
        {0,0,0,7,0,0} ---> false

*/

bool isPalindrome(const List *list) {
    Node *tmp = list->first;
    Node *tmp2 = list->first;
    int i=0;
    while (tmp != nullptr){
        tmp = tmp->next;
        i++;
    }
    tmp = list->first;
    for (int j=0 ; j < i/2; j++){


        for (int a=0; a < i-j-1 ; a++){
            tmp2= tmp2->next;

        }
//porovnaj to tu iba
        if (tmp->data != tmp2->data)
            return  false;
        tmp = tmp->next;
        tmp2 = list->first;
    }
    return true; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati sucet hodnot prvych 'n' uzlov v zozname 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).
        3) Parameter 'n' nebude zaporny a nebude mat nikdy vyssiu hodnotu ako je realny pocet
           uzlov v zozname.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] n - pocet uzlov od zaciatku zoznamu 'list', ktorych sucet sa vrati

    NAVRATOVA HODNOTA:
        Sucet hodnot prvych 'n' uzlov zoznamu 'list'. Ak 'n'=0, vtedy funkcia vrati hodnotu 0.

    PRIKLADY:
        {},0 ---> 0
        {1,2,3},0 ---> 0
        {6},1 ---> 6
        {5,6,7},2 ---> 11
        {4,4,4,4,4,4},6 ---> 24
        {-8,41,-314,21},3 ---> -281

*/

int sumNodes(const List *list, const int n) {
    Node *tmp = list->first;
    int number=0;
    for (int i = 0; i < n; ++i) {
        number = number + tmp->data;
        tmp = tmp->next;
    }
    return number; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci zoznam 'list1' obsahuje vsetky hodnoty uzlov zoznamu 'list2'.
    Na poradi nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list1' a 'list2' vzdy existuju (t.j. su rozne od 'nullptr').
        2) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).
        3) Zoznam 'list2' nebude obsahovat duplicitne uzly.

    PARAMETRE:
        [in] list1 - prvy zoznam
        [in] list2 - druhy zoznam

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci zoznam 'list1' obsahuje/neobsahuje
        vsetky hodnoty uzlov zoznamu 'list2'.

    PRIKLADY:
        {},{} ---> true
        {},{1,2,3} ---> false
        {1,2,3},{} ---> true
        {5,6,7},{5,6,8} ---> false
        {8,4,3},{3,8,4} ---> true
        {7,6,1,9,8},{1,6,8} ---> true
        {3,3,3,3,3},{2,3} ---> false
        {8,6,1,2,5,0,7,7},{7} ---> true
        {9,5,10},{41,10,5} ---> false

*/

bool contains(const List *list1, const List *list2) {
    Node *tmp = list1->first;
    Node *tmp2 = list2->first;
    bool hm = false;
    while (tmp2 != nullptr){
        hm = false;
             while (tmp != nullptr){
            if (tmp2->data == tmp->data){
                std::cout<<tmp2->data<<" ";
                std::cout<<tmp->data<<std::endl;
                hm=true;
            }
            tmp = tmp->next;
        }
        tmp = list1->first;
        tmp2 = tmp2->next;
        if (!hm)
            return false;

    }


    return true; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati HLBOKU kopiu zoznamu 'list'. Vo vytvorenej kopii musia byt zachovane
    hodnoty a poradie uzlov z povodneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa zoznamu, ktoreho hlboku kopiu treba vytvorit

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol ako hlboka kopia vstupneho zoznamu 'list'. Kopiou
        prazdneho zoznamu je prazdny zoznam.

    PRIKLADY:
        Vstup = {}
        Vystup = {}

        Vstup = {1,2,3}
        Vystup = {1,2,3}
        Poznamka: adresy uzlov na rovnakych poziciach v oboch zoznamoch sa musia lisit
        (pretoze je to hlboka kopia)
*/

List* deepCopyList(const List *list) {

    // Create a temp variable since ll.current doesn't move/change.

    Node* tmp = list->first;

    List *list2 = new List();
    list2->first = nullptr;

    if (tmp== nullptr)
        return  list2;
    Node *tmp2 = createNode(tmp->data);
    list2->first = tmp2;

    while (tmp->next != nullptr){
        tmp2->next = createNode(tmp->next->data);
        tmp2=tmp2->next;
        tmp=tmp->next;

    }
    return list2; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde posledny vyskyt uzla s hodnotou 'val' v zozname 'list' a vrati jeho adresu.
    Ak sa v zozname 'list' takyto uzol nenachadza, funkcia vrati 'nullptr'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hladana hodnota uzla

    NAVRATOVA HODNOTA:
        Adresa posledneho vyskytu uzla s hodnotou 'val' v zozname 'list'.

    PRIKLADY (treba otestovat pomocou debuggera):
        {},2 ---> nullptr
        {5,4,3,2},1 ---> nullptr
        {-5,4,-9,66},4 ---> adresa 2. uzla
        {1,1,1,5,6,41},1 ---> adresa 3. uzla
        {8,6,7,3,2,6},6 ---> adresa 6. uzla
*/

Node *findLastNodeOccurrence(const List *list, const int val) {
	Node *tmp = list->first;
	Node *vrati = nullptr;
    while (tmp != nullptr){
        if (tmp->data == val){
            vrati = tmp;
        }
        tmp = tmp->next;
    }
    return vrati; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {

    List *list = new List;
    list->first = nullptr;

    List *list2 = new List;
    list2->first = nullptr;

    List *list3 = new List;
    list3->first = nullptr;


    int aray[]{1,1,2,1,1};

    int arayz[]{1};


    for(int i = 0; i < 5; ++i) {
        appendNode(list,aray[i]);
    }


    for(int i = 0; i < 3; ++i) {
        appendNode(list2,arayz[i]);
    }

    //insertNode(list, 2);

    //std::cout<<"spoj listy"<<std::endl;
   // list = joinLists(list, list2);
  //   std::cout<<"usporadaj a vloz"<<std::endl;
  //  insertNode(list, 10);
   // std::cout<<"odstran posledny"<<std::endl;
      //removeLastNode(list);
      // std::cout<<"je palindrom"<<std::endl;
      std::cout<<isPalindrome(list)<<std::endl;
    //std::cout<<"sucet cisel"<<std::endl;
   //  std::cout<<sumNodes(list,1)<<std::endl;


   //std::cout<<contains(list,list2)<<std::endl;
  //  List *list3 = new List;
  // list3->first = nullptr;
   // int dataa[]{1,2,3,4,5};
  /*  ListData *listData = new ListData();
    listData->data = dataa;
    listData->len=4;*/


   // list = createList(listData);
   // list3 = deepCopyList(list);

    //std::cout<<list->first<<std::endl;
    //std::cout<<list3->first<<std::endl;
  //  Node *hmm = new Node;
   // hmm = findLastNodeOccurrence(list,8);

   // std::cout<<hmm;

   // int dataa[]{1,8,3,9,5};

   // ListData *listdata = new ListData;
   // listdata->len = 5;
   // listdata->data = dataa;
   // list3 = createList(listdata);



    Node *tmp = list->first;
    while (tmp) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;

    return 0;
}
