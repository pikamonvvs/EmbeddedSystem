#if 1
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	struct file *filp;
	int ret;
	char buff[128];
	filp = open("aaa", O_RDWR );
	ret = read( filp, buff, 2 );
	write(1, buff, ret );
	ret = read( filp, buff, 2 );
	write(1, buff, ret );
	close(filp);
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd;
	int ret;
	char buff[128];
	fd = open("aaa", O_RDWR );
	ret = read( fd, buff, 2 );
	write(1, buff, ret );
	ret = read( fd, buff, 2 );
	write(1, buff, ret );
	close(fd);
	return 0;
}
#endif
