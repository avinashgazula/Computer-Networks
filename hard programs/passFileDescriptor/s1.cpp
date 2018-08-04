#include<bits/stdc++.h>
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

#define ADDRESS "mysocket"

int sfd,usfd,nusfd;

int recv_fd(int socket)
 {
  int sent_fd, available_ancillary_element_buffer_space;
  struct msghdr socket_message;
  struct iovec io_vector[1];
  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];

  /* start clean */
  memset(&socket_message, 0, sizeof(struct msghdr));
  memset(ancillary_element_buffer, 0, CMSG_SPACE(sizeof(int)));

  /* setup a place to fill in message contents */
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = CMSG_SPACE(sizeof(int));

  if(recvmsg(socket, &socket_message, MSG_CMSG_CLOEXEC) < 0)
   return -1;

  if(message_buffer[0] != 'F')
  {
   /* this did not originate from the above function */
   return -1;
  }

  if((socket_message.msg_flags & MSG_CTRUNC) == MSG_CTRUNC)
  {
   /* we did not provide enough space for the ancillary element array */
   return -1;
  }

  /* iterate ancillary elements */
   for(control_message = CMSG_FIRSTHDR(&socket_message);
       control_message != NULL;
       control_message = CMSG_NXTHDR(&socket_message, control_message))
  {
   if( (control_message->cmsg_level == SOL_SOCKET) &&
       (control_message->cmsg_type == SCM_RIGHTS) )
   {
    sent_fd = *((int *) CMSG_DATA(control_message));
    return sent_fd;
   }
  }

  return -1;
 }

void *senderfn(void *param)
{


	string buffer;

	while(1)
	{
		cout<<"To Client :- ";
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
		cout<<"From Client :- "<<buffer<<endl;
		buffer[0] = 0;
	}
	pthread_exit(0);
}

int main(int argc, char **argv){

	//unix socket for server (connection-oriented)
	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket");

  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS);
	unlink(ADDRESS);
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");

	listen(usfd, 5);

	ucli_len=sizeof(ucli_addr);
	
	//socket for sfd
	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	if((nusfd=accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len)) == -1){
		perror("error unix accept");
		return -1;
	}
	else{
		while(1){
		
		if((sfd = recv_fd(nusfd)) != -1)
			break;
		}
	}
	//main server

	pthread_t receiver, sender;
	pthread_create(&receiver, NULL, receiverfn, NULL);
	pthread_create(&sender, NULL, senderfn, NULL);


	pthread_join(receiver, NULL);
	pthread_join(sender, NULL);
		
	return 0;
}
