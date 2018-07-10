#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/delay.h>

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
#define SEG_DIG  18

int led[] = { 7,8,9,10,11,14,15,0 };
int num[10][8] = {
	{ 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 0, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 1, 1, 0, 1 },
	{ 1, 0, 0, 1, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 1 }
};

#define FND_NUM  _IOW( 'c', 1 , int )

void fnd_write( int row )
{
	int j;
	int pin=0;
	int n;
	n = row;
	gpio_set_value( SEG_DIG, 1 );

	for( j=0, pin=0; j<8; j++, pin++ )
		gpio_set_value(led[pin], !num[n][j] );
}

long my_ioctl (struct file *filp, unsigned int cmd, unsigned long opt)
{
	int ret, num , size;
	printk("my_ioctl()\n");
	if( _IOC_TYPE(cmd)  != 'c' ) 
		return -EINVAL;
	if( _IOC_NR(cmd)<1 ||  1<_IOC_NR(cmd)) 
		return -EINVAL;
	size = _IOC_SIZE(cmd);
	switch( cmd )
	{
		case FND_NUM : 
			ret= copy_from_user(&num, (void*)opt, size);
			printk("num=%d\n", num );
			fnd_write(num);
			break;
	}
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
	int i;
	printk("my_init()\n");
	misc_register(&misc);
	gpio_direction_output( SEG_DIG, 0 );

	for(i=0; i<7; i++ )
		gpio_direction_output( led[i], 0 );

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
