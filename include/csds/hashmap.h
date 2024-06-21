#ifndef CSDS_HASHMAP_H
#define CSDS_HASHMAP_H

#include <stddef.h>

#ifndef __H_KEY_TYPE
#define __H_KEY_TYPE void*
#endif /* !__H_KEY_TYPE */

#ifndef __H_VALUE_TYPE
#define __H_VALUE_TYPE void*
#endif /* !__H_VALUE_TYPE */

/* what to return if the value is invalid, has to be of type __H_VALUE_TYPE */
#ifndef __H_VALUE_INVALID
#define __H_VALUE_INVALID NULL
#endif /* !__H_VALUE_INVALID */

#ifndef __H_GROWTH_FACTOR
#define __H_GROWTH_FACTOR 1.5
#endif /* !__H_GROWTH_FACTOR */

typedef struct {
	__H_KEY_TYPE* keys; /* array of keys */
	__H_VALUE_TYPE* values; /* array of values */
	size_t key_size; /* size of each key for ptr arithmetic */
	size_t value_size; /* size of each value for ptr arithmetic */
	size_t capacity; /* current capacity of the hashmap */
	size_t len; /* number of key-value pairs in the hash table */
	size_t (*hash)(const __H_KEY_TYPE* key); /* hash function to calculate the hash index */
	int (*compare)(const __H_KEY_TYPE* a, __H_KEY_TYPE* b); /* compare function between two keys */
} HashMap;

extern HashMap* hashmap_alloc(size_t len, size_t (*hash)(const __H_KEY_TYPE* key)); /* allocates memory for the hash map */
extern void hashmap_dealloc(HashMap* map); /* frees memory that was allocated */
extern size_t hashmap_insert(HashMap* map, __H_KEY_TYPE key, __H_VALUE_TYPE value); /* inserts key-value pair into hash map, returns hash */
extern __H_VALUE_TYPE hashmap_value(HashMap* map, __H_KEY_TYPE key); /* gets value for a key */
extern void hashmap_remove(HashMap* map, __H_KEY_TYPE key); /* removes key-value pair from the hash map */
/* auxiliary functions for the `hash` and `compare` function pointers */
extern size_t hash_djb2(const __H_KEY_TYPE* key); /* sample hash function, returns hash_idx */
extern int compare_str(const char* a, const char* b); /* compare function for strings */
extern int compare_int(const int a, const int b); /* compare function for integers */

#endif /* !CSDS_HASHMAP_H */
