#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>


char* functionA(char *line);
char* functionC(char *line);
char* functionU(char *line);
char* functionL(char *line);
char* functionR(char *line,int argc, char *argv[],char *opt);
char* functionRStar(char *line,int argc, char *argv[]);

char *readline() {
    const size_t BSIZE = 100;
    char *line = NULL;
    size_t capacity = 0;

    do {
        // Priprav dostatok pamate.
        capacity += BSIZE;

        // Alokuj miesto na capacity + '\0'.
        line = (char *) realloc(line, (capacity + 1) * sizeof(char));
        if (line == NULL)
            return line;

        // Nacitaj zo vstupu riadok (resp. jeho zvysok).
        if (fgets(line + capacity - BSIZE, BSIZE + 1, stdin) == NULL) {
            free(line);
            return NULL; // doslo k chybe citania alebo sme narazili na EOF
        }
        // Opakuj, pokym sa nenacita cely riadok.
        // Indikacia, ze zostal zvysok riadku:
        //   1. je naplnena cela BSIZE
        //   2. na konci nie je '\n'
    } while (strlen(line + capacity - BSIZE) >= BSIZE
             && line[capacity - 1] != '\n');
    // nacitany riadok obsahuje na konci znak '\n'
    return line;
}

////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int a =0 ,upressed=0,lpressed=0,counter=0;
    char *optargR;
    int detection=0;
    char *line=NULL;
    char atributes[50];

    int opt;
    char *optstring = ":acur:l";

    while ((opt = getopt(argc, argv, optstring)) != -1) {
                switch (opt) {
                    case 'a':
                        atributes[a]='a';
                        a++;
                        counter++;
                        break;
                    case 'c':
                        atributes[a]='c';
                        a++;
                        counter++;
                        break;
                    case 'u':
                        if (lpressed == 0){
                            upressed=1;
                            atributes[a]='u';
                            a++;
                            counter++;}
                        else
                            return 3;
                        break;
                    case 'l':
                        if (upressed == 0){
                            lpressed=1;
                            atributes[a]='l';
                            a++;
                            counter++;}
                        else
                            return 3;
                        break;
                    case 'r':
                        atributes[a]='r';
                        optargR = optarg;
                        a++;
                        counter++;
                        break;
                        default: /* '?' alebo ':' */
                            if (optopt == 'r'){
                                return 2;}

                        return 1;
                }
    }
    a=0;


        while ((line = readline()) != NULL) {
            if (*line == '\n')
                return 0;

            while (a!=counter){
                switch (atributes[a]) {
                    case 'a':
                        line = functionA(line);

                        a++;
                        break;
                    case 'c':
                        line = functionC(line);

                        a++;
                        break;
                    case 'u':
                        line = functionU(line);
                        a++;
                        break;
                    case 'l':
                        line = functionL(line);
                        a++;
                        break;
                    case 'r':
                        line = functionR(line,argc,argv,optargR);
                        detection = 1;
                        a++;
                        break;
                    default:
                        a++;
                        break;

                }

                }
            if (detection != 1){
                   line = functionRStar(line,argc,argv);
                   detection = 0;
                }


           printf("%s\n",line);

            a = 0;
            free(line);


        }
//        if (optind < argc) {
//            for (int i = optind; i < argc; i++) {
//                printf("Non-option CMD argument: %s\n", argv[i]);
//            }
//        }
        free(line);
        return 0;
    }
