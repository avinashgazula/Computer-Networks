#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    //int nsfd = atoi(argv[1]);
    char buffer[100];
    memset(buffer, 0, 100);
    read(0, buffer, sizeof(buffer));
    cout << buffer << endl;
    char *mess = "message accepted by server 1\n";
    send(0, mess, strlen(mess), 0);
    
}