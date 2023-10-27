#include <stdio.h>

int operacie(int a, int b);
int gcc(int a,int b);
int podiel(int a,int b);
//int spolocnyMenovatel(int a,int b,int c,int d);
//int najvacsiDelitelVacsi(int a,int b);
int PrvociselnyDelitel(int a);
int skuska(int a);
int main() {

    int a,b,c,d;
    printf("napiste 1 cislo \n");
    scanf("%d",&a);
    printf("napiste 2 cislo \n");
    scanf("%d",&b);
    /*printf("napiste 3 cislo \n");
    scanf("%d",&c);
    printf("napiste 4 cislo \n");
    scanf("%d",&d);*/

   // najvacsiDelitelVacsi(a,b);
    //spolocnyMenovatel(a,b,c,d);
    PrvociselnyDelitel(a);
    operacie(a, b);
    podiel(a,b);
    return 0;
}

int operacie(int a,int  b){
    printf("nasobenie je %d\n",a*b);
    printf("delenie je %d \n",a/b);
    printf("scinanie je %d \n",a+b);
    printf("odcitanie je %d \n",a-b);

}
int gcc(int a, int b){
    int c,d;
    if (a>b)
        c = a;
    else
        c = b;
    d = c;
    for (int i = 0; i < c; i++) {

        if(a % d == 0 && b % d ==0)
            return d;
        d--;
    }
}

int podiel(int a,int b){
    int c,d,delitel;
    d = a / b;
    c = (a%b);
   // printf("vysledne cislo je %d ",d);
    delitel = gcc(c,b);
    c = c/delitel;
    b = b/delitel;
   // printf("+ %d",c);
   // printf(" / %d",b);
}
/*
int spolocnyMenovatel(int a,int b,int c,int d){
    int e,f;
    e = gcc(a,b);
    f = gcc(c,d);
        printf("spolocny delitel 1 je %d ", e);
        printf("spolocny delitel 2 je %d ", f);

        printf("%d /",(a/e)*(d/f));
        printf("%d  -  ",(b/e)*(d/f));
        printf("%d /",(c/f)*(b/e));
        printf("%d",(d/f)*(b/e));


}*/
/*int najvacsiDelitelVacsi(int a,int b){

    int d=a,e,g=9;
    int f[9];

    for (int i = 0; i < a; i++) {
        if(a % d == 0){
            e = d;
            f[g]=e;
            printf("halo halo %d",f[g]);
            g--;
            if (b % d == 0){
                if (d != a)
                    printf("toto je cislo %d",f[g+2]);
                else
                    printf("%d",d);
            }
        }
        d--;
}
}*/
int skuska(int p){
    int q = p,s=0;

    for (int i = 0; i < p; i++) {

        if(p % q == 0){

            s=s+1;

        }
        q--;

}

    if (s > 2)
        return 0;
    else
        return 1;}

int PrvociselnyDelitel(int a){
    int b = a,d=0;

    for (int i = 0; i < a; i++) {
        if(a % b == 0){

            if(skuska(b)==1){

            }

        }
        b--;
}

}

