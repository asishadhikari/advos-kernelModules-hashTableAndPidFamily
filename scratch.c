#include <linux/module.h>    
#include <linux/kernel.h>   
#include <linux/types.h>	 
#include <linux/slab.h>
#include <linux/init.h>     
#include <linux/list.h>		

struct birthday
{
	char name[100];
	int day;
	int month;
	int year;
	struct list_head head;
};


struct hash_table
{
	struct list_head *head;
	unsigned int size;
};

//instantiate a hash_table 
static struct hash_table birthdays

static void traverse_table(void)
{
	unsigned int i;
	struct list_head *p;
	for(int i =0; i< hash_table.size; i++){
		
	}
}