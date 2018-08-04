#include <bits/stdc++.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#define BUF_LEN 40
#define custom_perror(s) {perror(s);exit(1);}

int main(int argc,char*argv[])
{
	int sfd,nsfd;unsigned int client_addr_len,newsfd_len;
	struct sockaddr_in server,client,newsfd_addr;
	if((sfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	custom_perror("socket:")	
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&server.sin_zero,8);
        int opt=1;
        setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	int len=sizeof(struct sockaddr_in);
	if((bind(sfd,(sockaddr*)&server,len))==-1)
		custom_perror("bind:")
	if((listen(sfd,5))==-1)
		custom_perror("listen")
	cout<<"Listening......\n";
	client_addr_len=sizeof(client);
	if((nsfd=accept(sfd,(sockaddr*)&client,&client_addr_len))==-1)
	custom_perror("accept")
        close(nsfd);
        close(sfd);
	return 0;
}
