#include <stdio.h>
#include <unistd.h>
int main()
{
	char *args[]={"./p3",NULL};
	printf("Now in p2\n");
	printf("calling exec in p2\n");
	execvp(args[0],args);
	return 0;
}