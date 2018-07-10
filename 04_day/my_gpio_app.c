#if 1
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd, ret;
	char buff[10];
	fd = open("/dev/mydev" , O_RDWR );
	while(1)
	{
		printf("입력(1:LEDON, 0:LEDOFF) : ");
		fgets( buff, sizeof buff, stdin );
		ret = write( fd, buff, strlen(buff) );
	}
	close(fd);
	return 0;
}
#endif

