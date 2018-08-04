#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main()
{
    char *fifo1 = "./myfifo1";
    mkfifo(fifo1, 0666);
    int fd1 = open(fifo1, O_WRONLY);
    while (1)
    {
        write(fd1, "hello1", 7);
        sleep(1);
    }
    close(fd1);
}