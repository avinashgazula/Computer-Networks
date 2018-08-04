#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
int main()
{
  set<string> paths;
  char* fifo="/home/anjierni97/Desktop/CN/Chatserver/sfifo";
  int c=mkfifo(fifo,0666);
  if(c<0)
  {
    printf("Error in server : %d\n",c);
    return 0;
  } 
  while(true)
  {
    char msg[100];
    int cd,i=0;
    cd=open(fifo,O_RDONLY);
    read(cd,msg,sizeof(msg));
    close(cd);
    string str;
    char client=msg[strlen(msg)-1];
    while(msg[i])
    {
      str+=msg[i];i++;
    }  
    if(msg[0]=='/')
    {
      cout<<"Access Granted to client-"<<client<<endl;
      paths.insert(str);
    }
    else if(msg[0]!='\0')
    {
      cout<<"Message recieved from client-"<<client<<": "<<str<<endl;
      set<string>::iterator it=paths.begin();
      for(;it!=paths.end();it++)
      {
        string temp=*it;
        char last_char=temp[temp.length()-1];
        if(last_char!=client)
        {
          char arr[100];
          strcpy(arr,temp.c_str());
          int fd=open(arr,O_WRONLY);
          write(fd,msg,strlen(msg)+1);
          close(fd);
        }
      }
    }
  }
  return 0;
}
