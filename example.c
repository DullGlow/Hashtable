#include <stdio.h>
#include "hashtable.h"


int main() {
    printf("HashTable test:\n");
    printf("Size allocated for each pair: %ld bytes\n", sizeof(item));
    printf("Size allocated for bucket array: %ld*BucketCount bytes\n", sizeof(item *));
    hashtable ht;
    htable_init(&ht);

    printf("\nPutting one:1, two:2, three:3 in table\n");
    htable_put(&ht, "one", 1);
    htable_put(&ht, "two", 2);
    htable_put(&ht, "three", 3);

    htable_print(&ht);
    printf("size(): %d\n", htable_size(&ht)); // same as ht.size
    printf("bucketCount: %d\n", ht.bucketCount);

    printf("\nFilling table with \"i\":i, where i is 0-49\n");
    for (int i = 0; i < 50; i++) {
        char key[50];
        sprintf(key, "%d", i);
        htable_put(&ht, key, i);
    }

    htable_print(&ht);
    printf("size(): %d\n", htable_size(&ht));
    printf("bucketCount: %d\n\n", ht.bucketCount);

    return 0;
}
