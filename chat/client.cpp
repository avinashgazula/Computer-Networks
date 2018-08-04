#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>
#include<string.h>
#include<iostream>


int main(int argc, char const *argv[])
{
	int fd;
	int cd;
	char cfifo[100] = "/home/avinash/Desktop/CN/chat/cfifo";
	char mfifo[50] = "/home/avinash/Desktop/CN/chat/mfifo";
	std::cout << "Enter client id : ";
	char id[5];
	std::cin >> id;
	strcat(cfifo, id);
	int x = mkfifo(cfifo, 0666);
	if(x<0){
		printf("Error in cfifo\n");
		return 0;
	}

	char message[1000];
	fd = open(mfifo, O_WRONLY);
	write(fd, cfifo, strlen(cfifo)+1);
	close(fd);

	cd = open(cfifo, O_RDONLY);
	read(cd, message, sizeof(message));
	printf("Message from server : %s \n",message);
	close(cd);
	while(1){


		printf("Enter a message :");
		scanf("%s", message);
		printf("Input Message %s\n",message);
		fd = open(mfifo, O_WRONLY);
		write(fd, cfifo, strlen(cfifo)+1);
		std::cout<<"Writing message to server\n";
		close(fd);
		fd = open(mfifo, O_WRONLY);
		write(fd, message, strlen(message)+1);
		std::cout<<"message written to server\n";
		close(fd);

		cd = open(cfifo, O_RDONLY);
		read(cd, message, sizeof(message));
		printf("Message from server : %s \n",message);
		close(cd);
	}

	return 0;
}
