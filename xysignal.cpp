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

int cpid,ppid,fd;



void ctop(int sig){
	std::cout<<"parent\n";
	char buffer[100];
	//fgets(buffer, 100, stdin);
	int i=0; char x[1];
	read(fd, x, 1);
	while(x[0]!='\0'&&x[0]!='\n'){
		buffer[i++]=x[0];
		read(fd, x, 1);

	}
	std::cout<<"p "<<buffer<<"\n";
	kill(cpid, SIGUSR2);
}

int main(int argc, char const *argv[])
{
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
		char *argc[4] ;
		argc[0]="./fs2";
		std::cout<<argc[0]<<"\n";
		char ch[10], ch1[10];
		sprintf(ch, "%d", fd);
		argc[1] = ch;
		sprintf(ch1, "%d", ppid);
		argc[2] = ch1;
		//itoa(ppid, argc[2], 10);
		argc[3] = NULL;
		std::cout<<argc[0]<<" "<<argc[1]<<" "<<argc[2]<<"\n";
		execvp(argc[0],argc);
		
		
	}
	
	return 0;
}