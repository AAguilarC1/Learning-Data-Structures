#ifndef TEST_RING_BUFFER_H
#define TEST_RING_BUFFER_H
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_rb_create_free(void);
void test_rb_push_pop(void);

int test_rb_suite(CU_pSuite rb_suite);

#endif // TEST_RING_BUFFER_H

