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

#define STEP_FORWARD  _IO( 'c', 1 )

int pin[4] = { 16,19,20,21 };
int seq[][4] = {
	{ 1,0,0,1 },
	{ 1,0,0,0 },
	{ 1,1,0,1 },
	{ 0,1,0,0 },
	{ 0,1,1,0 },
	{ 0,0,1,0 },
	{ 0,0,1,1 },
	{ 0,0,0,1 }
};

void forwards( int steps )
{
	int i,j,k;
	for(i=0; i<steps; i++ )
	{
		for(j=0; j<8; j++ )
		{
			for(k=0; k<4; k++ )
				gpio_set_value( pin[k], seq[j][k] );
			udelay(800);
		}
	}
}


long my_ioctl (struct file *filp, unsigned int cmd, unsigned long opt)
{
	int  size;
	printk("my_ioctl()\n");
	if( _IOC_TYPE(cmd)  != 'c' ) 
		return -EINVAL;
	if( _IOC_NR(cmd)<1 ||  1<_IOC_NR(cmd)) 
		return -EINVAL;
	size = _IOC_SIZE(cmd);
	switch( cmd )
	{
		case STEP_FORWARD : 
			{
				int i;
				for(i=0;i<100; i++)
				{
					forwards(1024);
					ndelay(100);
				}
			}
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

	for(i=0; i<4; i++ )
		gpio_direction_output( pin[i], 0 );

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
