#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/list.h>

#include <asm/uaccess.h>

#define MYDEV_NAME  "mydev"

typedef struct
{
	struct list_head list;
	char *data;
} MEM_INFO;

static size_t ramdisk_size = 0;
static size_t file_size = 0;
static LIST_HEAD(my_list);

static ssize_t mycdrv_write(struct file *file, const char __user * buf, size_t lbuf, loff_t * ppos) 
{
	int i;
	int nbytes, maxbytes, bytes_to_do;
	struct list_head *temp;
	char *ramdisk;

    printk("mycdrv_write()\n");
	for( i=0; i<ramdisk_size/4096; i++)
		;

	for( ; i< (*ppos/4096+1); i++)
	{
		MEM_INFO *temp = kmalloc(sizeof(MEM_INFO), GFP_KERNEL);
		temp->data = kmalloc(4096, GFP_KERNEL);
		list_add_tail( &temp->list, &my_list ); 
		ramdisk_size += 4096;
	    pr_info("파일크기=%u\n", ramdisk_size);
	}

	for( temp=my_list.next,i=0; i < *ppos/4096; i++)
	{
		temp = temp->next;
	}
	ramdisk = list_entry(temp,MEM_INFO,list)->data;

	maxbytes = ramdisk_size - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0)
		pr_warning("Reached end of the device on a write");
	nbytes =
		bytes_to_do - copy_from_user(ramdisk + *ppos%4096, buf, bytes_to_do);
	*ppos += nbytes;
	file_size = *ppos;
	pr_info("현재 파일 크기=%u\n", file_size);
	pr_info("\n Leaving the   WRITE function, nbytes=%d, pos=%d\n",
			nbytes, (int)*ppos);
	return nbytes;
}

static ssize_t
mycdrv_read(struct file *file, char __user * buf, size_t lbuf, loff_t * ppos)
{
	int i;
	int nbytes, maxbytes, bytes_to_do;
	struct list_head *temp;
	char *ramdisk;

    printk("mycdrv_read()\n");
	for( temp=my_list.next,i=0; i < *ppos/4096; i++)
	{
		temp = temp->next;
	}
	ramdisk = list_entry(temp,MEM_INFO,list)->data;

	maxbytes = file_size - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0)
		pr_info("Reached end of the device on a read");
	nbytes = bytes_to_do - copy_to_user(buf, ramdisk + *ppos%4096, bytes_to_do);
	*ppos += nbytes;
	pr_info("현재위치=%lld\n", *ppos);
	pr_info("\n Leaving the   READ function, nbytes=%d, pos=%d\n",
			nbytes, (int)*ppos);
	return nbytes;
}

static loff_t mycdrv_lseek(struct file *file, loff_t offset, int orig)
{
	loff_t testpos;
    printk("mycdrv_lseek()\n");
	switch (orig) {
		case SEEK_SET:	testpos = offset;	                  break;
		case SEEK_CUR:	testpos = file->f_pos + offset; 	break;
		case SEEK_END:	testpos = ramdisk_size + offset;	break;
		default:
						return -EINVAL;
	}
	testpos = testpos >= 0 ? testpos : 0;
	file->f_pos = testpos;
	pr_info("현재위치=%lld\n", testpos);
	return testpos;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.read  =  mycdrv_read,
	.write =  mycdrv_write,
	.llseek =  mycdrv_lseek, 
};

static struct miscdevice my_misc_device = 
{
	.minor = MISC_DYNAMIC_MINOR,
	.name  = MYDEV_NAME, 
	.fops  = &fops,
};

static int  my_generic_init(void)
{
	misc_register(&my_misc_device);
	printk("\nSucceeded in registering character device %s\n", MYDEV_NAME);
	return 0;
}

static void  my_generic_exit(void)
{
	struct list_head *temp;
	misc_deregister(&my_misc_device);
	printk("\ndevice unregistered\n");

	while( !list_empty(&my_list) )
	{
		temp = my_list.next;
		list_del(temp);
		kfree( list_entry(temp, MEM_INFO, list)->data );
		kfree( list_entry(temp, MEM_INFO, list));
	}
}

module_init(my_generic_init);
module_exit(my_generic_exit);
MODULE_LICENSE("GPL");

