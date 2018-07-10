#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int length, fd, rc;
	char *nodename = "/dev/mydev";
	char message[128] = "hello world how are you";

	length = strlen(message);

	if (argc > 1)
		nodename = argv[1];

	fd = open(nodename, O_RDWR);
	printf(" opened file descriptor first time  = %d\n", fd);

	lseek( fd, 4096, SEEK_SET);
	rc = write(fd, message, length);
	printf("return code from write = %d on %d, message=%s\n", rc, fd,
			message);

	memset(message, 0, length);
	lseek( fd, 4107, SEEK_SET);

	rc = read(fd, message, length);
	printf("return code from read  = %d on %d, message=%s\n", rc, fd,
			message);

	close(fd);
	exit(0);
}

