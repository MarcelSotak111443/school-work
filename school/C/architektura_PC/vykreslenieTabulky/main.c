#include <stdio.h>
#include <windows.h>

const unsigned char RohVpravoDole = 0xd9;

void draw(int number);
void drawVoid(int number, int ArrayLenght);
void chart(char one[],char two[],int velkost, int x , int y);

int main() {


    char zaznam[]="zaznam001";
    char meno[]="Marcel";
    char vyska[]="111cm";
    char hmotnost[]="127kg";
    char Tel[]="0940000940";

    int zaznamLenght = strlen(zaznam);
    int menoLenght = strlen(meno);
    int vyskaLenght = strlen(vyska);
    int hmotnostLenght = strlen(hmotnost);
    int TelLenght = strlen(Tel);

    int x = 10;
    int y = 11;
    int width = 10;
    int totalWidth = 2*width+strlen(zaznam);



    HANDLE  hConsole;                           // ziskanie handle konzoly
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,2);

    COORD point = {x,y};                      //             point.X = 39;

    SetConsoleCursorPosition(hConsole, point);  // nastavi sa na [39,12]
    printf("%c",218);
    draw(width);
    printf("%s",zaznam);
    draw(width-1);
    printf("%c",191);
    printf("\n");
    drawVoid(x,0);
    printf("%c",195);
    draw(totalWidth/2-1);
    printf("%c",194);
    draw(totalWidth/2);
    printf("%c",180);

    chart(meno,"meno",5,x,totalWidth);
    chart(vyska,"vyska",6,x,totalWidth);
    chart(hmotnost,"hmotnost",9,x,totalWidth);

    printf("\n");
    drawVoid(x,0);
    printf("%c",179);
    printf("Tel");
    drawVoid(totalWidth/2,4);
    printf("%c",179);
    printf("%s",Tel);
    drawVoid(totalWidth/2,strlen(Tel));
    printf("%c",179);
    printf("\n");
    drawVoid(x,0);
    printf("%c",192);    // krizovatka
    draw(totalWidth/2-1);
    printf("%c",193);
    draw(totalWidth/2);
    printf("%c",217);


    while (1){}
    point.X = 39; point.Y = 13;                  // ina moznost zadania suradnice
    SetConsoleCursorPosition(hConsole, point);  // nastavi sa na [0,22]


    return(0);
}
void draw(int number){
    for (int i = 0; i < number; i++) {
        printf("%c",196);

    }
}
void drawVoid(int number,int ArrayLenght){
    for (int j = 0; j < number-ArrayLenght; j++) {
        printf(" ");

    }
}
void chart(char one[],char two[],int velkost,int x,int totalWidth){

    int arrayLEnght = strlen(one);
    printf("\n");
    drawVoid(x,0);
    printf("%c",179);
    printf("%s",two);
    drawVoid(totalWidth/2,velkost);
    printf("%c",179);
    printf("%s",one);
    drawVoid(totalWidth/2,arrayLEnght);
    printf("%c",179);
    printf("\n");
    drawVoid(x,0);
    printf("%c",195);    // krizovatka
    draw(totalWidth/2-1);
    printf("%c",197);
    draw(totalWidth/2);
    printf("%c",180);
}