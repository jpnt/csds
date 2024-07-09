/* #include "../include/csds/vec.h" */

/* TODO */
/* void vec_quick_sort(Vec* vec); */

/* FIRST RULE, DONT RELY ON THE DATA STRUCTURE BUT ON THE FIELDS, DONT CREATE UNNCESSARY DEPENDENCIES */

/* int vec_linear_search(const Vec* vec, const void* x, */
/* 		int(*cmp)(const void*, const void*)); */
/*  */
/* int vec_binary_search(const Vec* vec, const void* x, */
/* 		int(*cmp)(const void*, const void*)) { */
/* 	int i = 0; */
/* 	int j = vec->len-1; */
/* 	int m; */
/*  */
/* 	while (i<j) { */
/* 		m = (i+j)/2; */
/* 		if (cmp(x, vec->items[m]) > 0) */
/* 			i=m+1; */
/* 		j=m; */
/* 	} */
/* 	if (cmp(x, vec->items[i]) == 0) */
/* 		return i; */
/*  */
/* 	return -1; */
/* } */
