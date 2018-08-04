#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include<iostream>
#include<fcntl.h>
#include<stdlib.h>

#define xysem1 "xysem1"
#define xysem2 "xysem2"

int ppid; 

void ptoc(int sig){
	std::cout<<"child\n";
	sem_t *x,*y;
	x = sem_open(xysem1, 0);
	y = sem_open(xysem2, 0);
	sem_post(y);
	int y_val[2];
	sem_getvalue(y,y_val);
	sem_init(x, 0, y_val[0]);
	std::cout<<"p1 "<<" x:"<<y_val[0]<<" y:"<<y_val[0]<<"\n";
	sleep(2);
	kill(ppid, SIGUSR1);
}

int main(int argc,char *argv[]){

	std::cout<<"in p2\n";
	//p = atoi(argv[]);
	ppid = atoi(argv[1]);
	signal(SIGUSR2, ptoc);
	//int y = kill(ppid, SIGUSR1);
	while(1);

}