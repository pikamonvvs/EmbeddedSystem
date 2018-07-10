#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
	if( 0==fork() )
	{
		printf("child\n");
		exit(0);
	}
	wait(0);

	printf("parent\n");
	return 0;
}
