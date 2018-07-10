#if 1
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

#define LED_ON   _IO( 'c', 1 )
#define LED_OFF  _IO( 'c', 2 )
#define LED_RATIO  _IOW( 'c', 3, int )

int main()
{
	int fd, ret, ratio;
	char buff[10];
	fd = open("/dev/mydev" , O_RDWR );
	while(1)
	{
		printf("입력(ratio) : ");
		fgets( buff, sizeof buff, stdin );  // "1\n"
		sscanf( buff, "%d", &ratio );
		ret = ioctl( fd, LED_RATIO, &ratio );
	}
	close(fd);
	return 0;
}
#endif
#if 0
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

#define LED_ON   _IO( 'd', 1 )
#define LED_OFF  _IO( 'c', 2 )

int main()
{
	int fd, ret, cmd;
	char buff[10];
	fd = open("/dev/mydev" , O_RDWR );
	while(1)
	{
		printf("입력(1:LEDON, 0:LEDOFF) : ");
		fgets( buff, sizeof buff, stdin );  // "1\n"
		sscanf( buff, "%d", &cmd );
		if( cmd == 1 ) 
		{
			ret = ioctl( fd, LED_ON );
			if( ret < 0 )
			{
				printf("ret=%d , errno=%d\n" , ret, errno);
				printf("err_str=%s\n" , strerror(errno));
				perror("ioctl()");
				exit(-1);
			}
		}
		if( cmd == 0 ) 
			ioctl( fd, LED_OFF );
	}
	close(fd);
	return 0;
}
#endif

#if 0
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd, ret, cmd;
	char buff[10];
	fd = open("/dev/mydev" , O_RDWR );
	while(1)
	{
		printf("입력(1:LEDON, 0:LEDOFF) : ");
		fgets( buff, sizeof buff, stdin );  // "1\n"
		sscanf( buff, "%d", &cmd );
		ioctl( fd, cmd );
	}
	close(fd);
	return 0;
}
#endif

