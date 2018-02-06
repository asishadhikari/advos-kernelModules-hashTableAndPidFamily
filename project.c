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
	struct list_head bucket_head;
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

static void traverseTable(void)
{
	struct list_head* iter_hashTable;
	struct list_head* iter_bucket;
	//for each entry in hashTable list
	list_for_each(iter_hashTable, &hashTable)
	{
	struct bucket* bucket_n = list_entry(iter_hashTable, struct bucket, hash_head);
	//for each entry in bucket
		list_for_each(iter_bucket, &(bucket_n->bucket_head))
		{
			struct birthday* person = list_entry(iter_bucket, struct birthday, head);
			printk("Name: %s, day=%d, month=%d, year=%d",person->name,
						 person->day, person->month, person->year);
		}
	}
}


struct list_head* get_bucket_head(char* name){
	unsigned int key = hashName(name);
	struct list_head* iter;
	list_for_each(iter, &hashTable)
	{
		struct bucket* a_bucket = list_entry(iter, struct bucket, hash_head);
		//if a match for key found in existing hashTable
		if (a_bucket->key==key){
	    return a_bucket->hash_head;
		}
  }
  //if no match found for bucket with the key for name
  struct bucket* new_bucket;
  new_bucket = kmalloc(sizeof(*new_bucket), GFP_KERNEL);
  new_bucket->key = key;
  this_bucket = *new_bucket;
  list_add_tail(new_bucket->hash_head, &hashTable);
  return new_bucket->hash_head;
}


static void add_birthday(struct birthday person)
{
	struct list_head *person_bucket;
	person_bucket = get_bucket_head(person.name);
	list_add_tail(&(person.head), &(person_bucket.bucket_head));
}



/* This function is called when the module is loaded. */
static int __init main_init(void)
{
	printk(KERN INFO "Loading Module\n");
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

	add_birthday(person1);
	add_birthday(person2);
	add_birthday(person3);
	add_birthday(person4);
	add_birthday(person5);

	traverseTable();
	return 0;
}

/* This function is called when the module is removed. */
static void __exit main_exit(void)
{
	kfree(&hashTable);
	printk(KERN INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */

module init(main_init);
module exit(main_exit);
MODULE LICENSE("GPL");
MODULE DESCRIPTION("Project 1");
MODULE AUTHOR("Ashish Adhikari");