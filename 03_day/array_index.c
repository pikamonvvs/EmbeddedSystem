#if 1
#include <stdio.h>
struct page
{
	int data[56];
};
int main()
{
	struct page a[5];
	struct page *p = &a[4];

	int index;
	 
	index = p - a;
	printf("index=%d\n", index );
	return 0;
}
#endif
#if 0
#include <stdio.h>
int main()
{
	int a[5] = {1,2,3,4,5};
	int *p = &a[4];

	int index;
	 
	index = p - a;
	printf("index=%d\n", index );
	return 0;
}
#endif
