#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
char n;
void* read(void* f)
{
  while(true)
  {
    char* cfifo=(char*)f;
    char str[100];
    int cd=open(cfifo,O_RDONLY);
    read(cd,str,sizeof(str));
    cout<<"\t\t\t\t\t "<<str<<endl;
    close(cd);  
  }
  
}
void* write(void* f)
{
  while(true)
  {
    char* sfifo=(char*)f;
    char str[100];
    //printf("Enter message :");
    int length;
    cin.getline(str,100);
    length=strlen(str);
    if(length>0)
    {
      str[length]=n;
      str[length+1]='\0';
    }
    int cd=open(sfifo,O_WRONLY);
    write(cd,str,strlen(str)+1);
    close(cd);  
  }
  
}
int main()
{
  cout<<"Enter Client Number : ";
  cin>>n;
  char cfifo[]="./cfifo";
  char* sfifo="./sfifo";
  int x=strlen(cfifo);
  cfifo[x]=n;
  cfifo[x+1]='\0';
  int c=mkfifo(cfifo,0666);
  if(c<0)
  {
    printf("%d error in client\n",c);
    return 0;
  }
  int fd=open(sfifo,O_WRONLY);
  char path[100];
  strcpy(path,cfifo);
  write(fd,path,strlen(path)+1);
  close(fd);
  pthread_t t1,t2;
  pthread_create(&t1,NULL,read,cfifo);
  pthread_create(&t2,NULL,write,sfifo);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  return 0;
}
