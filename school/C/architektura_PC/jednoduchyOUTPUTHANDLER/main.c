#include <stdio.h>
#include <windows.h>

int main() {



    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 51; i++) {

        SetConsoleTextAttribute(hConsole,i/10);
        printf("%0.3d\n",i);
        Sleep(1000);

    }


    return 0;
}
