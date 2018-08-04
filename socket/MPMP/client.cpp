#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
using namespace std;
#define PORT1 8080
#define PORT2 8081

int main()
{
    int csfd;
    struct sockaddr_in address;
    struct sockaddr_in server_address;
    char id[10];
    cout << "Enter id : ";
    cin >> id;

    int sno;
    cout << "Enter server 1 or 2 : ";
    cin >> sno;
    if ((csfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error");
        return -1;
    }
    memset(&server_address, '0', sizeof(server_address));

    server_address.sin_family = AF_INET;
    if (sno == 1)
        server_address.sin_port = htons(PORT1);
    else if (sno == 2)
        server_address.sin_port = htons(PORT2);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((connect(csfd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    else
    {
        char mess[50] = "Message from client";
        strcat(mess, id);
        send(csfd, mess, strlen(mess), 0);
        char buffer[100];
        read(csfd, buffer, sizeof(buffer));
        cout << buffer << endl;
    }
}