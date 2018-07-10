#if 1
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	int fd, ret;
	char buff[10];
	fd = open("/dev/mydev" , O_RDWR );
	ret = read( fd, buff, sizeof buff );
	buff[ret] = 0;
	printf("buff=%s, ret=%d\n", buff, ret );
	close(fd);
	return 0;
}
#endif

#if 0
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	int fd, ret;
	int temp;
	fd = open("/dev/mydev" , O_RDWR );
	ret = read( fd, &temp, sizeof temp );
	printf("temp=%d, ret=%d\n", temp, ret );
	close(fd);
	return 0;
}
#endif
