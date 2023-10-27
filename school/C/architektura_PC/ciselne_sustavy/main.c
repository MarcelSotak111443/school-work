#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int numberLenght(int number);

int main() {
    char binary[100],binaryReversed[100],hexadecimal[100],hexadecimalReversed[100];
    int b = 0,c = 0,i=0,ch=0,lenghtOfNumber;
    int currentNumber,square;
    int sizeOfArray=0;
    char residue;
    //long int binary;
    int MainNumber = 33777,number;  //pre x staci prepisat 33777 na 'x'
    bool s = false;

    lenghtOfNumber = numberLenght(MainNumber);
    square = lenghtOfNumber;
    printf("cislo v desiatkovej sustave je :  ");
    for (int i = 1; i <= lenghtOfNumber; i++) {
        currentNumber =  MainNumber / (pow(10,lenghtOfNumber-i));
        currentNumber = currentNumber % 10;
        printf("%d",currentNumber);
        printf("*10^%d",--square);
        if(square != 0){
            printf(" + ");
        }
    }
    number = MainNumber;
    printf("\n");
    while (number != 0){
        if (number % 2 == 1){
            binary[i]= '1';
        } else{
            binary[i]= '0';
        }
        i++;
        number = number / 2;
    }
    b=i;
    for (c = 0; c < i; c++){
        b = b-1;
        binaryReversed[c]=binary[b];
    }
    printf("zapis v binarnej sustave je:  ");
    for (c = 0; c < i; c++) {
        printf("%c", binaryReversed[c]);
    }
    printf("\n velkost pola je %d",i);


    ///////////
    printf("cislo je %d",MainNumber);
    while (MainNumber != 0){
        residue = MainNumber % 16;

        if(residue == 1) residue = '1';
        if(residue == 2) residue = '2';
        if(residue == 3) residue = '3';
        if(residue == 4) residue = '4';
        if(residue == 5) residue = '5';
        if(residue == 6) residue = '6';
        if(residue == 7) residue = '7';
        if(residue == 8) residue = '8';
        if(residue == 9) residue = '9';
        if(residue == 10) residue = 'A';
        if(residue == 11) residue = 'B';
        if(residue == 12) residue = 'C';
        if(residue == 13) residue = 'D';
        if(residue == 14) residue = 'E';
        if(residue == 15) residue = 'F';

        hexadecimal[ch]= residue;
        ch++;
        MainNumber = MainNumber / 16;
    }
    b=ch;
    for (c = 0; c < ch; c++){
        b = b-1;
        hexadecimalReversed[c]=hexadecimal[b];
    }
    printf("zapis v hexadecimalnej sustave je:  ");
    for (c = 0; c < ch; c++) {
        printf("%c", hexadecimalReversed[c]);
    }
    return 0;
}
int numberLenght(int number){
    printf("cislo je %d \n",number);
    if(number / 10 == 0) return 1;
    if(number / 100 == 0) return 2;
    if(number / 1000 == 0) return 3;
    if(number / 10000 == 0) return 4;
    if(number / 100000 == 0) return 5;

}