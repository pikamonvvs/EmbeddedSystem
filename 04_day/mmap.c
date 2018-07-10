#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int fd;
	char *p;
	fd = open("aaa", O_RDWR );
	ftruncate(fd, 100);
	p = mmap( 0 , 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	strcpy(p, "hello");
	munmap(p, 100);
	close(fd);
	return 0;
}
