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
		
		//send(nsfd , "accepted" , sizeof("accepted") , 0 );
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

	cout<<"i am in service\n";
	struct sockaddr_in cli_addr;
	socklen_t cli_len;
	while(1){

		if((nsfd = accept(0 , (struct sockaddr *)&cli_addr , &cli_len))==-1){
			perror("\n accept ");
			return -1;
		}
		else{
			pthread_t t0, t1;
			pthread_create(&t0,NULL,sendmsg,NULL);
			pthread_create(&t1,NULL,recvmsg,NULL);
			pthread_join(t0,NULL);
			pthread_join(t1,NULL);
		}
	}
	return 0;
}
