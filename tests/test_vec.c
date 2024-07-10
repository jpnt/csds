#include "../include/csds_vec.h"
#include "../include/csds_femtotest.h"

void test_vec_alloc_dealloc(void)
{
	/* Can also use: const VecHeader* vhead */
	const struct csds_vec_header* vhead;
	int* v_int = NULL;

	ASSERT_EQUALS(sizeof(v_int[0]), sizeof(int));

	vec_alloc((void**)&v_int, sizeof(v_int[0]), 10);

        vhead = VEC_HEADER_OF(v_int);

	/* printf("vhead = 0x%p\n", (void*)vhead); */
	/* printf("v_int = 0x%p\n", (void*)v_int); */

	ASSERT_EQUALS((char*)v_int-sizeof(struct csds_vec_header), (char*)vhead);

        ASSERT_EQUALS(vhead->cap, 10);

	/* Will free both vhead and v_int */
	vec_dealloc(v_int);
}

void test_vec_insert_remove(void)
{
	const struct csds_vec_header* vhead;
	int* v_int = NULL;
	int value = 761276891;
	int removed;

	/* Handling errors example, see csds_error.{h,c} */
	HANDLE_ERROR(vec_alloc((void**)&v_int, sizeof(v_int[0]), 0));

	vhead = VEC_HEADER_OF(v_int);

	ASSERT_EQUALS(vhead->cap, CSDS_VEC_INITIAL_CAP);

	vec_insert(v_int, 0, &value);
	ASSERT_EQUALS(v_int[0], value);

	/* Store the value, not the pointer to it */
	ASSERT_EQUALS(v_int[0], value);

	vec_remove(v_int, 0, &removed);
	ASSERT_EQUALS(removed, value);

	vec_dealloc(v_int);
}

void test_vec_push_pop(void)
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

void test_vec_growth(void)
{
	const struct csds_vec_header* vhead;
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

void test_vec_use_as_stack(void)
{
	const struct csds_vec_header* vhead;
	int value_in, value_out;

	int* v_int = NULL;
	vec_alloc((void**)&v_int, sizeof(int), 3);

	/* To use as a stack, use vec_push and vec_pop */

	/* Values are memcpy'ed */
	value_in = 10;
	vec_push(v_int, &value_in);
	value_in = 20;
	vec_push(v_int, &value_in);
	value_in = 30;
	vec_push(v_int, &value_in);

	vhead = VEC_HEADER_OF(v_int);
	ASSERT_EQUALS(vhead->len, 3);
	ASSERT_EQUALS(vhead->cap, 3);

	/* Remove them and copy to value_out */
	vec_pop(v_int, &value_out);
	ASSERT_EQUALS(value_out, 30);

	vec_pop(v_int, &value_out);
	ASSERT_EQUALS(value_out, 20);

	vec_pop(v_int, &value_out);
	ASSERT_EQUALS(value_out, 10);
}

void test_vec_use_as_fifo(void)
{
	const struct csds_vec_header* vhead;
	int value_in, value_out;

	int* v_int = NULL;
	vec_alloc((void**)&v_int, sizeof(int), 3);

	/* To use as a FIFO queue, use vec_push and vec_remove(,item_idx=0,) */

	/* Values are memcpy'ed */
	value_in = 10;
	vec_push(v_int, &value_in);
	value_in = 20;
	vec_push(v_int, &value_in);
	value_in = 30;
	vec_push(v_int, &value_in);

	vhead = VEC_HEADER_OF(v_int);
	ASSERT_EQUALS(vhead->len, 3);
	ASSERT_EQUALS(vhead->cap, 3);

	/* Remove them and copy to value_out */
	vec_remove(v_int, 0, &value_out);
	ASSERT_EQUALS(value_out, 10);

	vec_remove(v_int, 0, &value_out);
	ASSERT_EQUALS(value_out, 20);

	vec_remove(v_int, 0, &value_out);
	ASSERT_EQUALS(value_out, 30);
}

int main(void)
{
	TEST_RUN(test_vec_alloc_dealloc, "test_vec_alloc_dealloc");
	TEST_RUN(test_vec_insert_remove, "test_vec_insert_remove");
	TEST_RUN(test_vec_push_pop, "test_vec_push_pop");
	TEST_RUN(test_vec_growth, "test_vec_growth");
	TEST_RUN(test_vec_use_as_stack, "test_vec_use_as_stack");
	TEST_RUN(test_vec_use_as_fifo, "test_vec_use_as_fifo");

	TEST_REPORT();
}
