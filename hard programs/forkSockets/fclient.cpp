#include <bits/stdc++.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int sfd;

void *senderfn(void *param)
{


	string buffer;

	while(1)
	{
		cout<<"Message to Server :- ";
		getline(cin, buffer);
		send(sfd, buffer.c_str(), buffer.size(), 0);
	}
	pthread_exit(0);
}

void *receiverfn(void *param)
{
	char buffer[1000] = {};
	while(1)
	{
		recv(sfd, buffer, 1000, 0);
		if(buffer[0] != 0)
		cout<<"From Server :- "<<buffer<<endl;
		buffer[0] = 0;
	}
	pthread_exit(0);
}


int main(int argc, char **argv){
	
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;

	if((sfd=socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("Socket failed.");
		exit(1);
	}

	if(connect(sfd , (struct sockaddr *)&server , sizeof(server))==-1)
	{
		perror("\n connect : ");
		exit(1);
	}
	pthread_t receiver, sender;

	pthread_create(&receiver, NULL, receiverfn, NULL);
	pthread_create(&sender, NULL, senderfn, NULL);


	pthread_join(receiver, NULL);
	pthread_join(sender, NULL);
	return 0;
}
