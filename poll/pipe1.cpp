#include <bits/stdc++.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;
int main()
{
    char* fifo="./cfifo1";
    mkfifo(fifo,0666);
    while(true)
    {
    	sleep(2);
    	int fd=open(fifo,O_WRONLY);
        write(fd,"Reading pipe1",14);
    	close(fd);
    }
	return 0;
}