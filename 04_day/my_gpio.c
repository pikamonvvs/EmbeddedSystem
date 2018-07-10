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

// "0" -> "1"
ssize_t my_write (struct file *filp, const char __user *buff, size_t size, loff_t *off)
{
	char k_buff[8];
	int ret;
	printk("my_write()\n");

	ret = copy_from_user( k_buff, buff, size );

	if( strncmp( k_buff, "0", 1 ) == 0 )
		gpio_set_value( 16, 0 );
	else
		gpio_set_value( 16, 1 );

	return size;
}

static struct file_operations fops =
{
	.open    = my_open,
	.release = my_close,
	.write   = my_write,
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
