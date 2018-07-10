#include <stdio.h>
#include <pthread.h>

int global=6;

void *foo( void *data)
{
	printf("child : global=%d, local=%d\n", ++global, ++*(int*)data);
	return 0;
}

int main()
{
	pthread_t thread;
	int local=10;
	pthread_create( &thread, 0, foo, &local );
	//foo(&local);
	pthread_join( thread, 0 );

	printf("parent: global=%d, local=%d\n", ++global, local);
	return 0;
}
