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

int sfd;

void *sendmsg(void *args){
	
	while(1){
		string msg;
		cout<<"Send to Client :-\n";
		getline(cin,msg);cout<<msg<<endl;
		send(sfd , msg.c_str() , msg.size() , 0 );
	}
	return NULL;
}

void *recvmsg(void *args){
	
	while(1){
		char buffer[1024] = {};
		recv(sfd , buffer , 1024 , 0 );
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

	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	while(1){
	
		if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
		perror("\n connect : ");
		else {
			pthread_t t0, t1;
			pthread_create(&t0,NULL,sendmsg,NULL);
			pthread_create(&t1,NULL,recvmsg,NULL);
			pthread_join(t0,NULL);
			pthread_join(t1,NULL);
		}
	}
	return 0;
}
