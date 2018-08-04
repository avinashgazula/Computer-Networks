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

int main(int argc, char **argv){
	
	if((rsfd = socket(AF_INET, SOCK_RAW, 40)) < 0){
		perror("error in socket\n");
		exit(1);
	}
	
	struct sockaddr_in addr,source,dest;
	socklen_t len = sizeof(addr);
	
	char buffer[4096] = {};
	
	struct iphdr *iph;

	while(1){
		if((recvfrom(rsfd, buffer, 1024, 0, (struct sockaddr*)&addr, &len) ) < 0){
			perror("error in recvfrom\n");
		}
		if(buffer[0] != 0){
			char *msg = (char *)(buffer + sizeof(struct iphdr));
			cout<<"data = "<<msg<<endl;
			iph = (struct iphdr*)buffer;
	
			cout<<"header length = "<<(unsigned int)iph->ihl<<endl;//header length
    			cout<<"version = "<<(unsigned int)iph->version<<endl;//version
    			cout<<"type of service = "<<(unsigned int)iph->tos<<endl;//type of service
    			//cout<<"reserverd zero field = "<<(unsigned int)iphdr->ip_reserved_zero<<endl;//reserver zero field
			//cout<<"do not fragment = "<<(unsigned int)iphdr->ip_dont_fragment<<endl;//do not fragment
			//cout<<"more fragment = "<<(unsigned int)iphdr->ip_more_fragment<<endl;//more fragment
    			cout<<"ttl = "<<(unsigned int)iph->ttl<<endl;//time to live
			source.sin_addr.s_addr = iph->saddr;
			dest.sin_addr.s_addr = iph->daddr;
    			cout<<"src = "<<inet_ntoa(source.sin_addr)<<endl; //source ip address
			cout<<"dest = "<<inet_ntoa(dest.sin_addr)<<endl<<endl;//dest ip address
		}
		else{
			buffer[0] = 0;
		}
	}
	return 0;
}
