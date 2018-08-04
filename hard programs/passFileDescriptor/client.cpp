#include<bits/stdc++.h>
#include<time.h>
#include<stdio.h>
#include<semaphore.h>
#include<string.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
#include<net/ethernet.h>
#include<netinet/if_ether.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/un.h>
#include<sys/shm.h>

using namespace std;

int sfd;

void *senderfn(void *param)
{


	string buffer;

	while(1)
	{
		cout<<"Message to Server :- ";
		getline(cin, buffer);
		send(sfd, buffer.c_str(), buffer.size(), 0);
	}
	pthread_exit(0);
}

void *receiverfn(void *param)
{
	char buffer[1000] = {};
	while(1)
	{
		recv(sfd, buffer, 1000, 0);
		if(buffer[0] != 0)
		cout<<"From Server :- "<<buffer<<endl;
		buffer[0] = 0;
	}
	pthread_exit(0);
}

int main(int argc, char **argv){
	
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else {
		
		pthread_t receiver, sender;

		pthread_create(&receiver, NULL, receiverfn, NULL);
		pthread_create(&sender, NULL, senderfn, NULL);


		pthread_join(receiver, NULL);
		pthread_join(sender, NULL);
	};
	return 0;
}
