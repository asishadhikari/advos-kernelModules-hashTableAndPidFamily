#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
/* This function is called when the module is loaded. */
int simple init(void){
	printk(KERN INFO "Loading Module\n");
	return 0;
}

/* This function is called when the module is removed. */
void simple exit(void){
	printk(KERN INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */

module init(simple init);
module exit(simple exit);
MODULE LICENSE("GPL");
MODULE DESCRIPTION("Simple Module");
MODULE AUTHOR("Ashish Adhikari");