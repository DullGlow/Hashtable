#ifndef HASH_TABLE
#define HASH_TABLE

typedef struct item
{
	int value;
	char key[50];
	struct item *next;
}item;

typedef struct hashtable
{
	int size;
	int bucketCount;
	item **buckets;
}hashtable;

// Initiate hash table
void htable_init(hashtable *ht);

// Put <key,value> pair in table
void htable_put(hashtable *ht, char *key, int value);

// Get value of key
int htable_get(hashtable *ht, char *key);

// Delete <key,value> pair which has given key
void htable_delete(hashtable *ht, char *key);

// Cleans entire table
void htable_free(hashtable *ht);

// Checks if table has any element in it
int htable_isEmpty(hashtable *ht);

// Returns amount of elements table has
int htable_size(hashtable *ht);

// Check if key is present in table
int htable_containsKey(hashtable *ht, char *key);

// Prints out buckets and its pairs
void htable_print(hashtable *ht);

#endif
