#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>

#include <asm/uaccess.h>

int my_open (struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	return 0;
}

int my_close (struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

#if 1
// ashmem_ioctl
#define LED_ON     _IO( 'c', 1 )
#define LED_OFF    _IO( 'c', 2 )
#define LED_RATIO  _IOW( 'c', 3 , int )

long my_ioctl (struct file *filp, unsigned int cmd, unsigned long opt)
{
	int ret, ratio , size;
	printk("my_ioctl()\n");
	if( _IOC_TYPE(cmd)  != 'c' ) 
		return -EINVAL;
	if( _IOC_NR(cmd)<1 ||  3<_IOC_NR(cmd)) 
		return -EINVAL;
	size = _IOC_SIZE(cmd);
	switch( cmd )
	{
		case LED_ON  : gpio_set_value( 16, 0 ); break;
		case LED_OFF : gpio_set_value( 16, 1 ); break;
		case LED_RATIO : 
					   ret= copy_from_user(&ratio, (void*)opt, size);
					   printk("ratio=%d\n", ratio );
					   break;
	}
	return 0;
}
#endif
#if 0

#define LED_ON   _IO( 'c', 1 )
#define LED_OFF  _IO( 'c', 2 )

long my_ioctl (struct file *filp, unsigned int cmd, unsigned long opt)
{
	printk("my_ioctl()\n");
	if( _IOC_TYPE(cmd)  != 'c' ) 
		return -EINVAL;
	if( _IOC_NR(cmd)<1 ||  2<_IOC_NR(cmd)) 
		return -EINVAL;
	switch( cmd )
	{
		case LED_ON  : gpio_set_value( 16, 0 ); break;
		case LED_OFF : gpio_set_value( 16, 1 ); break;
	}
	return 0;
}
#endif

#if 0
// binder_ioctl
long my_ioctl (struct file *filp, unsigned int cmd, unsigned long opt)
{
	printk("my_ioctl()\n");
	if( cmd == 0 )
		gpio_set_value( 16, 0 );
	else if ( cmd == 1 )
		gpio_set_value( 16, 1 );
	return 0;
}
#endif

static struct file_operations fops =
{
	.open             = my_open,
	.release          = my_close,
	.unlocked_ioctl   = my_ioctl,
	.compat_ioctl     = my_ioctl,
};

static struct miscdevice  misc =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mydev",
	.fops = &fops, 
};

int my_init(void)           
{                               
	printk("my_init()\n");
	misc_register(&misc);
	gpio_direction_output( 16, 0 );
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&misc);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
