#include <stdio.h>

#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}
int hodKockami(int position,int a,int b);


int main() {

    int seed,road,boost,blocks,variable1,vitaz;
    int j=0,k=0;
    int hrac1=-1,hrac2=-1;


    printf("Zadajte seed \n");
    scanf(" %d",&seed);
    printf("Zadajde dlzku cety \n");
    scanf(" %d",&road);
    printf("Zadajte pocet boostov \n");
    scanf(" %d",&boost);
    printf("Zdajte pocet blockov \n");
    scanf(" %d",&blocks);

    if(seed <= 0 || road < 10 || road > 100 ){
        printf("zla cesta");
        return 1;
    }
    if(boost + blocks > road / 2){
        printf("Kratka cesta");
        return 1;
    }
    srnd(seed);
    int draha[road];

    int najPole[400];
    for (int i = 0; i < road; i++) {
        draha[i]= 0;
    }
    while (j < boost){
        variable1 = rnd(1, road - 1);
        while (draha[variable1] != 0)
            variable1 = rnd(1, road - 1);
        draha[variable1]=5;
        j++;
    }
    j=0;
    variable1 = 0;
    while (j < blocks){
        variable1 = rnd(1, road - 1);
        while (draha[variable1] == 6 || draha[variable1] == 5)
            variable1 = rnd(1, road - 1);
        draha[variable1]=6;
        j++;
    }
        printf("BLOCK:");
        for (int k = 0; k < road; k++) {
            if(draha[k]==5)
            printf("%i ",k);
        }
        printf("\n");
        printf("BOOST:");
        for (int k = 0; k < road; k++) {
        if(draha[k]==6)
            printf("%i ",k);
        }
        printf("\n");

        //////////// pohyb
        int a,b,c=0;
        int Ph=-1,Po=-1,help;
        int pohyb1,pohyb2;
        int boost1 = 0,boost2 = 0;
        int round=1;


       while(Ph < road && Po < road) {

           vitaz = 1;
           printf("[%i,1] ", round);
           round++;
           printf("[%i,%i] ", Ph, boost1);
           a = rnd(1, 6);
           b = rnd(1, 6);
           pohyb1 = hodKockami(Ph, a, b);

           printf("[%i,%i] ", a, b);

           if ((a == 6 && b == 6) && Ph < Po && Po != -1 && Ph != -1) {
               help = Ph;
               Ph = Po;
               Po = help;

               najPole[c]=Ph;
               c++;
               najPole[c]=Po;
           } else if (a == 1 && b == 1 && Ph > Po && Po != -1 && Ph != -1) {
               help = Po;
               Po = Ph;
               Ph = help;

               najPole[c]=Ph;
               c++;

               najPole[c]=Po;
           } else {
               if (a == 6 && b == 6 && Ph != -1)
                   pohyb1 = 6;
               if (a == 1 && b == 1 && Ph!= -1)
                   pohyb1 = 1;
               if (pohyb1!=0){
               Ph = Ph + pohyb1 + boost1;
               najPole[c]=Ph;

               }else najPole[c]=-1;}



           if (draha[Ph] == 6) {
               boost1 = boost1 + 1;
               draha[Ph] = 0;

           }
           if (draha[Ph] == 5) {
               if (boost1 != 0) {
                   boost1 = 0;
                   draha[Ph] = 0;
               } else {
                   draha[Ph] = 0;
                   Ph = -1;


               }
           }

           if (Ph == Po) {
               Po = -1;
               ;

           }
           printf("[%i,%i] \n", Ph, boost1);
           c++;



        if(Ph < road){
            vitaz = 2;
        printf("[%i,2] ", round);
        round++;
        printf("[%i,%i] ", Po, boost2);
        a = rnd(1, 6);
        b = rnd(1, 6);
        pohyb2 = hodKockami(Po, a, b);
        printf("[%i,%i] ", a, b);
        if (a == 6 && b == 6 && Po < Ph && Po!= -1 && Ph!= -1) {
            help = Po;
            Po = Ph;
            Ph = help;

            najPole[c]=Ph;
            c++;

            najPole[c]=Po;
        }else if (a == 1 && b == 1 && Po > Ph && Po!= -1 && Ph!= -1) {
            help = Ph;
            Ph = Po;
            Po = help;

            najPole[c]=Ph;
            c++;

            najPole[c]=Po;

        }else{
            if (a == 6 && b == 6 && Po!= -1 )
            pohyb2 = 6;
            if (a == 1 && b == 1 && Po != -1)
            pohyb2 = 1;
            if (pohyb2!= 0){
            Po = Po + pohyb2 + boost2;
            najPole[c]=Po;
        }
            else najPole[c]=-1;}
        if (draha[Po] == 6) {
            boost2 = boost2 + 1;
            draha[Po] = 0;
        }

        if (draha[Po] == 5) {
            if (boost2 != 0) {
                boost2 = 0;
                draha[Po] = 0;
            } else {
                draha[Po] = 0;
                Po = -1;


            }
        }
        if (Po == Ph) {
            Ph = -1;

        }
            c++;
            printf("[%i,%i] \n", Po, boost2);
    }}
       /////////////// vypisy
       printf("WINNER:%i\n",vitaz);
//      printf("HOTSPOT:%i\road",);
    int counter,max=0;
    int nwmCo[c];
    for (int l = 0; l < c; l++) {
        counter=0;
        for (int x = 0; x < c; x++) {
           if (najPole[l]!= -1){
            if (najPole[l]== najPole[x]){
                counter +=1;
//                printf("L %i,X %i Num %i Numx %i counter %i \road",l,x,najPole[l],najPole[x],counter);
                nwmCo[l]=counter;}
        }else
          nwmCo[l]= 0;
        }}

        max = nwmCo[0];
        for (int v = 0; v < c; v++) {
//            printf("%i \road",nwmCo[v]);
            if (nwmCo[v]>max){
                max = nwmCo[v];
//                printf("max je %i",max);
            }


        }
//    for (int i = 0; i < c; ++i){
//        printf("%i\road",najPole[i]);
//
//    }
        printf("HOTSPOT:%i\n",max);
        return 0;
}

int hodKockami(position,a,b){

    if (position == -1){
        if(a+b > 7)
            return a+b-7+1;
        else
            return 0;
    }
    if(a + b == 12)
        return 12;
    if (a + b == 2)
        return 2;

    if (a >= b)
        return a;
    else
        return b;

}

