#include <stdio.h>

int primeFactors(int a , int b);
int skuska(int a);
int main() {

    int a,b;

    scanf("%d",&a);

    scanf("%d",&b);
    if(a < 1){
        printf("ERROR");
        return 1;
    }
    primeFactors(a,b);
    return 0;
}
int primeFactors(int a,int b){
    int d=0;

    for (int i = 2; i <= a; i++) {
        if(a % i == 0){

            if(skuska(i)==1){
                if(d < b)
                {
                    printf(" %d \n",i);
                    d++;
                }
            }
        }

    }
}
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