#ifndef TEST_DYNAMIC_ARRAY_H
#define TEST_DYNAMIC_ARRAY_H
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include "test_util.h"
#include "dynamic_array.h"

void test_dyn_arr_create(void);
void test_dyn_arr_push_pop(void);
void test_dyn_arr_peek(void);

int test_dynamic_arr_suite(CU_pSuite dyn_arr_suite);


#endif // TEST_DYNAMIC_ARRAY_H
