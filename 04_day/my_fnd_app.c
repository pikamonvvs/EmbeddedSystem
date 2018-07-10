#if 1
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

#define FND_NUM  _IOW( 'c', 1 , int )

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
		ret = ioctl( fd, FND_NUM, &num );
	}
	close(fd);
	return 0;
}
#endif


