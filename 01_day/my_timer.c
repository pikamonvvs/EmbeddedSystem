#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

static struct timer_list my_timer;

void my_timer_handler(unsigned long data )
{
	printk("my_timer_handler(%lu)\n", data );
}

int my_init(void)           
{                               
	printk("my_init()\n");
	init_timer(&my_timer);
	my_timer.expires  = jiffies + 3*HZ;
	my_timer.function = my_timer_handler;
	my_timer.data	  = 0;
	add_timer(&my_timer);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	del_timer(&my_timer);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
