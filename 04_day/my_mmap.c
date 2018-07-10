#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/mm.h>

#include <asm/uaccess.h>

static unsigned long page;
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


int my_mmap (struct file *filp, struct vm_area_struct *vma)
{
	unsigned long pfn;
	printk("my_mmap()\n");
	printk("vm_start=%p, vm_end=%p\n", (void*)vma->vm_start, (void*)vma->vm_end );

	pfn = virt_to_phys((void*)page)>>12;
	remap_pfn_range(vma, vma->vm_start, pfn, 4096, vma->vm_page_prot);
	return 0;
}

static struct file_operations fops =
{
	.open             = my_open,
	.release          = my_close,
	.mmap             = my_mmap,
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
	page = __get_free_pages( GFP_KERNEL, 0 );
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&misc);
	free_pages( page, 0 );
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
