#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

int init_module(void)              // 정의로 이동 : g,]
{                                  // 돌아오기 : ctrl,t
	int value;
	printk("init_module()\n");
	value = gpio_get_value(24);

	printk("value=%d\n", value );
	return 0;
}

void cleanup_module(void)
{
	printk("cleanup_module()\n");
}

MODULE_LICENSE("GPL");
