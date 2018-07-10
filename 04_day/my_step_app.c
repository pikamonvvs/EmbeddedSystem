#if 1
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

#define STEP_FORWARD  _IO( 'c', 1 )

int main()
{
	int fd, ret, num;
	char buff[10];
	fd = open("/dev/mydev" , O_RDWR );
	while(1)
	{
		printf("입력(num) : ");
		fgets( buff, sizeof buff, stdin );  // "1\n"
		sscanf( buff, "%d", &num );
		if(num == 1 )
			ret = ioctl( fd, STEP_FORWARD );
	}
	close(fd);
	return 0;
}
#endif


