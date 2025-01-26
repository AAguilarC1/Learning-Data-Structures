#ifndef TEST_BINARY_HEAP_H
#define TEST_BINARY_HEAP_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stddef.h>

void test_binary_heap_create_free(void);
void test_binary_heap_enqueue_dequeue(void);
void test_binary_heap_peek(void);
void test_binary_heap_merge(void);

int test_binary_heap_suite(CU_pSuite bnt_suite);

#endif // TEST_BINARY_HEAP_H

