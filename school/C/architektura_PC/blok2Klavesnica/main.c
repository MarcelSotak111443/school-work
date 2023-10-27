
#include <conio.h> // V tejto kniznici najdete co potrebujete
#include <stdio.h>
#include <windows.h>
#include <time.h>


void navod();
int random();

int main(){

    printf("F1 pre navod \n");
    printf("F2 pre spustenie merania programu \n");
    printf("F10 alebo ESC pre ukoncenie \n");

    char ch;
    do
        {
            if(kbhit())                        // Ak je nieco stlacene
            {
                ch = getch();                 // Tak to nacitame do ch
                switch(ch)                    // A potom testujeme…
                {
                    case 0x00:
                        switch (getch()) {
                            case 59: navod();
                            break;
                            case 60: random();
                            break;
                            case 68: return 0;
                            break;
                            default:printf("vyberte si z ponuky");

                        };
                        default: printf("%c",ch);  // Inac zobraz pismenko
                }
            }
        } while(ch != 27); // Stale dokola, az po <ESC>

        printf("\n\nKoniec\n\n");
        return 0;
    }

    void navod(){
    printf("navod \n");

    printf("pre krok spat stlacne ESC \n");
    while(getch() != 27)
        printf("nezadali ste ESC \n");
    printf("F1 pre navod \n");
    printf("F2 pre spustenie merania programu \n");
    printf("F10 alebo ESC pre ukoncenie \n");

    }

    int random(){
        clock_t start, koniec;   // premenne typu clock_t
        float  trvanie;
        int cislo;

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        for (int j = 0; j < rows/2-3; j++) {
            printf("\n");
        }

        for (int i = 0; i < columns/2-6; i++) {
            printf(" ");
        }
        cislo = rand()%26+96;
        printf("Stlac ");
        printf("%c\n",cislo);

        start = clock();
        while(getch() != cislo)
        {}
        koniec = clock();

        trvanie =(float)(koniec - start);
        printf("\nStlacene %c , ",cislo);
        printf("cas : %f \n",trvanie/1000);

        printf("F1 pre navod \n");
        printf("F2 pre spustenie merania programu \n");
        printf("F10 alebo ESC pre ukoncenie \n");


}





