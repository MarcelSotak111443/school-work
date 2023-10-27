#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int numberLenght(int number);

int main() {
    char binary[100],binaryReversed[100],hexadecimal[100],hexadecimalReversed[100];
    int b = 0,c = 0,i=0,ch=0;  //pomocne do retazcov a tak
    int currentNumber,vyskaMocniny,lenghtOfNumber, sizeOfArray=0,number;
    char zvysok;
    int MainNumber = 'x';  //pre x staci prepisat 33777 na 'x'
    bool s = false;

    lenghtOfNumber = numberLenght(MainNumber); //zisti dlzku cisla
    vyskaMocniny = lenghtOfNumber;
    printf("cislo v desiatkovej sustave je :  ");
    for (int i = 1; i <= lenghtOfNumber; i++) {      //pre kazde cislo urob
        currentNumber =  MainNumber / (pow(10,lenghtOfNumber-i));   //zisti cislo na danej pozicii
        currentNumber = currentNumber % 10;                                //zisti cislo na danej pozicii
        printf("%d",currentNumber);
        printf("*10^%d",--vyskaMocniny);
        if(vyskaMocniny != 0){                                             //aby sa na konci nevypisalo +
            printf(" + ");
        }
    }
    number = MainNumber;
    printf("\n");
    while (number != 0){                                                   //ak je zvysok zapis ho do retazca pokial cislo neni 0
        if (number % 2 == 1){
            binary[i]= '1';
        } else{
            binary[i]= '0';
        }
        i++;
        number = number / 2;
    }
    b=i;
    for (c = 0; c < i; c++){                                             // reversed retazec
        b = b - 1;
        binaryReversed[c]=binary[b];
    }
    printf("zapis v binarnej sustave je:  ");                 // vypis retazec
    for (c = 0; c < i; c++) {
        printf("%c", binaryReversed[c]);
    }
    ///////////
    while (MainNumber != 0){                                          //to iste ako pri dvojkovej ale s1 16
        zvysok = MainNumber % 16;
        if(zvysok==1) zvysok = '1';
        if(zvysok==2) zvysok = '2';
        if(zvysok==3) zvysok = '3';
        if(zvysok==4) zvysok = '4';
        if(zvysok==5) zvysok = '5';
        if(zvysok==6) zvysok = '6';
        if(zvysok==7) zvysok = '7';
        if(zvysok==8) zvysok = '8';
        if(zvysok==9) zvysok = '9';
        if(zvysok==10) zvysok = 'A';
        if(zvysok==11) zvysok = 'B';
        if(zvysok==12) zvysok = 'C';
        if(zvysok==13) zvysok = 'D';
        if(zvysok==14) zvysok = 'E';
        if(zvysok==15) zvysok = 'F';

        hexadecimal[ch]= zvysok;
        ch++;
        MainNumber = MainNumber / 16;
    }
    b=ch;
    for (c = 0; c < ch; c++){
        b = b - 1;
        hexadecimalReversed[c]=hexadecimal[b];
    }
    printf("\n zapis v hexadecimalnej sustave je:  ");
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