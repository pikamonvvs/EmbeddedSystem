#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

typedef struct
{
	int gpio;
	int active_low;
} DEV_INFO;

static DEV_INFO dev_info = { 23, 1 };
static unsigned int irq;

irqreturn_t my_irq_handler(int irq, void *id)
{
	DEV_INFO *dev_info = (DEV_INFO *)id;
	int value=0; 
	printk("my_irq_handler(%d, %p)\n", irq, id );
	value = gpio_get_value(dev_info->gpio);
	value ^= dev_info->active_low;
	if( value == 1 )
		printk("Pressed Event\n");
	else
		printk("Realeased Event\n");

	return IRQ_HANDLED;
}

int my_init(void)           
{                               
	int ret;
	unsigned long flags=IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	printk("my_init()\n");
	irq = gpio_to_irq(23);
	printk("irq=%d\n", irq);
	ret = request_irq(irq, my_irq_handler, flags, "MY INT", &dev_info);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	free_irq(irq,&dev_info);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
