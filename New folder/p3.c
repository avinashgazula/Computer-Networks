#include <stdio.h>
#include <unistd.h>
int main()
{
	char *args[]={"./p4",NULL};
	printf("Now in p3\n");
	printf("calling exec in p3\n");
	execvp(args[0],args);
	return 0;
}