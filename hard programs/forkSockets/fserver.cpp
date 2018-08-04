#include <bits/stdc++.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int sfd,nsfd;

void *senderfn(void *param)
{


	string buffer;

	while(1)
	{
		cout<<"Message to Client :- ";
		getline(cin, buffer);
		send(nsfd, buffer.c_str(), buffer.size(), 0);
	}
	pthread_exit(0);
}

void *receiverfn(void *param)
{
	char buffer[1000] = {};
	while(1)
	{
		recv(nsfd, buffer, 1000, 0);
		if(buffer[0] != 0)
		cout<<"From Client :- "<<buffer<<endl;
		buffer[0] = 0;
	}
	pthread_exit(0);
}


int main( int argc, char *argv[]){

	char buffer[1000], buffer2[1050];
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	cli_len = sizeof(cli_addr);
	int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		
		perror("\n socket ");
		exit(1);
	}

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	{
		perror("\n bind : ");
		exit(1);
	}

	if(listen(sfd,10) < 0){
		
		perror("\n listen : ");
		exit(1);
	}

	while(1){
		
		if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
			{
				perror("\n accept ");
				return -1;
			}
		else{
			pid_t pid = fork();
			if(pid > 0){
				close(nsfd);//closing nsfd in parent process
				continue;
			}
			else{
				close(sfd);//closing sfd in child process
				pthread_t receiver, sender;

				pthread_create(&receiver, NULL, receiverfn, NULL);
				pthread_create(&sender, NULL, senderfn, NULL);


				pthread_join(receiver, NULL);
				pthread_join(sender, NULL);
			}
		}
	}
	return 0;
}
