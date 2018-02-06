#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

//number of buckets for hash table implementation
#define HASH_TABLE_SIZE 20
//hash table implemented as doubly linked list with buckets of unique value 
static struct list_head hashTable;
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


	
	struct birthday person1 = {
	  .name = "Charles",
		.day = 12,
	  .month = 1,
	  .year = 1921,
	};
	struct birthday person2 = {
	  .name = "Xavier",
		.day = 1,
	  .month = 12,
	  .year = 1321,
	};
	struct birthday person3 = {
	  .name = "Cotay",
		.day = 22,
	  .month = 11,
	  .year = 1421,
	};
	struct birthday person4 = {
	  .name = "Ramy",
		.day = 22,
	  .month = 10,
	  .year = 1969,
	};
	struct birthday person5 = {
	  .name = "Simpson",
		.day = 13,
	  .month = 7,
	  .year = 1979,
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
  while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % HASH_TABLE_SIZE ;  //limit hash table size
}

static void traverseTable(void)
{
	//traverse only if list not empty 
	if (!list_empty(&hashTable)){
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
}

//create new bucket and add it to hashTable
struct list_head* create_bucket(unsigned int key){
	struct bucket *new_bucket = kmalloc(sizeof(struct bucket), GFP_KERNEL);
	//init key for new bucket
	new_bucket->key=key;
	//init hash head to hashTable
	new_bucket->hash_head = hashTable;
	//add new bucket to hashTable
	list_add_tail(&(new_bucket->hash_head), &hashTable);
	return &(new_bucket->bucket_head);
}




//return the bucket (and init if necessary) a person with this name will belong to
struct list_head* get_bucket_head(char* name){
	unsigned int key = hashName(name);
	struct list_head *iter;
	struct bucket *cur_bucket;
	list_for_each(iter, &hashTable){
		cur_bucket = list_entry(iter, struct bucket, hash_head);
		if (key==cur_bucket->key){
			return &(cur_bucket->bucket_head);
		}
	}
	//if bucket with key not present in hashTable
	return create_bucket(key);
}


static void add_birthday(struct birthday person)
{
	//get the bucket this record will belong to
	struct list_head *person_bucket = get_bucket_head(person.name);
	//put the node into a bucket
	list_add_tail(&(person.head), person_bucket);

}


/* This function is called when the module is loaded. */
static int __init main_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	//initialise 5 struct birthday elements

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
	//kfree(&hashTable);
	printk(KERN_INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */

module_init(main_init);
module_exit(main_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Project 1");
MODULE_AUTHOR("Ashish Adhikari");