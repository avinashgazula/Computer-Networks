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

int main()
{
	int rsfd;
	rsfd=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);

	if(rsfd < 0)
	{
		printf("error in creating socket\n");
		return -1;
	}

	unsigned char *buffer = (unsigned char *) malloc(65536); //to receive data
	memset(buffer,0,65536);
	struct sockaddr saddr;
	int saddr_len = sizeof (saddr);
	 

	int buflen=recvfrom(rsfd,buffer,65536,0,&saddr,(socklen_t *)&saddr_len);
	if(buflen<0)
	{
		printf("error in reading recvfrom function\n");
		return -1;
	}

	printf("%s is received %d is length\n",buffer,buflen);


	struct ethhdr *eth = (struct ethhdr *)(buffer);
	printf("\nEthernet Header\n");
	printf("\t|-Source Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
				eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
	printf("\t|-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
		eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	printf("\t|-Protocol : %d\n",eth->h_proto);

	printf("\n\nIP Header\n");
	unsigned short iphdrlen;
	struct sockaddr_in source,dest;
	struct iphdr *ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->saddr;
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->daddr;
	 
	printf("\t|-Version : %d\n",(unsigned int)ip->version);
	 
	printf("\t|-Internet Header Length : %d DWORDS or %d Bytes\n",
		(unsigned int)ip->ihl,((unsigned int)(ip->ihl))*4);
	 
	printf( "\t|-Type Of Service : %d\n",(unsigned int)ip->tos);
	 
	printf( "\t|-Total Length : %d Bytes\n",ntohs(ip->tot_len));
	 
	printf( "\t|-Identification : %d\n",ntohs(ip->id));
	 
	printf( "\t|-Time To Live : %d\n",(unsigned int)ip->ttl);
	 
	printf("\t|-Protocol : %d\n",(unsigned int)ip->protocol);
	 
	printf("\t|-Header Checksum : %d\n",ntohs(ip->check));
	 
	printf("\t|-Source IP : %s\n", inet_ntoa(source.sin_addr));
	 
	printf("\t|-Destination IP : %s\n",inet_ntoa(dest.sin_addr));
	return 0;
}