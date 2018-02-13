#include <linux/module.h>       
#include <linux/kernel.h>       
#include <linux/sched.h>        

void print_grandparent_processes(struct task_struct* grandparent){
	while(grandparent){
		pr_info("grandparent name: %s , grandparent state:%ld , grandparent pid:%d  \n", grandparent->comm, grandparent->state, grandparent->pid);
		grandparent = grandparent->parent;
	}
}

void print_task_info(void)
{
        struct task_struct* tasks;
        for_each_process(tasks) {
                pr_info("name: %s ,  state:%ld , pid:%d  \n", tasks->comm, tasks->state, tasks->pid);
                if(tasks->parent){
                	struct task_struct* parent;
                	parent = tasks->parent; 
                	pr_info(" parent name:%s, parent state:%ld,  parent pid:%d \n", parent->comm, parent->state,parent->pid);
                pr_info("######### Task has following properties ############");
                if(tasks->parent->parent){
                	print_grandparent_processes(tasks->parent->parent);
                }

                }
               
        }
}


static int __init main_init(void)
{
        printk(KERN_INFO "[ INIT ==\n");

        print_task_info();

        return 0;
}

static void __exit main_exit(void)
{
        printk(KERN_INFO "Exiting Module....\n");
}

module_init(main_init);
module_exit(main_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Project 2");
MODULE_AUTHOR("Ashish Adhikari");