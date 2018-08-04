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
    char *fifo2 = "./myfifo2";
    mkfifo(fifo2, 0666);
    int fd2 = open(fifo2, O_WRONLY);
    while (true)
    {
        write(fd2, "hello2", 7);
        sleep(1);
    }
    close(fd2);
}