#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>
#include<string.h>


int main(int argc, char const *argv[])
{
	int fd;
	int cd;
	char *cfifo = "/home/cs15/c157118/CN/cfifo";
	char *mfifo = "/home/cs15/c157118/CN/mfifo";
	int x = mkfifo(cfifo, 0666);
	if(x<0){
		printf("Error in cfifo\n");
	}

	char message[100];
	fd = open(mfifo, O_WRONLY);
	write(fd, cfifo, strlen(cfifo)+1);
	close(fd);

	cd = open(cfifo, O_RDONLY);
	read(cd, message, sizeof(message));
	printf("Message from server : %s \n",message);
	close(cd);
	while(1){

		
		fd = open(mfifo, O_WRONLY);
		message[0] = '\0';
		printf("Enter a message :");
		fgets(message, 100, stdin);
		write(fd, message, strlen(message+1));
		close(fd);

		cd = open(cfifo, O_RDONLY);
		read(cd, message, sizeof(message));
		printf("Message from server : %s \n",message);
		close(cd);

	}

	return 0;
}