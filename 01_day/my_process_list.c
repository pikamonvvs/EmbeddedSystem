#if 1
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int my_init(void)           
{                               
	struct task_struct *p;
	printk("my_init()\n");
	for_each_process(p)
		printk("pid=%5d, comm=%s\n", p->pid, p->comm );
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
#endif
#if 0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int my_init(void)           
{                               
	struct list_head *temp;
	struct task_struct *p;
	printk("my_init()\n");
	for( temp = init_task.tasks.next; temp != &init_task.tasks; temp = temp->next )
	{
		p = container_of( temp, struct task_struct, tasks );
		printk("pid=%5d, comm=%s\n", p->pid, p->comm );
	}
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
#endif
#if 0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int my_init(void)           
{                               
	struct list_head *temp;
	struct task_struct *p;
	printk("my_init()\n");
	for( temp = current->tasks.next; temp != &current->tasks; temp = temp->next )
	{
		p = container_of( temp, struct task_struct, tasks );
		printk("pid=%5d, comm=%s\n", p->pid, p->comm );
	}
	p = container_of( temp, struct task_struct, tasks );
	printk("pid=%5d, comm=%s\n", p->pid, p->comm );
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
#endif
