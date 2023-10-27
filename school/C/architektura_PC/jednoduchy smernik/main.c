#include <stdio.h>
#include <string.h>

int main() {
    char retazec[] = "architektura_pocitacov_je_super_predmet_milujem_ho";

    char *smernik = retazec;

    for (int i = 0; i < strlen(retazec); i++) {
        printf("%c",*(smernik+i));
    }
    printf("\n");

    printf("%s \n",smernik);

    printf("pismenko na adrese %d je %c \n",smernik,*smernik);
    smernik++;
    printf("pismenko na adrese %d je %c \n",smernik,*smernik);
    smernik++;
    *smernik= 'F';
    printf("pismenko na adrese %d je %c \n",smernik,*smernik);
    printf("%s \n",smernik);

    int f;
    smernik = 10000;
    *smernik = 5;
    printf("pismenko na adrese %d je %d \n",smernik,*smernik);

    return 0;
}
