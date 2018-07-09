#if 1
#include <stdio.h>

#define __must_check		__attribute__((warn_unused_result))

int __must_check foo(void)
{
	printf("foo()\n");
	return 1;
}

int main()
{
	int ret = foo();
	return 0;
}
#endif

#if 0
#include <stdio.h>

void bar(void)
{
	printf("bar()\n");
}

void foo(void) __attribute__((alias("bar")));

//----------------------------------------------------------------

int main()
{
	foo();
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define __used			__attribute__((__used__))
#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)
#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)
# define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#define __MODULE_INFO(tag, name, info)					              \
static const char __UNIQUE_ID(name)[]					                          \
  __used __attribute__((section(".modinfo"), unused, aligned(1)))	  \
  = __stringify(tag) "=" info

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)
#define MODULE_LICENSE(_license) MODULE_INFO(license, _license)
//----------------------------------------------------------------
MODULE_LICENSE("GPL"); MODULE_LICENSE("BSD");

int main()
{
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define __used			__attribute__((__used__))
#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)
#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)
# define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __LINE__)

#define __MODULE_INFO(tag, name, info)					              \
static const char __UNIQUE_ID(name)[]					                          \
  __used __attribute__((section(".modinfo"), unused, aligned(1)))	  \
  = __stringify(tag) "=" info

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)
#define MODULE_LICENSE(_license) MODULE_INFO(license, _license)
//----------------------------------------------------------------
MODULE_LICENSE("GPL");
MODULE_LICENSE("BSD");

int main()
{
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define __used			__attribute__((__used__))
#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#define __MODULE_INFO(tag, name, info)					              \
static const char name[]					                          \
  __used __attribute__((section(".modinfo"), unused, aligned(1)))	  \
  = __stringify(tag) "=" info

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)
#define MODULE_LICENSE(_license) MODULE_INFO(license, _license)
//----------------------------------------------------------------
MODULE_LICENSE("GPL");
MODULE_LICENSE("BSD");

int main()
{
	return 0;
}
#endif

#if 0
#include <stdio.h>

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

static const char license[] = __stringify(license) "=" "GPL";

int main()
{
	printf("%s\n", license );
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

char *p = "line" "="  __stringify(__LINE__);
// char *p = "=" "GPL";

int main()
{
	printf("%s\n", p );
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define foo bar
#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

char *p = __stringify(foo) "=" "GPL";
// char *p = "=" "GPL";

int main()
{
	printf("%s\n", p );
	return 0;
}
#endif

#if 0
#include <stdio.h>

#define __stringify_1(x...)	#x
//#define __stringify(x...)	__stringify_1(x)

char *p = __stringify_1(license) "=" "GPL";
// char *p = "=" "GPL";

int main()
{
	printf("%s\n", p );
	return 0;
}
#endif

#if 0

static int  __attribute__((section(".modinfo"))) global=10; 

int main()
{
	return 0;
}
#endif

#if 0
#include <stdio.h>

int main()
{
	char __attribute__((aligned(4))) ch;
	printf("%p\n", &ch );
	return 0;
}
#endif
#if 0

//static int global=10; 
static __attribute__((unused)) int global=10; 

int main()
{
	return 0;
}
#endif

#if 0
//  __used 

#define __used			__attribute__((__used__))

static __used int global=10; 

int main()
{
	return 0;
}
#endif
