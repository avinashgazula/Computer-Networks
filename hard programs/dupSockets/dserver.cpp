#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<bits/stdc++.h>

using namespace std;

int nsfd;

void *sendmsg(void *args){
	
	while(1){
		string msg;
		cout<<"Send to Client :-\n";
		getline(cin,msg);
		send(nsfd , msg.c_str() , msg.size() , 0 );
	}
	return NULL;
}

void *recvmsg(void *args){
	
	while(1){
		char buffer[1024] = {};
		recv(nsfd , buffer , 1024 , 0 );
		if(buffer[0] != 0)
		cout<<"Message from Client :- "<<buffer<<endl;
		else
		buffer[0] = 0;
	}
	return NULL;
}

int main(int argc, char **argv){
	
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
	else printf("\n bind successful \n");

	listen(sfd,10);

	

		if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1){
			perror("\n accept ");
			return -1;
		}
		else{
			pid_t pid = fork();
			if(pid > 0){
				close(nsfd);
			}
			else{
				dup2(sfd,0);
				execlp("./service","service",NULL);

			}
		}
	
	return 0;
}
