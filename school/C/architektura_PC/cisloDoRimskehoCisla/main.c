#include <stdio.h>
#include <math.h>

#include <aclapi.h>

int numberLenghtGet(int number);

int main() {

    int number,numberLenght,currentNumber,numberLenghtVariable;
    int X=0,L=0,V=0,I=0;
    printf("Zadaj cislo \n");
    scanf("%d",&number);
    numberLenght = numberLenghtGet(number);   //zisti dlzku cisla
    numberLenghtVariable = numberLenght;
    for (int i = 1; i <= numberLenght; i++) {
        currentNumber = number / (pow(10, numberLenght - i));   //zisti cislo na danej pozicii od najvysssieho
        currentNumber = currentNumber % 10;
        if (numberLenghtVariable==1){
            for (int j = 0; j < currentNumber; j++) {
                I= I + 1;
                }
            if (I > 8) {
                printf("IX");
                I = I - 9;
            }
            if (I > 3 && I < 5){
                printf("IV");
                I = I - 4;
            }
            else{
                if(I > 4){
                    V = V + 1;
                    I = I - 5;
                }
            }
            numberLenghtVariable--;
            for (int m = 0; m < V; m++){
                printf("V");
            }
            for (int n = 0; n < I; n++) {
                printf("I");
            }
        }
        if (numberLenghtVariable==2){                     //ak ma cislo 2 cisla
            for (int k = 0; k < currentNumber; k++) {
                X = X + 1;
            }
            if (X > 8) {
                printf("XC");
                X = X - 9;
            }
            if (X > 3 && X < 5){
                printf("XL");
                X = X - 4;
                }
            else{
                if (X > 4){
                    L = L+1;
                    X = X - 5;
                }
            }
            numberLenghtVariable--;                 //vypis podla premennych
            for (int k = 0; k < L; k++) {
                printf("L");
            }
            for (int l = 0; l < X ; l++){
                printf("X");
            }
        }
        if(numberLenght == 3){
            printf("C");
            exit(0);
        }
    }
    return 0;
}
int numberLenghtGet(int number){
    printf("cislo je %d \n",number);
    if(number / 10 == 0) return 1;
    if(number / 100 == 0) return 2;
    if(number / 1000 == 0) return 3;
    if(number / 10000 == 0) return 4;
    if(number / 100000 == 0) return 5;

}