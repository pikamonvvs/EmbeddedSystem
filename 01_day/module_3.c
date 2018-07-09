#include <linux/module.h>
#include <linux/kernel.h>

int my_init(void)           
{                               
	printk("my_init()\n");
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
