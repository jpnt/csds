#ifndef CSDS_VEC_H
#define CSDS_VEC_H

#include <stddef.h>

#ifndef __V_ITEM_TYPE
#define __V_ITEM_TYPE void*
#endif

/* what to return if the item is invalid, has to be of type __V_ITEM_TYPE */
#ifndef __V_ITEM_INVALID
#define __V_ITEM_INVALID NULL
#endif /* !__V_ITEM_INVALID */

#ifndef __V_GROWTH_FACTOR
#define __V_GROWTH_FACTOR 1.5
#endif /* !__V_GROWTH_FACTOR */

typedef struct {
	__V_ITEM_TYPE* items;
	size_t len;
	size_t capacity;
} Vec;

extern Vec* vec_alloc(size_t capacity); /* allocate new vector with the specified initial capacity */
extern void vec_dealloc(Vec* vec); /* free the vector and optionally free all associated memory */
extern void vec_grow(Vec* vec); /* grow/reallocate the vector to accommodate more items */
/* whole purpose of having Vec is for it to be able to grow and accommodate generic values, so there is no vec_init */
extern void vec_insert(Vec* vec, size_t item_idx, __V_ITEM_TYPE item); /* insert an item at the specified index */
extern __V_ITEM_TYPE vec_remove(Vec* vec, size_t item_idx); /* remove and return the item at the specified index */
extern void vec_push(Vec* vec, __V_ITEM_TYPE item); /* push an item onto the end of the vector */
extern __V_ITEM_TYPE vec_pop(Vec* vec); /* pop and return the item from the end of the vector */

#endif /* !CSDS_VEC_H */
