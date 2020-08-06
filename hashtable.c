#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUCKET_INIT_COUNT 50
#define LOAD_FACTOR 1.1

int hashFn(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return (int)hash;
}

// Called upon reaching load factor. Doubles bucket size
void rehash(hashtable *ht) {
	// Initialize new hashtable
	hashtable new_ht;
	new_ht.bucketCount = ht->bucketCount*2;
	new_ht.size = 0;
	new_ht.buckets = malloc(sizeof(item*) * new_ht.bucketCount);

	// Copy the old hashtable over and delete old items
	for (int i = 0; i < ht->bucketCount; i++) {
		item *current = ht->buckets[i];
		while (current != NULL) {
			// TODO: Put old elements in new table (no malloc())
			htable_put(&new_ht, current->key, current->value);

			item *next = current->next;
			free(current);
			current = next;
		}
	}

	// Empty old buckets and update hashtable pointer to new one
	free(ht->buckets);
	*ht = new_ht;
}

// Initiates an item at given location
void item_init(item **t, char *key, int value) {
	*t = malloc(sizeof(item));
	(*t)->value = value;
	strcpy((*t)->key, key);
	(*t)->next = NULL;
}

void htable_init(hashtable *ht) {
	ht->buckets = malloc(sizeof(item *) * BUCKET_INIT_COUNT);
	ht->size = 0;
	ht->bucketCount = BUCKET_INIT_COUNT;
}

void htable_put(hashtable *ht, char *key, int value) {
	int index = hashFn(key) % ht->bucketCount;
	// Bucket is empty
	if (ht->buckets[index] == NULL)
		item_init(&ht->buckets[index], key, value);
	else {
		item* current = ht->buckets[index];
		while (strcmp(current->key, key) != 0 && current->next != NULL)
			current = current->next;
		// If current key already exists
		if (strcmp(current->key, key) == 0) {
			current->value = value;
			return;
		}
		// Create new item at the end
		item* new;
		item_init(&new, key, value);
		current->next = new;
	}
	ht->size++;
	if ((float)ht->size / ht->bucketCount > LOAD_FACTOR)
		rehash(ht);
}

int htable_get(hashtable *ht, char *key) {
	int index = hashFn(key) % ht->bucketCount;
	item* current = ht->buckets[index];
	while (current != NULL && strcmp(current->key, key) != 0) {
		current = current->next;
	}
	if (current == NULL)
		return -1;
	return current->value;
}

void htable_delete(hashtable *ht, char *key) {
	int index = hashFn(key) % ht->bucketCount;
	item* current = ht->buckets[index];
	item* last = current;
	while (current != NULL && strcmp(current->key, key) != 0) {
		last = current;
		current = current->next;
	}
	// No key found
	if (current == NULL)
		return;

	// Deleting head of bucket
	if (current == last) {
		// Set second item as head for bucket
		ht->buckets[index] = current->next;
		free(current);
	}
	else {
		// Save pointer to next item
		item *next = current->next;
		// Assign it as last item's next
		last->next = next;
		free(current);
	}
	ht->size--;
}

void htable_free(hashtable *ht) {
	for (int i = 0; i < ht->bucketCount; i++) {
		item *current = ht->buckets[i];
		while (current != NULL) {
			item *temp = current->next;
			free(current);
			ht->size--;    // Useful for debbuging
			current = temp;
		}
	}
	if (ht->size != 0) {/* output error */}
}

int htable_isEmpty(hashtable *ht) {
	return ht->size == 0;
}

int htable_size(hashtable *ht) {
	return ht->size;
}

int htable_containsKey(hashtable *ht, char *key) {
	int index = hashFn(key) % ht->bucketCount;
	item* current = ht->buckets[index];
	while (current != NULL) {
		if (strcmp(current->key, key) == 0)
			return 1;
	}
	return 0;
}

void htable_print(hashtable *ht) {
	for (int i = 0; i < ht->bucketCount; i++) {
		// If current bucket is empty, don't print it
		if (ht->buckets[i] == NULL)
			continue;
		printf("Bucket %d: ", i);
		item *current = ht->buckets[i];
		while (current != NULL) {
			printf("\"%s\":%d, ", current->key, current->value);
			current = current->next;
		}
		printf("\n");
	}
}
