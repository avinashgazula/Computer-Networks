#include <stdio.h>
#include <unistd.h>
int main()
{
	char *args[]={"./p2",NULL};
	printf("Now in p1\n");
	printf("calling exec in p1\n");
	execvp(args[0],args);
	return 0;
}