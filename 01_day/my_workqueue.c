#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/workqueue.h>

typedef struct
{
	int gpio;
	int active_low;
	struct work_struct my_work;
} DEV_INFO;

static DEV_INFO dev_info = { 23, 1 };
static unsigned int irq;

irqreturn_t my_irq_handler(int irq, void *id)
{
	DEV_INFO *dev_info = (DEV_INFO *)id;
	printk("my_irq_handler(%d, %p)\n", irq, id );

	schedule_work(&dev_info->my_work);

	return IRQ_HANDLED;
}

void my_work_handler(struct work_struct *work)
{
	DEV_INFO *dev_info = container_of( work, DEV_INFO, my_work);
	int value=0; 
	printk("my_work_handler(%p)\n", work );
	value = gpio_get_value(dev_info->gpio);
	value ^= dev_info->active_low;
	if( value == 1 )
		printk("Pressed Event\n");
	else
		printk("Realeased Event\n");
}

int my_init(void)           
{                               
	int ret;
	unsigned long flags=IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	printk("my_init()\n");
	irq = gpio_to_irq(23);
	printk("irq=%d\n", irq);
	ret = request_irq(irq, my_irq_handler, flags, "MY INT", &dev_info);
	INIT_WORK(&dev_info.my_work, my_work_handler);
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
