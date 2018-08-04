#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
int main()
{
  int sfd,conn,result;
  struct sockaddr_in sa;
 
  char ch[100];
   socklen_t so;
  sfd=socket(AF_INET,SOCK_STREAM,0);
  if(sfd<0)
  {
    printf("Socket not created on client side\n");
    exit(0);
  }
  bzero(&sa,sizeof(sa));
  sa.sin_family=AF_INET;
  sa.sin_port=htons(5604);
  sa.sin_addr.s_addr=htonl(INADDR_ANY);
  
  conn=connect(sfd,(struct sockaddr *)&sa,sizeof(sa));
  if(conn<0)
  {
    printf("not connecting to server\n");
    exit(0);
  }
  printf("\n Enter the msg \n");
  scanf("%s",&ch);
  send(sfd,ch,sizeof(ch),0);
  recv(sfd,ch,sizeof(ch),0);
  puts(ch);
  close(sfd);
  return 0;
}
