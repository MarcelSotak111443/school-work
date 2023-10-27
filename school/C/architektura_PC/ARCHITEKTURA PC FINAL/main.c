
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#pragma comment(lib, "Ws2_32.lib")

void sent(char* buffer,SOCKET connect);
int receive(SOCKET connect);
int ConsoleDimension();
int main() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    printf("columns: %d\n", columns);
    printf("rows: %d\n", rows);

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleOutputCP(CP_UTF8); //prva uloha
    SetConsoleTextAttribute(hConsole,2);//druha uloha

//uvodne nastavovacky

    WSADATA wsaData;    //struktura WSADATA pre pracu s Winsock
    int iResult;

// Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);     //zakladna inicializacia
    if (iResult != 0)     //kontrola, ci nestala chyba
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL;     //struktura pre pracu s adresami
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;     //pracujeme s protokolom TCP/IP


// Resolve the server address and port
    iResult = getaddrinfo("147.175.115.34", "777", &hints, &result);
    if (iResult != 0)     //kontrola, ci nenastala chyba
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    } else
        printf("getaddrinfo didnt fail\n");

    //vytvorenie socketu a pripojenie sa

    SOCKET ConnectSocket = INVALID_SOCKET;

// Attempt to connect to the first address returned by
// the call to getaddrinfo
    ptr = result;

// Create a SOCKET for connecting to server => pokus o vytvorenie socketu
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)     //kontrola, ci nenastala chyba
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    } else
        printf("Error at socket didnt occur\n");

// Connect to server. => pokus o pripojenie sa na server

    iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)     //kontrola, ci nenastala chyba
        printf("Not connected to server…\n");
    else
        printf("Connected to server\n");

    if (iResult == SOCKET_ERROR)    //osetrenie chyboveho stavu
    {
        printf("chybicka");
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }

    Sleep(250);


//posielanie
#define DEFAULT_BUFLEN 4096 //makro, kde definujeme velkost prijimacieho buffera

    char sendbuf[4096] = {}; //buffer (v zasade retazec), kam sa budu ukladat data, ktore chcete posielat
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];

    int width;

    int x=0;
    while (x < 100) {
        x++;


        //posielnie




      //  SetConsoleTextAttribute(hConsole,2);
      //  COORD point = {x,y};                      //             point.X = 39;
      //  SetConsoleCursorPosition(hConsole, point);  // nastavi sa na [39,12]
        width = ConsoleDimension();
        printf("width je %d \n", width);
        for (int j = 0; j < width / 2 + 1; ++j) {
            printf(" ");

        }

        fgets(sendbuf,20, stdin);
        sent(sendbuf,ConnectSocket);


        //prijimanie


         iResult = receive(ConnectSocket);




//        if (strstr(recvbuf,"OutputCP(CP_UTF8)")!=NULL){
//
//            printf("%s", recvbuf);
//        }
         if (iResult == 303){
            int sum;
            int final;
            sum = 1 + 1 + 1 + 4 + 4;
            final = sum % 4;
            printf("vysledok je %i",final);
            sprintf(sendbuf, "%d", final);
            printf("%s",sendbuf);
            sent(sendbuf,ConnectSocket);
            receive(ConnectSocket);
        }
        if (iResult == 460){
            int a= 460/2;
            char PRIMENUMBER[a];
            for (int i = 0;i<a; i++) {
                PRIMENUMBER[i]= recvbuf[i*2+1];
            }
            sent(PRIMENUMBER,ConnectSocket);
            receive(ConnectSocket);

        }



        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);     //prisli validne data, vypis poctu
        else if (iResult == 0)
            printf("Connection closed\n");     //v tomto pripade server ukoncil komunikaciu
        else
            printf("recv failed with error: %d\n", WSAGetLastError());     //ina chyba
//zavretie socketu

//        closesocket(ConnectSocket);
//        WSACleanup();

    }

}

void sent(char* buffer,SOCKET ConnectSocket) {
    int iResult;
    iResult = send(ConnectSocket, buffer, (int) strlen(buffer), 0);
    int kokot = ConsoleDimension();

    for (int j = 0; j < kokot/2+1; ++j) {
        printf(" ");

    }
    for (int i = 0; buffer[i]!='\0'; ++i) {
        printf("%c",buffer[i]);
    }
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        exit(0);
    }
    printf("Bytes Sent: %ld\n", iResult);     //vypisanie poctu odoslanych dat

}

int receive(SOCKET ConnectSocket){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;



#define DEFAULT_BUFLEN 4096 //makro, kde definujeme velkost prijimacieho buffera
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int j=0;
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);     //funkcia na príjimanie

    char *p;
    int a;
    if(strchr(recvbuf, '\n') != NULL){
        p = strchr(recvbuf, '\n');
        printf("%i \n", p - recvbuf + 1);
        a = p - recvbuf + 1;
        *(recvbuf + a) = '\0';}


    if (iResult == 132){
        for (int c = 0; c<132; c++) {
            recvbuf[c]= recvbuf[c] ^ 55;

        }}

    int b=0,i=0;
    for ( i = 0; recvbuf[i] != '\0'; i++) {
        b++;
        if (b > columns/2){
            while (recvbuf[i]!=' '){
                i--;
            }
            b = 0;
            for ( ; j < i; j++) {
                printf("%c",recvbuf[j]);
            }
            recvbuf[j]='\n';
        }
    }
    for ( ; j < i; j++) {
        printf("%c",recvbuf[j]);
    }

    return iResult;


}
int ConsoleDimension(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    printf("columns: %d\n", columns);
    printf("rows: %d\n", rows);
    return columns;
}