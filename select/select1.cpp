#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

void *s1(void *x)
{
    cout << "in s1\n";
}

void *s2(void *x)
{
    cout << "in s2\n";
}

void *s3(void *x)
{
    cout << "in s3\n";
}

int main()
{
    struct timeval tval;
    tval.tv_sec = 1;
    tval.tv_usec = 0;
    char *fifo1 = "./myfifo1";
    char *fifo2 = "./myfifo2";
    cout<<"Hello\n";
    while (true)
    {
        cout<<"yoyo\n";
        int fd1 = open(fifo1, O_RDONLY);
        int fd2 = open(fifo2, O_RDONLY);
        cout<<"fd1 "<<fd1<<endl;
        cout<<"fd2 "<<fd2<<endl;
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fd1, &readfds);
        FD_SET(fd2, &readfds);
        int n = select(5, &readfds, NULL, NULL, &tval);
        cout<<"n "<<n<<endl;
        if (FD_ISSET(fd1, &readfds))
        {
            char a[100];
            read(fd1, a, 7);
            cout<<"t1 "<<a<<endl;
            sleep(2);
        }
        if (FD_ISSET(fd2, &readfds))
        {
            char a[100];
            read(fd2, a, 7);
            cout<<"t2 "<<a<<endl;
            sleep(2);
        }
        close(fd1);
        close(fd2);
    }

}