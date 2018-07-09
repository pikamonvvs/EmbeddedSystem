#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

static int my_int=100;
module_param( my_int, int, 0660 );

static int my_array[5] = {1,2,3,4,5};
static int count=0;
module_param_array( my_array, int, &count, 0660 );

static char *my_string="default";
module_param( my_string, charp, 0660 );

static char my_string_1[128]="default";
module_param_string( my_str, my_string_1, sizeof(my_string_1) , 0660 );

int my_init(void)           
{                               
	int i;
	printk("my_init()\n");
	printk("my_int=%d\n", my_int);
	printk("my_string=%s\n", my_string);
	printk("my_string_1=%s\n", my_string_1);
	for( i=0; i<count; i++ )
		printk("my_array[%d]=%d\n", i, my_array[i]);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
