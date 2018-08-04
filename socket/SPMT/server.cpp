#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;
#define PORT 8080

void* ser(void* f){
    //int nsfd = *(int*) f;
    char buffer[100];
    memset(buffer, 0, 100);
    read(0, buffer, sizeof(buffer));
    cout << buffer << endl;
    char *mess = "message accepted by server";
    send(0, mess, strlen(mess), 0);
}

int main()
{
    int sfd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        return 0;
    }

    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("setsockopt error");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(sfd, (struct sockaddr *)&address, addrlen) < 0)
    {
        printf("bind failed");
        return 0;
    }

    if (listen(sfd, 3) < 0)
    {
        printf("listen error");
        return 0;
    }

    while (1)
    {
        int nsfd;
        if ((nsfd = accept(sfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            printf("accept error");
            //printf(errno);
            return 0;
        }

        int c = fork();
        if (c > 0)
        {
            close(nsfd);
        }
        else
        {
            close(sfd);
            dup2(nsfd, 0);
            pthread_t tid;
            pthread_create(&tid, NULL, ser, NULL);
            pthread_join(tid, NULL);


            
        }
    }

}
