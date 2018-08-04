#include <bits/stdc++.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;
int main()
{
   int c=fork();
   if(c>0)
   {
      struct pollfd pfds[2];
      int fd1,fd2;
      fd1 = open("./cfifo1",O_RDONLY);
      fd2 = open("./cfifo2",O_RDONLY);

      pfds[0].fd = fd1;
      pfds[1].fd = fd2;
      pfds[0].events = POLLIN;
      pfds[1].events = POLLIN;

      while(true)
      {
        poll(pfds,2,2);sleep(2);
        if(pfds[0].revents && POLLIN)
        {
        	char buffer[100];
        	read(pfds[0].fd,buffer,sizeof(buffer));
         	cout<<buffer<<endl;
        }
        if(pfds[1].revents && POLLIN)
        {
        	char buffer[100];
        	read(pfds[1].fd,buffer,sizeof(buffer));
        	cout<<buffer<<endl;
        }
      }
   }
   else
   {
      int b=fork();
      if(b>0)
      {
         char* arr[2] = {"./pipe1",NULL};
         execvp(arr[0],arr);
      }
      else
      {
         char* arr[2] = {"./pipe2",NULL};
         execvp(arr[0],arr);
      }
   }
   return 0;
}