char* functionA(char *line){
    int i ;
    for (i = 0; i < strlen(line); i++) {
        if (*(line + i) >= 65 && *(line + i) <= 90 || (*(line + i) >= 97 && *(line + i) <= 122)&& !(line[i] == '\0'))
            line[i]=line[i];
        else
            line[i]=' ';
            }


    return line;


}
char* functionC(char *line) {

    for (int i = 0,j = 0; line[i+1] != '\0'; i++) {


        while (!(line[i] >= 65 && line[i] <= 90) && !(line[i] >= 97 && line[i] <= 122) && !(line[i] == '\0')) {
            for (j = i; line[j+1] != '\0'; ++j) {

                line[j] = line[j+1];
            }
            line[j] = '\0';
        }
    }

    return line;
}
char* functionU(char *line){
    int i=0;
    for (i = 0; i < strlen(line); i++) {
        if ( (*(line + i) >= 97 && *(line + i) <= 122)){
            line[i]=line[i]-32;
        }

    }
    line[i]='\0';
    return line;
}
char* functionL(char *line) {
    int i = 0;
    for (i = 0; i < strlen(line); i++) {
        if (*(line + i) >= 65 && *(line + i) <= 90 ){
            line[i]=line[i]+32;
        }

    }
    line[i]='\0';
    return line;
}
char* functionR(char *line,int argc, char *argv[],char *optargG){


    int j=0;

    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-u") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-r") != 0){
            strcpy(argv[j],*(argv+i));
            j++;
        }
    }
    optargG = argv[0];
    argc = j;

    char* result;
    int i, cnt = 0;
    int mallocc = strlen(line);
    int oldWlena;
    int oldWlenb;
    int oldWlenc;
    int oldWlend;
    int oldWlene;
    int oldWlenf;
    int oldWleng;
    int oldWlenh;
    int oldWleni;
    int oldWlenj;

    int newWlen = strlen(optargG);
    int oldWlen = strlen(argv[0]);

    if (argc > 1)
        oldWlena = strlen(argv[1]);
    if (argc > 2)
        oldWlenb = strlen(argv[2]);
    if (argc > 3)
        oldWlenc = strlen(argv[3]);
    if (argc > 4)
        oldWlend = strlen(argv[4]);
    if (argc > 5)
        oldWlene = strlen(argv[5]);
    if (argc > 6)
        oldWlenf = strlen(argv[6]);
    if (argc > 7)
        oldWleng = strlen(argv[7]);
    if (argc > 8)
        oldWlenh = strlen(argv[8]);
    if (argc > 9)
        oldWleni = strlen(argv[9]);
    if (argc > 10)
        oldWlenj = strlen(argv[10]);


    // Counting the number of times old word
    // occur in the string
    for (i = 0; line[i] != '\0'; i++) {
        if (argc>0){
            if (strstr(&line[i], argv[0]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlen;
                i += oldWlen - 1;
            }}
        if (argc>1){
            if (strstr(&line[i], argv[1]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlena;
                i += oldWlena - 1;}
        }
        if (argc>2){
            if (strstr(&line[i], argv[2]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlenb;
                i += oldWlenb - 1;}
        }
        if (argc>3){
            if (strstr(&line[i], argv[3]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlenc;
                i += oldWlenc - 1;}
        }
        if (argc>4){
            if (strstr(&line[i], argv[4]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlend;
                i += oldWlend - 1;}
        }
        if (argc>5){
            if (strstr(&line[i], argv[5]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlene;
                i += oldWlene - 1;}
        }
        if (argc>6){
            if (strstr(&line[i], argv[6]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlenf;
                i += oldWlenf - 1;}
        }
        if (argc>7){
            if (strstr(&line[i], argv[7]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWleng;
                i += oldWleng - 1;}
        }
        if (argc>8){
            if (strstr(&line[i], argv[8]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlenh;
                i += oldWlenh - 1;}
        }
        if (argc>9){
            if (strstr(&line[i], argv[9]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWleni;
                i += oldWleni - 1;}
        }
        if (argc>10){
            if (strstr(&line[i], argv[10]) == &line[i]) {
                mallocc = mallocc + newWlen - oldWlenj;
                i += oldWlenj - 1;}
        }

    }

    // Making new string of enough length
    result = (char*)malloc( mallocc + 1);  //i + cnt * (newWlen - oldWlen)

    i = 0;
    while (*line) {
        // compare the substring with the result
        switch (argc) {
            case 11:
                if (strstr(line, argv[10]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlenj;
                    break;}
            case 10:
                if (strstr(line, argv[9]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWleni;
                    break;}
            case 9:
                if (strstr(line, argv[8]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlenh;
                    break;}
            case 8:
                if (strstr(line, argv[7]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWleng;
                    break;}
            case 7:
                if (strstr(line, argv[6]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlenf;
                    break;}
            case 6:
                if (strstr(line, argv[5]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlene;
                    break;}
            case 5:
                if (strstr(line, argv[4]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlend;
                    break;}
            case 4:
                if (strstr(line, argv[3]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlenc;
                    break;}
            case 3:
                if (strstr(line, argv[2]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlenb;
                    break;}
            case 2:if (strstr(line, argv[1]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlena;
                    break;}
            case 1:if (strstr(line, argv[0]) == line) {
                    strcpy(&result[i], optargG);
                    i += newWlen;
                    line += oldWlen;
                    break;}
            default:result[i++] = *line++;
        }
    }

    result[i-1]='\0';
    return result;
}

char* functionRStar(char *line,int argc, char *argv[]) {
    int j=0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-u") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-r") != 0){
            strcpy(argv[j],*(argv+i));
            j++;
        }
    }


    argc = j;

    char *result=NULL;
    int i, cnt = 0;
    int mallocc = strlen(line);

    result = (char *) malloc(strlen(line));  //i + cnt * (newWlen - oldWlen)
    i = 0;


    while (*line) {
        // compare the substring with the result
        switch (argc) {
            case 12:
                if (strstr(line, argv[11]) == line) {
                    for (int j = 0; j < strlen(argv[11]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 11:
                if (strstr(line, argv[10]) == line) {
                    for (int j = 0; j < strlen(argv[10]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 10:
                if (strstr(line, argv[9]) == line) {
                    for (int j = 0; j < strlen(argv[9]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 9:
                if (strstr(line, argv[8]) == line) {
                    for (int j = 0; j < strlen(argv[8]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 8:
                if (strstr(line, argv[7]) == line) {
                    for (int j = 0; j < strlen(argv[7]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 7:
                if (strstr(line, argv[6]) == line) {
                    for (int j = 0; j < strlen(argv[6]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 6:
                if (strstr(line, argv[5]) == line) {
                    for (int j = 0; j < strlen(argv[5]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 5:
                if (strstr(line, argv[4]) == line) {
                    for (int j = 0; j < strlen(argv[4]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 4:
                if   (strstr(line, argv[3]) == line) {
                        for (int j = 0; j < strlen(argv[3]); j++) {
                            strcpy(&result[i], "*");
                            i += 1;
                            line += 1;}
                        break;}
            case 3: if (strstr(line, argv[2]) == line) {
                    for (int j = 0; j < strlen(argv[2]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 2: if (strstr(line, argv[1]) == line) {
                    for (int j = 0; j < strlen(argv[1]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            case 1:
                if (strstr(line, argv[0]) == line) {
                    for (int j = 0; j < strlen(argv[0]); j++) {
                        strcpy(&result[i], "*");
                        i += 1;
                        line += 1;}
                    break;}
            default:result[i++] = *line++;
        }
    }
    result[i-1]='\0';
    return result;

}



