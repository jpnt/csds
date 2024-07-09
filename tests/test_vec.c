#include "../include/csds_vec.h"
#include "../include/csds_femtotest.h"

void test_alloc_dealloc(void)
{
	struct csds_vec_header* vhead;
	int* v_int = NULL;

	ASSERT_EQUALS(sizeof(v_int[0]), sizeof(int));

	vec_alloc((void**)&v_int, sizeof(v_int[0]), 10);

	ASSERT(v_int != NULL, "Failed to alloc memory");

        vhead = VEC_HEADER_OF(v_int);

	/* printf("vhead = 0x%p\n", (void*)vhead); */
	/* printf("v_int = 0x%p\n", (void*)v_int); */

	ASSERT_EQUALS((char*)v_int-sizeof(struct csds_vec_header), (char*)vhead);

        ASSERT_EQUALS(vhead->cap, 10);

	/* Will free both vhead and v_int */
	vec_dealloc(v_int);
}

void test_insert_remove(void)
{
	struct csds_vec_header* vhead;
	int* v_int = NULL;
	int value = 761276891;
	int old_value = value;
	int removed;

	/* Handling errors example, see csds_error.{h,c} */
	HANDLE_ERROR(vec_alloc((void**)&v_int, sizeof(v_int[0]), 0));

	vhead = VEC_HEADER_OF(v_int);

	ASSERT_EQUALS(vhead->cap, CSDS_VEC_INITIAL_CAP);

	vec_insert(v_int, 0, &value);
	ASSERT_EQUALS(v_int[0], value);

	/* Store the value, not the pointer to it */
	value = 11;
	ASSERT_EQUALS(v_int[0], old_value);
	value = old_value;

	vec_remove(v_int, 0, &removed);
	ASSERT_EQUALS(removed, value);

	vec_dealloc(v_int);
}

void test_push_pop(void)
{
	int* v_int = NULL;
	int value = 991278;
	int old_value = value;

	/* Explicit allocation, always */
	vec_alloc((void**)&v_int, sizeof(int), 0);

	vec_push(v_int, &value);

	value = 11;
	ASSERT_EQUALS(v_int[0], old_value);
	
	vec_pop(v_int, &value);
	ASSERT_EQUALS(value, old_value);
}

void test_growth(void)
{
	VecHeader* vhead;
	int* v_int = NULL;
	int value = 123;

	vec_alloc((void**)&v_int, sizeof(int), 1);

	vhead = VEC_HEADER_OF(v_int);

	vec_push(v_int, &value);
	ASSERT_EQUALS(vhead->cap, 1);
	ASSERT_EQUALS(v_int[0], value);

	vec_push(v_int, &value);
	ASSERT(vhead->cap > 1, "Vec capacity should grow");
	/* printf("vhead->cap=%ld\n", vhead->cap); */
	ASSERT_EQUALS(v_int[1], value);

	vec_dealloc(v_int);
}

int main(void)
{
	TEST_RUN(test_alloc_dealloc, "test_alloc_dealloc");
	TEST_RUN(test_insert_remove, "test_insert_remove");
	TEST_RUN(test_push_pop, "test_push_pop");
	TEST_RUN(test_growth, "test_growth");

	TEST_REPORT();
}
