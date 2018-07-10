#if 1
#include <stdio.h>
// O(log n)
unsigned int my_ffs(unsigned int word)
{
	int num = 0;

	if ((word & 0xffff) == 0) {
		num += 16;
		word >>= 16;
	}
	if ((word & 0xff) == 0) {
		num += 8;
		word >>= 8;
	}
	if ((word & 0xf) == 0) {
		num += 4;
		word >>= 4;
	}
	if ((word & 0x3) == 0) {
		num += 2;
		word >>= 2;
	}
	if ((word & 0x1) == 0)
		num += 1;
	return num;
}

int main()
{
	unsigned int bitmap=0;
	unsigned int index=0;
	bitmap |= 1<<24;

	index = my_ffs( bitmap );
	printf("%u\n", index );
	return 0;
}
#endif

#if 0
#include <stdio.h>
// O(n)
unsigned int my_ffs(unsigned int bitmap )
{
	int i;
	for(i=0; i<32; i++ )
		if( bitmap & (1<<i) )
			break;
	return i;
}

int main()
{
	unsigned int bitmap=0;
	unsigned int index=0;
	bitmap |= 1<<24;

	index = my_ffs( bitmap );
	printf("%u\n", index );
	return 0;
}
#endif
