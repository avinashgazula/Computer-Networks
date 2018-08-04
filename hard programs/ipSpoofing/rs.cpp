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

int rsfd,opt = 1;
struct sockaddr_in addr;
socklen_t len = sizeof(addr);

unsigned short csum(unsigned short *ptr,int nbytes) 
{
    register long sum;
    unsigned short oddbyte;
    register short answer;
 
    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }
 
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
     
    return(answer);
}

int main(int argc, char **argv){
	
	if((rsfd = socket(AF_INET, SOCK_RAW, 40)) < 0){
		perror("error in socket\n");
		exit(1);
	}
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if((setsockopt(rsfd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt))) < 0){
		perror("error in including ip header\n");
	}
	char buffer[4096] = {},*data;
	
	struct iphdr *iph = (struct iphdr*)buffer;
	
	iph->ihl = 5;//header length
    	iph->version = 4;//version
    	iph->tos = 0;//type of service
    	
    	iph->id = htonl (54321); //Id of this packet
    	iph->frag_off = 0;//fragment offset
    	iph->ttl = 255;//time to live
    	iph->protocol = 40;//protocol
    	iph->check = 0;      //Set to 0 before calculating checksum
    	iph->saddr = inet_addr ("10.0.0.2");    //Spoof the source ip address
    	iph->daddr = addr.sin_addr.s_addr;//destination address
	
	while(1){
		cout<<"enter the data :-\n";
		data = (char *)(buffer + sizeof(struct iphdr));
		cin>>data;
		cout<<data<<endl;
		iph->tot_len = sizeof (struct iphdr) + strlen(data);
		//Ip checksum
    		iph->check = csum ((unsigned short *) buffer, iph->tot_len);
		if((sendto(rsfd, buffer, 4096, 0, (struct sockaddr*)&addr, sizeof(addr)) ) < 0)
			perror("error in sendto()\n");
	}
	return 0;
}
