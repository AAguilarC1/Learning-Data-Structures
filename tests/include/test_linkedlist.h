#ifndef TEST_LINKEDLIST_H
#define TEST_LINKEDLIST_H
// TODO: Add tests for linkedlist
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "linkedlist.h"

void testCreateList(void);
void test_ll_insert_node_head(void);
void test_ll_insert_node_tail(void);
void test_ll_insert_node_at(void);

void test_ll_delete_node_head(void);
void test_ll_delete_node_tail(void);
void test_ll_delete_node_at(void);

void test_peek(void);

int test_linkedlist_suite(CU_pSuite linkedlist_suite);

#endif // TEST_LINKEDLIST_H
