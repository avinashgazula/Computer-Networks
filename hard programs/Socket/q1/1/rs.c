#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
void reverse(char *ch)
{
   int len=strlen(ch),i,temp,j;
   j=(len-1);
   for(i=0,j=(len-1);i<=j;i++,j--)
   {
      temp=ch[i];
      ch[i]=ch[j];
      ch[j]=temp;
   }
}

int main()
{
  int sfd,nsfd,bnd,list,result,len,i;
  FILE *fp;
  struct sockaddr_in sa,ca;
  char buff[100];
  
   socklen_t so;
  sfd=socket(AF_INET,SOCK_STREAM,0);
  if(sfd<0)
  {
    printf("Socket not created on server side\n");
    exit(0);
  }
  bzero(&sa,sizeof(sa));
  sa.sin_family=AF_INET;
  sa.sin_port=htons(5604);
  sa.sin_addr.s_addr=htonl(INADDR_ANY);
  
  bnd=bind(sfd,(struct sockaddr *)&sa,sizeof(sa));
  if(bnd<0)
  {
    printf("socket is not binded on server side\n");
    exit(0);
  }
  list=listen(sfd,5);
  if(list<0)
  {
    printf("not listening on server side\n");
    exit(0);
  }
  nsfd=accept(sfd,(struct sockaddr *)&ca,&so);
  if(nsfd<0)
  {
    printf("Not accepted on server side\n");
    exit(0);
  }
  recv(nsfd,buff,sizeof(buff),0);
  
  reverse(buff); 

  send(nsfd,&buff,sizeof(buff),0);
  close(sfd);
  close(nsfd);
  return 0;
}
