#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>
#include<string.h>
#include<iostream>

void capitalise(char message[]){
	for(int i=0; message[i]!='\0'; i++){
		if(message[i]>='a'&&message[i]<='z')
			message[i]+='A'-'a';
	}
}

int main(int argc, char const *argv[])
{
	int fd;
	int cd;
	char mfifo[50] = "/home/avinash/Desktop/CN/chat/mfifo";
	int x = mkfifo(mfifo, 0666);
	if(x<0){
		printf("Error in mfifo\n");
		return 0;
	}
	
	char path[100]="";
	while(1){
		std::cout<<"start\n";
		char message[1000];
		fd = open(mfifo, O_RDONLY);
		read(fd, message, sizeof(message));
		close(fd);
		std::cout<<"message : "<<message<<"\n";
		if(message[0]=='/'){
			std::cout<<"path : "<<path<<"\n";
			if(strcmp(path,message)){
				strcpy(path, message);
				std::cout<<"1\n";
				close(cd);
				std::cout<<"1.\n";
				cd = open(path, O_WRONLY);
				std::cout<<"2\n";
				if(cd>=0){
					std::cout<<"Connected to "<<path<<"\n";
					write(cd, "access granted\n", 16);
				}
				close(cd);
			}
		}
		else{
			capitalise(message);
			printf("capitalised message %s\n",message );
			cd = open(path, O_WRONLY);
			write(cd, message, strlen(message)+1);
			close(cd);
		}
	}
	
	return 0;
}
