#include <bits/stdc++.h>
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

int rsfd;
struct sockaddr_in addr;
socklen_t len = sizeof(addr);

void *sendmsg(void *args){
	
	char buffer[1024] = {};
	while(1){
		cout<<"Enter message :-\n";
		cin.getline(buffer, 1024);
		sendto(rsfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
	}	
	pthread_exit(0);
}

void *recvmsg(void *args){
	
	char buffer[1024] = {};
	while(1){
		recvfrom(rsfd, buffer, 1024, 0, (struct sockaddr*)&addr, &len);
		if(buffer[0] != 0){
			char *msg = (char *)(buffer + sizeof(struct ip));
			cout<<"Message :-\n"<<msg<<endl;
		}
		else
		buffer[0] = 0;
	}	
	pthread_exit(0);
}

int main(int argc, char **argv){
	
	if((rsfd = socket(AF_INET, SOCK_RAW, 168)) < 0){
		perror("error in socket");
		exit(1);
	}
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;

	pthread_t t1, t2;
	pthread_create(&t1,NULL,sendmsg,NULL);
	pthread_create(&t2,NULL,recvmsg,NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
