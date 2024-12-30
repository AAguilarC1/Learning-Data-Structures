#ifndef TEST_MIN_HEAP_H
#define TEST_MIN_HEAP_H
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "heap.h"

void testAllocateHeap();
void testAllocateHeapFromArray();
void testInsertIntoHeapArray();
void testInsert();

int test_min_heap_suite(CU_pSuite min_heap_suite);

#endif // TEST_MIN_HEAP_H