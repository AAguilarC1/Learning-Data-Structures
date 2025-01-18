#ifndef TEST_DOUBLY_LINKED_LIST_H
#define TEST_DOUBLY_LINKED_LIST_H
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "test_util.h"
#include "doubly_linked_list.h"

void test_dll_create_list(void);
void test_dll_add_remove_node_head(void);
void test_dll_add_remove_node_tail(void);
void test_dll_insert_remove_node_at(void);
void test_dll_peek(void);

int test_doubly_linked_list_suite(CU_pSuite dll_suite);

#endif // TEST_DOUBLY_LINKED_LIST_H
