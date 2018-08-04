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
int main(){
    size_t size;
    key_t mykey;
    int shmid,pid;
    pid = getpid();
    size = 4*sizeof(int);
    mykey = ftok(".",'x');
    shmid = shmget(mykey, size, IPC_CREAT|0666);
    shm_arr = (int*)shmat(shmid,NULL,0);

    while(1){
        int n;
        cout<<"Enter 1 to signal\n";
        cin>>n;
        if(n==1)
        kill(shm_arr[0], SIGUSR1);
    }
}