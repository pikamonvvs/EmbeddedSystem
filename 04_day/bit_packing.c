#if 1
#include <stdio.h>
int main()
{
	int info=0;
	info |= 4;
	info |= 80<<3;
	info |= 1<<11;
	printf("year=%d, score=%d, gen=%d\n", 
			info&0x7, (info>>3)&0xff, (info>>11)&1 );
	return 0;
}
#endif
#if 0
#include <stdio.h>
int main()
{
	int year=4;
	int score=80;
	int gen=1;
	printf("year=%d, score=%d, gen=%d\n", year, score, gen );
	return 0;
}
#endif
