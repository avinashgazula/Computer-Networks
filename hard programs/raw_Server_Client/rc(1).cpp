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

int main(int argc, char **argv){
	
	int rsfd;
	
	if((rsfd = socket(AF_INET, SOCK_RAW, 150)) < 0){
		perror("error in socket");
		exit(1);
	}
	
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	char buffer[1024] = {};
	

	while(1){
		cout<<"Enter message :-\n";
		cin.getline(buffer,1024);
	
		if((sendto(rsfd, buffer, 1024, 0, (struct sockaddr*)&addr, len) ) < 0){
			perror("error in sento\n");
		}
	}
	return 0;
}
