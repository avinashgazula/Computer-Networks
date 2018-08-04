#include<bits/stdc++.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include<iostream>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

#define xysem1 "xysem1"
#define xysem2 "xysem2"

int cpid,ppid,fd;
sem_t *x, *y;


void ctop(int sig){
	std::cout<<"parent\n";
	sem_post(x);
	int x_val[2];
	sem_getvalue(x,x_val);
	sem_init(y, 0, x_val[0]);
	std::cout<<"p1 "<<" x:"<<x_val[0]<<" y:"<<x_val[0]<<"\n";
	sleep(2);
	kill(cpid, SIGUSR2);
}

int main(int argc, char const *argv[])
{
	x = sem_open(xysem1, O_CREAT, 0644, 1);
	y = sem_open(xysem2, O_CREAT, 0644, 1);

	sem_init(x, 0, 0);
	sem_init(y, 0, 0);

	int x_val[2];
	sem_getvalue(x,x_val);
	int y_val[2];
	sem_getvalue(y,y_val);
	std::cout<<"p1 "<<" x:"<<x_val[0]<<" y:"<<y_val[0]<<"\n";

	fd = open("myfile.txt", O_RDONLY);
	int c = fork();
	
	if(c>0){
		//dup2(fd1,0);
		std::cout<<"in parent\n";
		cpid = c;
		signal(SIGUSR1, ctop);
		sleep(4);
		int x = kill(cpid, SIGUSR2);
		while(1);
	}
	else{
		std::cout<<"in child\n";
		ppid = getppid();
		//dup2(fd,0);
		char *argc[3] ;
		argc[0]="./xy2";
		//std::cout<<argc[0]<<"\n";
		char ch1[10];
		sprintf(ch1, "%d", ppid);
		argc[1] = ch1;
		//itoa(ppid, argc[2], 10);
		argc[2] = NULL;
		//std::cout<<argc[0]<<" "<<argc[1]<<" "<<argc[2]<<"\n";
		execvp(argc[0],argc);
		
		
	}
	
	return 0;
}