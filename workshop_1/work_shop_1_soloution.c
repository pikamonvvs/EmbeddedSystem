#if 1
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static char *option=0;
static char *name=0;
module_param( option, charp, 0660 );
module_param( name, charp, 0660 );

void title_print(void)
{
	printk("%6s %6s %6s %6s %s\n",
			"UID","PID","PPID","TID","NAME" );
}
void task_print(struct task_struct *p)
{
	printk("%6d %6d %6d %6d %s\n", 
			p->self_exec_id,p->tgid,p->parent->pid,
			p->pid, p->comm);
}

void my_process_list(void)
{
	struct task_struct *p;
	for_each_process(p)
	{
		if( name != 0 )
		{
			if( strncmp(name, p->comm, strlen(name)) != 0 )
				continue;
		}
		task_print(p);
	} 
}
void my_thread_list(void)
{
	struct task_struct *g, *t;
	do_each_thread(g, t)
	{
		if( name != 0 )
		{
			if( strncmp(name, g->comm, strlen(name)) != 0 )
				continue;
		}
		task_print(t);
	} while_each_thread(g, t);
}

int my_init(void)
{
	if( option != 0 )
		printk("option=[%s]\n", option);
	if( name != 0 )
		printk("name=[%s]\n", name);
	title_print();
	if( (option!=0) && (strncmp( option, "t", 1 )==0) )
		my_thread_list();
	else
		my_process_list();

	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}

module_init(my_init);
module_exit(my_exit);
#endif
