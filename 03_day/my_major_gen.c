#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>

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

static int major;
static dev_t devt;
static struct class *my_class;
int my_init(void)           
{                               
	printk("my_init()\n");
	my_class = class_create( THIS_MODULE, "my_class");
	major = register_chrdev(0, "mydev", &fops);
	printk("major=%d\n", major );
	devt = MKDEV( major, 0 );
	device_create(my_class, 0, devt, 0, "mydev" );
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	device_destroy( my_class, devt);
	unregister_chrdev( major, "mydev");
	class_destroy(my_class);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
