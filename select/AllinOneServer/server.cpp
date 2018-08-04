#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>
using namespace std;
int* shm_arr;
void handler(int sig){
    int c = fork();
    if(c>0){

    }
    else{
        char* argv[2];
        argv[0]="./client";
        argv[1]=NULL;
        execvp(argv[0], argv);
    }
}

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
    char *fifo2 = "./cfifo";
    //cout << "Hello\n";
    int pipefd[2];
    pipe(pipefd);
    int kfd = open("kbd.txt", O_RDONLY);
    
    signal(SIGUSR1, handler);
    size_t size;
    key_t mykey;
    int shmid,pid;
    pid = getpid();
    size = 4*sizeof(int);
    mykey = ftok(".",'x');
    shmid = shmget(mykey, size, IPC_CREAT|0666);
    shm_arr = (int*)shmat(shmid,NULL,0);
    shm_arr[0] = pid;


    int c = fork();
    if (c > 0)
    {
        while (true)
        {
            //cout << "yoyo\n";

            int fifofd = open(fifo2, O_RDONLY);
            cout << "kfd " << kfd << "\t";
            cout << "pipefd[0] " << pipefd[0] << "\t";
            cout << "fifofd " << fifofd << endl;
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(kfd, &readfds);
            FD_SET(pipefd[0], &readfds);
            FD_SET(fifofd, &readfds);
            int n = select(7, &readfds, NULL, NULL, &tval);
            cout << "n " << n << endl;
            if (FD_ISSET(kfd, &readfds))
            {
                char ab[100];
                memset(ab,0,100);
                int p=read(kfd, ab, 5);
                if(p>0)
                cout << "keyboard " << ab << endl;
                sleep(1);
            }
            if (FD_ISSET(pipefd[0], &readfds))
            {
                char a[100];
                memset(a,0,100);
                read(pipefd[0], a, 13);
                cout << "pipe " << a << endl;
                sleep(1);
            }
            if (FD_ISSET(fifofd, &readfds))
            {
                char a[100];
                memset(a,0,100);
                read(fifofd, a, 7);
                cout << "fifo " << a << endl;
                sleep(1);
            }
            sleep(1);
            close(fifofd);
        }
    }
    else
    {
        while (true)
        {
            write(pipefd[1], "pipe_message", 13);
            sleep(1);
        }
    }

    /* pthread_t t[3];
    pthread_create(&t[0],NULL,s1,NULL); 
    pthread_create(&t[1],NULL,s2,NULL);
    pthread_create(&t[2],NULL,s3,NULL);
    pthread_join(t[0],NULL);
    pthread_join(t[1],NULL);
    pthread_join(t[2],NULL);*/
}