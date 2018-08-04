#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>

#define ADDRESS "mysocket"
int* shm_arr;

int main(int argc, char *argv[])
{

    size_t size;
    key_t mykey;
    int shmid,pid;
    pid = getpid();
    size = 6*sizeof(int);
    mykey = ftok(".",'x');
    shmid = shmget(mykey, size, IPC_CREAT|0666);
    shm_arr = (int*)shmat(shmid,NULL,0);
    shm_arr[0] =1;
    shm_arr[5] = 2;


    if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept ");
	else printf("\n accept successful");

    while(1){
        char buf[10];
        recv(nsfd, buf, 10, 0);
        printf("%s\n", buf);
    }



    //printf("x %d", x);
}
