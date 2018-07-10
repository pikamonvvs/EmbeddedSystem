#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#define CONFIG_ARM_L1_CACHE_SHIFT   6
#define L1_CACHE_SHIFT		CONFIG_ARM_L1_CACHE_SHIFT
#define L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)
#define ARCH_MIN_TASKALIGN	L1_CACHE_BYTES

struct my_struct
{
	int gpio;
	int active_low;
	char name[192];
} __attribute__((packed));

static struct kmem_cache *my_struct_cachep;

int my_init(void)           
{                               
	struct my_struct *p;
	printk("my_init()\n");
	my_struct_cachep = kmem_cache_create("my_struct",
			                             sizeof(struct my_struct), 
										 1,
						                 SLAB_PANIC|SLAB_NOTRACK|SLAB_ACCOUNT, 
										 NULL);
	p = kmem_cache_alloc(  my_struct_cachep, GFP_KERNEL );
	p->gpio = 24;
	p->active_low = 1;
	strcpy(p->name, "my_device");
	printk("gpio=%d, active_low=%d, name=%s\n", p->gpio, p->active_low, p->name );
	kmem_cache_free( my_struct_cachep , p );

	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	kmem_cache_destroy( my_struct_cachep );
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
