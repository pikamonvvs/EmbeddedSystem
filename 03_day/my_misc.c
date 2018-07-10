#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

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

static struct file_operations fops =
{
	.open    = my_open,
	.release = my_close,
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
