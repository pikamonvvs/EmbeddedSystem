#include <stdio.h>
#include <time.h>
int main()
{
	time_t now;
	now = time(0);
	printf("%lu\n", now );
	return 0;
}
