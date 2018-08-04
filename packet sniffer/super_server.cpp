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
vector<int> fds;
set<int> port_no;
void add_socket(int num)
{
        int sfd,nsfd;unsigned int client_addr_len,newsfd_len;
	struct sockaddr_in server,client,newsfd_addr;
	if((sfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	custom_perror("socket:")	
	server.sin_family=AF_INET;
	server.sin_port=htons(num);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&server.sin_zero,8);
	int len=sizeof(struct sockaddr_in);
        int opt=1;
        setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	if((bind(sfd,(sockaddr*)&server,len))==-1)
		custom_perror("bind:")
	if((listen(sfd,5))==-1)
		custom_perror("listen")
        fds.push_back(sfd); 
}

int main(int argc,char*argv[])
{
       int sfd,nsfd;unsigned int client_addr_len,newsfd_len;
	struct sockaddr_in server,client,newsfd_addr;
	if((sfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
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
	
	while(1)
	{
		cout<<"Listening\n";
                fd_set read_fds;
                int max_fd=-1;
                FD_SET(sfd,&read_fds);
                max_fd=max(max_fd,sfd);           
                for(int i=0;i<fds.size();i++)
                {
                   FD_SET(fds[i],&read_fds);max_fd=max(max_fd,fds[i]);  
                }
                struct timeval t;
                t.tv_sec=5;
                t.tv_usec=0;
                int ret=select(max_fd+1,&read_fds,NULL,NULL,&t); 
                if(ret>0)
                {
		    client_addr_len=sizeof(client);
                        for(int j=0;j<fds.size();j++){
                        if(FD_ISSET(fds[j],&read_fds))
                        { 
                           char buff[]="service done ";
                           int nsfd=accept(fds[j],NULL,NULL);          
                           cout<<"accepted "<<endl;
                        }}
                        if(FD_ISSET(sfd,&read_fds)){
                          char buf[BUF_LEN];
		 	  int n=recvfrom(sfd,buf,BUF_LEN,0,(sockaddr*)&client,&client_addr_len);
			  int port=atoi(buf);
                          if(port_no.find(port)!=port_no.end())
                          continue;
                          else
                          add_socket(port);
                        }
             }
	}
	return 0;
}
