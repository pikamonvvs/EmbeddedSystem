
#if 1
struct aaa
{
	int a,b;
};

struct aaa *foo(void) 
{
	static struct aaa aaa;
	return &aaa;
}

int main()
{
	foo()->a = 10;
	return 0;
}
#endif
#if 0
struct aaa
{
	int a,b;
};

struct aaa foo(void) 
{
	static struct aaa aaa;
	return aaa;
}

int main()
{
	foo().a = 10;
	return 0;
}
#endif
#if 0
int (*foo(void))[10] 
{
	static int a[10][10];
	return a;
}

int main()
{
	foo()[1][1] = 10;
	return 0;
}
#endif
#if 0
int *foo(void)
{
	static int a[10];
	return a;
}

int main()
{
	foo()[1] = 10;
	return 0;
}
#endif
