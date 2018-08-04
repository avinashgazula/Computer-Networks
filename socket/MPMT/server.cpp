#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;
#define PORT1 8080
#define PORT2 8081

void *ser1(void *f)
{
    //int nsfd = *(int*) f;
    char buffer[100];
    memset(buffer, 0, 100);
    read(0, buffer, sizeof(buffer));
    cout << buffer << endl;
    char *mess = "message accepted by server 1\n";
    send(0, mess, strlen(mess), 0);
}

void *ser2(void *f)
{
    //int nsfd = *(int*) f;
    char buffer[100];
    memset(buffer, 0, 100);
    read(0, buffer, sizeof(buffer));
    cout << buffer << endl;
    char *mess = "message accepted by server 2\n";
    send(0, mess, strlen(mess), 0);
}

int main()
{
    int sfd1, sfd2;
    struct sockaddr_in address1, address2;
    int opt = 1;
    int addrlen1 = sizeof(address1);
    int addrlen2 = sizeof(address2);

    if ((sfd1 = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket1 failed");
        return 0;
    }

    if (setsockopt(sfd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("setsockopt1 error");
        return 0;
    }

    address1.sin_family = AF_INET;
    address1.sin_addr.s_addr = INADDR_ANY;
    address1.sin_port = htons(PORT1);

    if (bind(sfd1, (struct sockaddr *)&address1, addrlen1) < 0)
    {
        printf("bind1 failed");
        return 0;
    }

    if (listen(sfd1, 10) < 0)
    {
        printf("listen1 error");
        return 0;
    }

    if ((sfd2 = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket2 failed");
        return 0;
    }

    if (setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("setsockopt2 error");
        return 0;
    }

    address2.sin_family = AF_INET;
    address2.sin_addr.s_addr = INADDR_ANY;
    address2.sin_port = htons(PORT2);

    if (bind(sfd2, (struct sockaddr *)&address2, addrlen2) < 0)
    {
        printf("bind2 failed");
        return 0;
    }

    if (listen(sfd2, 10) < 0)
    {
        printf("listen2 error");
        return 0;
    }
    struct timeval tval;
    tval.tv_sec = 1;
    tval.tv_usec = 0;

    while (true)
    {
        //cout<<"in loop\n";
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sfd1, &readfds);
        FD_SET(sfd2, &readfds);
        //cout<<sfd1<<" "<<sfd2<<endl;
        int n;
        n = select(100, &readfds, NULL, NULL, NULL);
        //cout << "n " << n << endl;

        if (FD_ISSET(sfd1, &readfds))
        {
            cout << "sfd1\n";
            //while (1)
            {
                int nsfd;
                if ((nsfd = accept(sfd1, (struct sockaddr *)&address1, (socklen_t *)&addrlen1)) < 0)
                {
                    //printf("accept error");
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
                    close(sfd1);
                    dup2(nsfd, 0);
                    pthread_t tid;
                    pthread_create(&tid, NULL, ser1, NULL);
                    pthread_join(tid, NULL);
                }
            }
        }
        if (FD_ISSET(sfd2, &readfds))
        {
            cout << "sfd2\n";
            //while (1)
            {
                int nsfd;
                if ((nsfd = accept(sfd2, (struct sockaddr *)&address2, (socklen_t *)&addrlen2)) < 0)
                {
                    //printf("accept error");
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
                    close(sfd2);
                    dup2(nsfd, 0);
                    pthread_t tid;
                    pthread_create(&tid, NULL, ser2, NULL);
                    pthread_join(tid, NULL);
                }
            }
        }
    }
}
