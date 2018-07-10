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
	fd = open("/dev/mydev", O_RDWR );
	p = mmap( 0 , 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	printf("p = %p\n", p );
	strcpy( p , "hello" );
	printf("%s\n", p );
	munmap(p, 4096);
	close(fd);
	return 0;
}
