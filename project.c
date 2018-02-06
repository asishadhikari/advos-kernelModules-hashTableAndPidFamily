#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

//number of buckets for hash table implementation
#define HASH_TABLE_SIZE 20
//hash table implemented as doubly linked list with buckets of unique value 
static LIST_HEAD(hashTable);
//node
struct birthday
{
	char name[100];
	int day;
	int month;
	int year;
	//list_head has next and prev, embed ll within nodes
	struct list_head head;
};


//container of node
struct bucket
{
	unsigned int key;
	//unique list_head for each bucket
	LIST_HEAD(bucket_head);
	//part of the main list of hashing buckets
	struct list_head hash_head;

};


// hash function for using name as key
unsigned int hashName(unsigned char *str)
{
  unsigned long hash = 0;
  int c;
  while (c = *str++)
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % HASH_TABLE_SIZE ;  //limit hash table size
}

static void initialise_bucket(void)
{
	struct bucket *new_bucket;
	
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		new_bucket = kmalloc(sizeof(*new_bucket,GFP_KERNEL));
		list_add(new_bucket,hashTable);

	}
}

//add birthday to respective bucket
static void add_birthday(struct birthday){
	unsigned index = hashName(birthday.name);
	
}



/* This function is called when the module is loaded. */
int simple init(void)
{
	
	//initialise 5 struct birthday elements
	struct birthday person1={
	  .name = "Charles",
		.day = 12,
	  .month = 1,
	  .year = 1921,
	};
	struct birthday person2={
	  .name = "Xavier",
		.day = 1,
	  .month = 12,
	  .year = 1321,
	};
	struct birthday person3={
	  .name = "Cotay",
		.day = 22,
	  .month = 11,
	  .year = 1421,
	};
	struct birthday person4={
	  .name = "Ramy",
		.day = 22,
	  .month = 10,
	  .year = 1969,
	};
	struct birthday person5={
	  .name = "Simpson",
		.day = 13,
	  .month = 7,
	  .year = 1979,
	};



	/*
	//initialise head member in struct birthday 
	INIT_LIST_HEAD(&person1->head);
	INIT_LIST_HEAD(&person2->head);
	INIT_LIST_HEAD(&person3->head);
	INIT_LIST_HEAD(&person4->head);
	INIT_LIST_HEAD(&person5->head);
	//add the birthday instances to the tail of the linked list
	list_add_tail(&person1->head, &hashTable);
	list_add_tail(&person2->head, &hashTable);
	list_add_tail(&person3->head, &hashTable);
	list_add_tail(&person4->head, &hashTable);
	list_add_tail(&person5->head, &hashTable);
	*/



	printk(KERN INFO "Loading Module\n");
	return 0;
}

/* This function is called when the module is removed. */
void simple exit(void)
{
	printk(KERN INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */

module init(simple init);
module exit(simple exit);
MODULE LICENSE("GPL");
MODULE DESCRIPTION("Simple Module");
MODULE AUTHOR("Ashish Adhikari");