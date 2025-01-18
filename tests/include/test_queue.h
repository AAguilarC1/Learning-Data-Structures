#ifndef TEST_QUEUE_H
#define TEST_QUEUE_H
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdint.h>
#include "test_util.h"
#include "queue.h"

void test_queue_create_free(void);
void test_queue_enqueue_dequeue(void);
void test_queue_peek(void);

int test_queue_suite(CU_pSuite q_suite);

#endif //TEST_QUEUE_H
