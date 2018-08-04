#include <stdio.h>
#include <signal.h>

void fn2(int sig){
	printf("Terminated %d\n", sig);
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, fn2);
	while(1);
	return 0;
}