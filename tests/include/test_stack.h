#ifndef TEST_STACK_H
#define TEST_STACK_H
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "stack.h"
//TODO: Add tests for stack

void test_stack_create(void);
void test_stack_push_pop(void);

int test_stack_suite(CU_pSuite stack_suite);

#endif