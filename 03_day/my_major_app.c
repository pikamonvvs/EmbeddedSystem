#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd;
	fd = open("/dev/mydev" , O_RDWR );
	close(fd);
	return 0;
}
