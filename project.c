#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct birthday{
	int day;
	int month;
	int year;
	//list_head has next and prev
	struct list_head list;
};

//macro to init birthday_list of type LIST_HEAD
static LIST_HEAD(birthday_list);








/* This function is called when the module is loaded. */
int simple init(void){
	struct birthday *person;
	person = kmalloc(sizeof(*person),GFP_KERNEL);
	person->day = 23;
	person->month = 6;
	person->year = 1994;
	//initialise the list head with first node's list
	INIT_LIST_HEAD(&person->list);

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